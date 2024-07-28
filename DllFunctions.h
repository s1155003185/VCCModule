// <vcc:vccproj gen="DEMAND"/>
#ifndef DLL_FUNCTIONS_H
#define DLL_FUNCTIONS_H

#ifdef _WIN32
#define DLLEXPORT __declspec (dllexport) 
#else
#define DLLEXPORT extern 
#endif

// <vcc:dllInterfaceHeader gen="FORCE">
// </vcc:dllInterfaceHeader>

extern "C"
{

DLLEXPORT int GetVersion();

// <vcc:dllInterface gen="FORCE">
// </vcc:dllInterface>
}

#endif