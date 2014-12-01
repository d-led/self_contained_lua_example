/* This file has been generated using ris, do not modify! */
#include "resource.h"
#include <unordered_map>
namespace test {
std::string Resource::hello() {
    static char const literal[] =  {
        112, 114, 105, 110, 116, 39, 104, 101, 108, 108, 111, 33, 39, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::Get(std::string const& key) {
    static std::unordered_map<std::string,ResourceGetter> getters = {
        { "hello", Resource::hello },
    };
    auto getter = getters.find(key);
    if (getter == getters.end())
         return OnNoKey(key);
    return getter->second();
}
}
