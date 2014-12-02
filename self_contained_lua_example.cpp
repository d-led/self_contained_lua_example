#include <LuaState.h>
#include <iostream>

#include "resource.h"

#include <lua.hpp>

int resource_module_loader(lua_State* L) {
    const char* name = lua_tostring(L,-1);
    test::Resource::GetKeys([name, L](std::string const& resource_name) {
        if (resource_name == name) {
            auto res = test::Resource::Get(resource_name);
            int ret = luaL_loadbuffer(L, res.c_str(), res.size(), name);
            switch (ret) {
                case LUA_ERRMEM:
                    return luaL_error(L, "LUA_ERRMEM: %s\n", lua_tostring(L, -1));
                case LUA_ERRSYNTAX:
                    return luaL_error(L, "LUA_ERRSYNTAX: %s\n", lua_tostring(L, -1));
            }
            return 1;
        }
    });

    return 0;
}

void set_loader(lua_State* L) {
    lua_register(L, "_____", resource_module_loader);
    luaL_dostring(L, "table.insert(package.loaders, _____)");
    luaL_dostring(L, "_____ = nil");
}

int main() {
    try {
        lua::State s;
        s.doString(test::Resource::hello());

        s.set("test", s.doString(test::Resource::test_module()));
        s.doString("test.hello()");

        set_loader(s.getState());

        s.doString("my_module = require 'test/test'");
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
