#pragma once
#include <vector>

namespace vcc
{
    // general
    #define GETSET(type, var, def) \
    private: \
        type _##var = def; \
    public: \
        type Get##var() { return _##var; }\
        void Set##var(type val) { _##var = val; }

    #define GET(type, var, def) \
    private: \
        type _##var = def; \
    public: \
        type Get##var() { return _##var; }\

    #define SET(type, var, def) \
    private: \
        type _##var = def; \
    public: \
        void Set##var(type val) { _##var = val; }

    #define STATICGET(type, var, def) \
    public: \
        static type Get##var() { return def; }
        
    // list
    #define GETVECTOR(type, var) \
    private: \
        std::vector<type> _##var; \
    public: \
        std::vector<type> *Get##var() { return &_##var; }
        
}
