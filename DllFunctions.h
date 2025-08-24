// <vcc:vccproj gen="DEMAND"/>
#ifndef DLL_FUNCTIONS_H
#define DLL_FUNCTIONS_H

#include <string>

#ifdef _WIN32
#define DLLEXPORT __declspec (dllexport) 
#else
#define DLLEXPORT extern 
#endif

// <vcc:dllInterfaceHeader gen="REPLACE">
// </vcc:dllInterfaceHeader>

extern "C"
{

DLLEXPORT int getVersion();

// <vcc:dllInterface gen="REPLACE">
// </vcc:dllInterface>
}

#endif