#include <LuaState.h>
#include <iostream>

#include "resource.h"

int main() {
    try {
        lua::State s;
        s.doString(test::Resource::hello());
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
