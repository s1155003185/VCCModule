#include <gtest/gtest.h>

#include <string>

#include "dll.hpp"

#define DLL_NAME L"libVCCCore"

TEST(DllTest, LoadDll) {
    std::wstring dllName = DLL_NAME;

    #ifdef _WIN32
    dllName += L".dll";
    #elif __aarch64__
    dllName = L"bin/Debug/" + dllName + L".dylib";
    #else
    dllName = L"bin/Debug/" + dllName + L".so";
    #endif
    vcc::Dll h(dllName);
    EXPECT_TRUE(h.getH());
    
    typedef long long int (*getVersionFunction)();
    const getVersionFunction getVersion = reinterpret_cast<getVersionFunction>(h.getProcedure(L"getVersion"));
    EXPECT_TRUE(getVersion != nullptr);
    EXPECT_EQ(getVersion(), 1);
}
