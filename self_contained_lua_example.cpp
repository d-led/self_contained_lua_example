#include <LuaState.h>
#include <iostream>

#include "resource.h"

int main() {
    try {
        lua::State s;
        s.doString(test::Resource::hello());

        s.set("test", s.doString(test::Resource::test_module()));
        s.doString("test.hello()");
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
