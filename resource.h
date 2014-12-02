#pragma once
/* This file has been generated using ris, do not modify! */
#include <string>
namespace test {
class Resource /*final*/ {
public:
    static std::string hello();
    static std::string test_module();
public:
    typedef std::string(*ResourceGetter)();
public: // key/value api
template <typename TInserter>
static void GetKeys(TInserter inserter) {
    static const char* keys[] = {
        "hello",
        "test/test",
    };
    for (auto key : keys) {
        inserter(key);
    }
}
public: // key/value api
    static std::string Get(std::string const& key);
public:
    static std::string OnNoKey(std::string const& key="") {
        // could be configured to throw
        return "";
    }
};
}
