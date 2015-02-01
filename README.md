a self contained lua example
============================

This is an example of a C++ program with embedded lua scripts.

embedding the resources
-----------------------

the [resources](resources.json) (scripts) are embedded using the resource compiler [ris](https://github.com/d-led/ris).

```
premake4 res
```

custom lua module loader
------------------------
the example features a custom lua module loader ([`resource_module_loader`, `set_loader`](self_contained_lua_example.cpp)) which allows loading lua modules from the embedded text resources.

embedded libraries
------------------

- [lualinq](https://github.com/xanathar/lualinq.git), Copyright (c) 2014, Marco Mastropaolo


alternatives
------------

- [single-executable app deployment for LuaJIT: bundle](http://luapower.com/bundle)
- [seed: a lua executable which loads data from a zip file concatenated to itself](https://github.com/Chingliu/seed)
