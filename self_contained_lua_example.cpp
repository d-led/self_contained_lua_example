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
            std::cout<<"Loading "<<name<<" from an embedded resource"<<std::endl;
            auto res = test::Resource::Get(resource_name);
            int ret = luaL_loadbuffer(L, res.c_str(), res.size(), name);
            switch (ret) {
                case LUA_ERRMEM:
                    top = luaL_error(L, "Memory error: %s\n", lua_tostring(L, -1));
                    return;
                case LUA_ERRSYNTAX:
                    top = luaL_error(L, "Syntax error: %s\n", lua_tostring(L, -1));
                    return;
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

        // set a custom module loader
        set_loader(s.getState());
        
        // load a module from memory
        s.doString("my_module = require 'test/test'");
        
        s["my_module"]["hello"]();
        
        // Another module from embedded resources
        s.doString("require 'lualinq'");

        // example from lualinq docu, Copyright (c) 2014, Marco Mastropaolo
        s.doString(R"(
            local array = { { say="ciao", lang="ita" }, { say="hello", lang="eng" }, }
            from(array)
                :where("lang", "ita")
                :select("say")
                :foreach(print)
        )");

        // should not cause any action since module already loaded
        s.doString("require 'lualinq'");
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
