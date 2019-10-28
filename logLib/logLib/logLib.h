// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LOGLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LOGLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#include <string>

#ifdef LOGLIB_EXPORTS
#define LOGLIB_API __declspec(dllexport)
#else
#define LOGLIB_API __declspec(dllimport)
#endif

extern "C" LOGLIB_API bool logMessage(std::string logMessage, std::string filePath);