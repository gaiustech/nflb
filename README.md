## No Files Left Behind

A slightly dodgy method of ensuring that temp files are cleaned when a process
exits. Intercepts `open64()` and logs files opened with `O_CREAT`. But intercepting
`exit()` or using a destructor won't work as the process may exit abnormally. Then
the wrapper script deletes them when the process exits by any means. The sensible
modern way to do this would be with a container!

### Usage:

Tested on CentOS 7.5

```
$ gcc -fPIC -shared -o nflb.so nflb.c -ldl
$ ./nflb.sh python -c "from tempfile import mkstemp; [mkstemp() for x in range(10)]"
Cleaning up /tmp/7XQmvc
Cleaning up /tmp/tmp0mSl6W
Cleaning up /tmp/tmpezR1Kk
Cleaning up /tmp/tmpvgAzkp
Cleaning up /tmp/tmp1oTe5Z
Cleaning up /tmp/tmpLoPPxA
Cleaning up /tmp/tmpykHlC5
Cleaning up /tmp/tmpnzaOnH
Cleaning up /tmp/tmpCfZ3ej
Cleaning up /tmp/tmpY3AcqZ
Cleaning up /tmp/tmpzcg1rB
```

_eof_
