/* This file has been generated using ris, do not modify! */
#include "resource.h"
#include <unordered_map>
namespace test {
std::string Resource::hello() {
    static char const literal[] =  {
        112, 114, 105, 110, 116, 39, 104, 101, 108, 108, 111, 32, 102, 114, 111, 109, 32, 114, 101, 115, 111, 117, 114, 99, 101, 32, 115, 116, 114, 105, 110, 103, 33, 39, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::test_module() {
    static char const literal[] =  {
        108, 111, 99, 97, 108, 32, 116, 61, 123, 125, 10, 116, 46, 104, 101, 108, 108, 111, 61, 102, 117, 110, 99, 116, 105, 111, 110, 40, 41, 32, 112, 114, 105, 110, 116, 39, 104, 101, 108, 108, 111, 32, 102, 114, 111, 109, 32, 114, 101, 115, 111, 117, 114, 99, 101, 32, 109, 111, 100, 117, 108, 101, 33, 39, 32, 101, 110, 100, 10, 114, 101, 116, 117, 114, 110, 32, 116, 10, 
    };
    return std::string(literal, sizeof(literal)/sizeof(char));
}
std::string Resource::Get(std::string const& key) {
    static std::unordered_map<std::string,ResourceGetter> getters = {
        { "hello", Resource::hello },
        { "test/test", Resource::test_module },
    };
    auto getter = getters.find(key);
    if (getter == getters.end())
         return OnNoKey(key);
    return getter->second();
}
}
