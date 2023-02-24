#pragma once
#include <mutex>
#include <map>
#include <set>
#include <vector>

using namespace std;

namespace vcc
{
    #define THREAD_SAFE \
    protected: \
        mutex __mutex; \
    public: \
        mutex *GetMutex() { return &__mutex; }

    // general
    #define GETSET(type, var, def) \
    private: \
        type _##var = def; \
    public: \
        type Get##var() { lock_guard<mutex> lock(__mutex); return _##var; }\
        void Set##var(type val) { lock_guard<mutex> lock(__mutex); _##var = val; }

    #define GET(type, var, def) \
    private: \
        type _##var = def; \
    public: \
        type Get##var() { lock_guard<mutex> lock(__mutex); return _##var; }\

    #define STATICGET(type, var, def) \
    public: \
        static type Get##var() { return def; }
        
    // vector
    #define VECTOR(type, var) \
    private: \
        vector<type> _##var; \
    public: \
        vector<type> *Get##var() { lock_guard<mutex> lock(__mutex); return &_##var; } \
        void Insert##var(type value) { lock_guard<mutex> lock(__mutex); this->_##var.push_back(value); } \
        void Insert##var(size_t index, type value) { lock_guard<mutex> lock(__mutex); this->_##var.insert(this->_##var.begin() + index, value); } \
        void Insert##var(vector<type> &value) { this-> Insert##var(0, value); } \
        void Insert##var(size_t index, vector<type> &value) { lock_guard<mutex> lock(__mutex); this->_##var.insert(this->_##var.begin() + index, value.begin(), value.end()); } \
        void Remove##var(size_t index) { lock_guard<mutex> lock(__mutex); this->_##var.erase(this->_##var.begin() + index); } \
        void Clear##var() { lock_guard<mutex> lock(__mutex); this->_##var.clear(); }

    #define SET(type, var) \
    private: \
        set<type> _##var; \
    public: \
        set<type> *Get##var() { lock_guard<mutex> lock(__mutex); return &_##var; } \
        void Insert##var(type value) { lock_guard<mutex> lock(__mutex);  this->_##var.insert(value); } \
        void Insert##var(set<type> value) { lock_guard<mutex> lock(__mutex); this->_##var.insert(value.begin(), value.end()); } \
        void Remove##var(type value) { lock_guard<mutex> lock(__mutex); this->_##var.erase(value); } \
        void Clear##var() { lock_guard<mutex> lock(__mutex); this->_##var.clear(); }

    #define MAP(keyType, valueType, var) \
    private: \
        map<keyType, valueType> _##var; \
    public: \
        map<keyType, valueType> *Get##var() { lock_guard<mutex> lock(__mutex); return &_##var; }
        
}
