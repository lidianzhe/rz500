#ifndef REPORTINGHOOK_H
#define REPORTINGHOOK_H

#if defined(WIN32)
  #include <windows.h>
  #if defined(CMIRISLIB_LIBRARY)
	#define CMIRISLIBINTERNAL_EXPORT __declspec(dllexport)
  #else
	#define CMIRISLIBINTERNAL_EXPORT __declspec(dllimport)
  #endif
#else
  #define CMIRISLIBINTERNAL_EXPORT
#endif

#pragma once

#if defined(WIN32)
  void CMIRISLIBINTERNAL_EXPORT setFilterDebugHook(void);
#endif

#endif // REPORTINGHOOK_H
