a self contained lua example
============================

This is an example of a C++ program with embedded lua scripts.

embedding the resources
-----------------------

the resources (scripts) are embedded using the resource compiler [ris](https://github.com/d-led/ris).

```
premake4 res
```

embedded libraries
------------------

- [lualinq](https://github.com/xanathar/lualinq.git), Copyright (c) 2014, Marco Mastropaolo