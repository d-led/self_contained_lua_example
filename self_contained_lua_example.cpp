#include <LuaState.h>
#include <iostream>

#include "resource.h"

#include <lua.hpp>

int resource_module_loader(lua_State* L) {
    const char* name = luaL_checkstring(L, 1);
    lua_pop(L, 1);
    auto top = lua_gettop(L);
    test::Resource::GetKeys([name, L, &top](std::string const& resource_name) {
        if (resource_name == name) {
            auto res = test::Resource::Get(resource_name);
            int ret = luaL_loadbuffer(L, res.c_str(), res.size(), name);
            switch (ret) {
                case LUA_ERRMEM:
                    return luaL_error(L, "Memory error: %s\n", lua_tostring(L, -1));
                case LUA_ERRSYNTAX:
                    return luaL_error(L, "Syntax error: %s\n", lua_tostring(L, -1));
            }
            top = 1;
        }
    });

    return top;
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

        s["my_module"]["hello"]();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
