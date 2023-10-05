/**
 * This file is derived from versionhelpers.h of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */

#ifndef _INC_VERSIONHEADERS
#define _INC_VERSIONHEADERS

#include <winapifamily.h>

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) && !defined(__WIDL__)

#ifdef __cplusplus
#define VERSIONHELPERAPI inline bool
#else
#define VERSIONHELPERAPI FORCEINLINE BOOL
#endif

VERSIONHELPERAPI IsWindowsVersionOrGreater(WORD major, WORD minor, WORD servpack);

VERSIONHELPERAPI IsWindowsXPOrGreater(void);

VERSIONHELPERAPI IsWindowsXPSP1OrGreater(void);

VERSIONHELPERAPI IsWindowsXPSP2OrGreater(void);

VERSIONHELPERAPI IsWindowsXPSP3OrGreater(void);

VERSIONHELPERAPI IsWindowsVistaOrGreater(void);

VERSIONHELPERAPI IsWindowsVistaSP1OrGreater(void);

VERSIONHELPERAPI IsWindowsVistaSP2OrGreater(void);

VERSIONHELPERAPI IsWindows7OrGreater(void);

VERSIONHELPERAPI IsWindows7SP1OrGreater(void);

VERSIONHELPERAPI IsWindows8OrGreater(void);

VERSIONHELPERAPI IsWindows8Point1OrGreater(void);

VERSIONHELPERAPI IsWindowsThresholdOrGreater(void);

VERSIONHELPERAPI IsWindows10OrGreater(void);

VERSIONHELPERAPI IsWindowsServer(void);

#endif
#endif
