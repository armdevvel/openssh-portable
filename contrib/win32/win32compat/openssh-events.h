//**********************************************************************`
//* This is an include file generated by Message Compiler.             *`
//*                                                                    *`
//* Copyright (c) Microsoft Corporation. All Rights Reserved.          *`
//**********************************************************************`
#pragma once
#include <wmistr.h>
#include <evntrace.h>
#include "evntprov.h"
//
//  Initial Defs
//
#if !defined(ETW_INLINE)
#define ETW_INLINE DECLSPEC_NOINLINE __inline
#endif

#if defined(__cplusplus)
extern "C" {
#endif

//
// Allow Diasabling of code generation
//
#ifndef MCGEN_DISABLE_PROVIDER_CODE_GENERATION
#if  !defined(McGenDebug)
#define McGenDebug(a,b)
#endif 


#if !defined(MCGEN_TRACE_CONTEXT_DEF)
#define MCGEN_TRACE_CONTEXT_DEF
typedef struct _MCGEN_TRACE_CONTEXT
{
    TRACEHANDLE            RegistrationHandle;
    TRACEHANDLE            Logger;
    ULONGLONG              MatchAnyKeyword;
    ULONGLONG              MatchAllKeyword;
    ULONG                  Flags;
    ULONG                  IsEnabled;
    UCHAR                  Level; 
    UCHAR                  Reserve;
    USHORT                 EnableBitsCount;
    PULONG                 EnableBitMask;
    const ULONGLONG*       EnableKeyWords;
    const UCHAR*           EnableLevel;
} MCGEN_TRACE_CONTEXT, *PMCGEN_TRACE_CONTEXT;
#endif

#if !defined(MCGEN_LEVEL_KEYWORD_ENABLED_DEF)
#define MCGEN_LEVEL_KEYWORD_ENABLED_DEF
FORCEINLINE
BOOLEAN
McGenLevelKeywordEnabled(
    _In_ PMCGEN_TRACE_CONTEXT EnableInfo,
    _In_ UCHAR Level,
    _In_ ULONGLONG Keyword
    )
{
    //
    // Check if the event Level is lower than the level at which
    // the channel is enabled.
    // If the event Level is 0 or the channel is enabled at level 0,
    // all levels are enabled.
    //

    if ((Level <= EnableInfo->Level) || // This also covers the case of Level == 0.
        (EnableInfo->Level == 0)) {

        //
        // Check if Keyword is enabled
        //

        if ((Keyword == (ULONGLONG)0) ||
            ((Keyword & EnableInfo->MatchAnyKeyword) &&
             ((Keyword & EnableInfo->MatchAllKeyword) == EnableInfo->MatchAllKeyword))) {
            return TRUE;
        }
    }

    return FALSE;

}
#endif

#if !defined(MCGEN_EVENT_ENABLED_DEF)
#define MCGEN_EVENT_ENABLED_DEF
FORCEINLINE
BOOLEAN
McGenEventEnabled(
    _In_ PMCGEN_TRACE_CONTEXT EnableInfo,
    _In_ PCEVENT_DESCRIPTOR EventDescriptor
    )
{

    return McGenLevelKeywordEnabled(EnableInfo, EventDescriptor->Level, EventDescriptor->Keyword);

}
#endif


//
// EnableCheckMacro
//
#ifndef MCGEN_ENABLE_CHECK
#define MCGEN_ENABLE_CHECK(Context, Descriptor) (Context.IsEnabled &&  McGenEventEnabled(&Context, &Descriptor))
#endif

#if !defined(MCGEN_CONTROL_CALLBACK)
#define MCGEN_CONTROL_CALLBACK

//DECLSPEC_NOINLINE __inline
VOID
//__stdcall
McGenControlCallbackV2(
    _In_ LPCGUID SourceId,
    _In_ ULONG ControlCode,
    _In_ UCHAR Level,
    _In_ ULONGLONG MatchAnyKeyword,
    _In_ ULONGLONG MatchAllKeyword,
    _In_opt_ PEVENT_FILTER_DESCRIPTOR FilterData,
    _Inout_opt_ PVOID CallbackContext
    )
/*++

Routine Description:

    This is the notification callback for Vista.

Arguments:

    SourceId - The GUID that identifies the session that enabled the provider. 

    ControlCode - The parameter indicates whether the provider 
                  is being enabled or disabled.

    Level - The level at which the event is enabled.

    MatchAnyKeyword - The bitmask of keywords that the provider uses to 
                      determine the category of events that it writes.

    MatchAllKeyword - This bitmask additionally restricts the category 
                      of events that the provider writes. 

    FilterData - The provider-defined data.

    CallbackContext - The context of the callback that is defined when the provider 
                      called EtwRegister to register itself.

Remarks:

    ETW calls this function to notify provider of enable/disable

--*/
{
    PMCGEN_TRACE_CONTEXT Ctx = (PMCGEN_TRACE_CONTEXT)CallbackContext;
    ULONG Ix;
#ifndef MCGEN_PRIVATE_ENABLE_CALLBACK_V2
    UNREFERENCED_PARAMETER(SourceId);
    UNREFERENCED_PARAMETER(FilterData);
#endif

    if (Ctx == NULL) {
        return;
    }

    switch (ControlCode) {

        case EVENT_CONTROL_CODE_ENABLE_PROVIDER:
            Ctx->Level = Level;
            Ctx->MatchAnyKeyword = MatchAnyKeyword;
            Ctx->MatchAllKeyword = MatchAllKeyword;
            Ctx->IsEnabled = EVENT_CONTROL_CODE_ENABLE_PROVIDER;

            for (Ix = 0; Ix < Ctx->EnableBitsCount; Ix += 1) {
                if (McGenLevelKeywordEnabled(Ctx, Ctx->EnableLevel[Ix], Ctx->EnableKeyWords[Ix]) != FALSE) {
                    Ctx->EnableBitMask[Ix >> 5] |= (1 << (Ix % 32));
                } else {
                    Ctx->EnableBitMask[Ix >> 5] &= ~(1 << (Ix % 32));
                }
            }
            break;

        case EVENT_CONTROL_CODE_DISABLE_PROVIDER:
            Ctx->IsEnabled = EVENT_CONTROL_CODE_DISABLE_PROVIDER;
            Ctx->Level = 0;
            Ctx->MatchAnyKeyword = 0;
            Ctx->MatchAllKeyword = 0;
            if (Ctx->EnableBitsCount > 0) {
                RtlZeroMemory(Ctx->EnableBitMask, (((Ctx->EnableBitsCount - 1) / 32) + 1) * sizeof(ULONG));
            }
            break;
 
        default:
            break;
    }

#ifdef MCGEN_PRIVATE_ENABLE_CALLBACK_V2
    //
    // Call user defined callback
    //
    MCGEN_PRIVATE_ENABLE_CALLBACK_V2(
        SourceId,
        ControlCode,
        Level,
        MatchAnyKeyword,
        MatchAllKeyword,
        FilterData,
        CallbackContext
        );
#endif
   
    return;
}

#endif
#endif // MCGEN_DISABLE_PROVIDER_CODE_GENERATION
//+
// Provider OpenSSH Event Count 5
//+
EXTERN_C __declspec(selectany) const GUID OpenSSH = {0xc4b57d35, 0x0636, 0x4bc3, {0xa2, 0x62, 0x37, 0x0f, 0x24, 0x9f, 0x98, 0x02}};

//
// Channel
//
#define OpenSSH_Admin 0x10
#define OpenSSH_Operational 0x11
#define OpenSSH_Debug 0x12

//
// Levels
//
#define Debug 0x10

//
// Event Descriptors
//
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR CRITICAL_Event = {0x1, 0x0, 0x10, 0x1, 0x0, 0x0, 0x8000000000000000};
#define CRITICAL_Event_value 0x1
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR ERROR_Event = {0x2, 0x0, 0x10, 0x2, 0x0, 0x0, 0x8000000000000000};
#define ERROR_Event_value 0x2
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR WARNING_Event = {0x3, 0x0, 0x11, 0x3, 0x0, 0x0, 0x4000000000000000};
#define WARNING_Event_value 0x3
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR INFO_Event = {0x4, 0x0, 0x11, 0x4, 0x0, 0x0, 0x4000000000000000};
#define INFO_Event_value 0x4
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR DEBUG_Event = {0x6, 0x0, 0x12, 0x10, 0x0, 0x0, 0x2000000000000000};
#define DEBUG_Event_value 0x6

//
// Note on Generate Code from Manifest Windows Vista and above
//
//Structures :  are handled as a size and pointer pairs. The macro for the event will have an extra 
//parameter for the size in bytes of the structure. Make sure that your structures have no extra padding.
//
//Strings: There are several cases that can be described in the manifest. For array of variable length 
//strings, the generated code will take the count of characters for the whole array as an input parameter. 
//
//SID No support for array of SIDs, the macro will take a pointer to the SID and use appropriate 
//GetLengthSid function to get the length.
//

//
// Allow Diasabling of code generation
//
#ifndef MCGEN_DISABLE_PROVIDER_CODE_GENERATION

//
// Globals 
//


//
// Event Enablement Bits
//

EXTERN_C __declspec(selectany) DECLSPEC_CACHEALIGN ULONG OpenSSHEnableBits[1];
EXTERN_C __declspec(selectany) const ULONGLONG OpenSSHKeywords[5] = {0x8000000000000000, 0x8000000000000000, 0x4000000000000000, 0x4000000000000000, 0x2000000000000000};
EXTERN_C __declspec(selectany) const UCHAR OpenSSHLevels[5] = {1, 2, 3, 4, 16};
EXTERN_C __declspec(selectany) MCGEN_TRACE_CONTEXT OpenSSH_Context = {0, 0, 0, 0, 0, 0, 0, 0, 5, OpenSSHEnableBits, OpenSSHKeywords, OpenSSHLevels};

EXTERN_C __declspec(selectany) REGHANDLE OpenSSHHandle = (REGHANDLE)0;

#if !defined(McGenEventRegisterUnregister)
#define McGenEventRegisterUnregister
//DECLSPEC_NOINLINE __inline
ULONG //__stdcall
McGenEventRegister(
    _In_ LPCGUID ProviderId,
    _In_opt_ PENABLECALLBACK EnableCallback,
    _In_opt_ PVOID CallbackContext,
    _Inout_ PREGHANDLE RegHandle
    )
/*++

Routine Description:

    This function register the provider with ETW USER mode.

Arguments:
    ProviderId - Provider Id to be register with ETW.

    EnableCallback - Callback to be used.

    CallbackContext - Context for this provider.

    RegHandle - Pointer to Registration handle.

Remarks:

    If the handle != NULL will return ERROR_SUCCESS

--*/
{
    ULONG Error;


    if (*RegHandle) {
        //
        // already registered
        //
        return ERROR_SUCCESS;
    }

    Error = EventRegister( ProviderId, EnableCallback, CallbackContext, RegHandle); 

    return Error;
}


//DECLSPEC_NOINLINE __inline
ULONG //__stdcall
McGenEventUnregister(_Inout_ PREGHANDLE RegHandle)
/*++

Routine Description:

    Unregister from ETW USER mode

Arguments:
            RegHandle this is the pointer to the provider context
Remarks:
            If Provider has not register RegHandle = NULL,
            return ERROR_SUCCESS
--*/
{
    ULONG Error;


    if(!(*RegHandle)) {
        //
        // Provider has not registerd
        //
        return ERROR_SUCCESS;
    }

    Error = EventUnregister(*RegHandle); 
    *RegHandle = (REGHANDLE)0;
    
    return Error;
}
#endif
//
// Register with ETW Vista +
//
#ifndef EventRegisterOpenSSH
#define EventRegisterOpenSSH() McGenEventRegister(&OpenSSH, McGenControlCallbackV2, &OpenSSH_Context, &OpenSSHHandle) 
#endif

//
// UnRegister with ETW
//
#ifndef EventUnregisterOpenSSH
#define EventUnregisterOpenSSH() McGenEventUnregister(&OpenSSHHandle) 
#endif

//
// Enablement check macro for CRITICAL_Event
//

#define EventEnabledCRITICAL_Event() ((OpenSSHEnableBits[0] & 0x00000001) != 0)

//
// Event Macro for CRITICAL_Event
//
#define EventWriteCRITICAL_Event(process, payload)\
        EventEnabledCRITICAL_Event() ?\
        Template_zz(OpenSSHHandle, &CRITICAL_Event, process, payload)\
        : ERROR_SUCCESS\

//
// Enablement check macro for ERROR_Event
//

#define EventEnabledERROR_Event() ((OpenSSHEnableBits[0] & 0x00000002) != 0)

//
// Event Macro for ERROR_Event
//
#define EventWriteERROR_Event(process, payload)\
        EventEnabledERROR_Event() ?\
        Template_zz(OpenSSHHandle, &ERROR_Event, process, payload)\
        : ERROR_SUCCESS\

//
// Enablement check macro for WARNING_Event
//

#define EventEnabledWARNING_Event() ((OpenSSHEnableBits[0] & 0x00000004) != 0)

//
// Event Macro for WARNING_Event
//
#define EventWriteWARNING_Event(process, payload)\
        EventEnabledWARNING_Event() ?\
        Template_zz(OpenSSHHandle, &WARNING_Event, process, payload)\
        : ERROR_SUCCESS\

//
// Enablement check macro for INFO_Event
//

#define EventEnabledINFO_Event() ((OpenSSHEnableBits[0] & 0x00000008) != 0)

//
// Event Macro for INFO_Event
//
#define EventWriteINFO_Event(process, payload)\
        EventEnabledINFO_Event() ?\
        Template_zz(OpenSSHHandle, &INFO_Event, process, payload)\
        : ERROR_SUCCESS\

//
// Enablement check macro for DEBUG_Event
//

#define EventEnabledDEBUG_Event() ((OpenSSHEnableBits[0] & 0x00000010) != 0)

//
// Event Macro for DEBUG_Event
//
#define EventWriteDEBUG_Event(process, payload)\
        EventEnabledDEBUG_Event() ?\
        Template_zz(OpenSSHHandle, &DEBUG_Event, process, payload)\
        : ERROR_SUCCESS\

#endif // MCGEN_DISABLE_PROVIDER_CODE_GENERATION


//
// Allow Diasabling of code generation
//
#ifndef MCGEN_DISABLE_PROVIDER_CODE_GENERATION

//
// Template Functions 
//
//
//Template from manifest : 2StrTemplate
//
#ifndef Template_zz_def
#define Template_zz_def
//ETW_INLINE
ULONG
Template_zz(
    _In_ REGHANDLE RegHandle,
    _In_ PCEVENT_DESCRIPTOR Descriptor,
    _In_opt_ PCWSTR  _Arg0,
    _In_opt_ PCWSTR  _Arg1
    )
{
#define ARGUMENT_COUNT_zz 2

    EVENT_DATA_DESCRIPTOR EventData[ARGUMENT_COUNT_zz];

    EventDataDescCreate(&EventData[0], 
                        (_Arg0 != NULL) ? _Arg0 : L"NULL",
                        (_Arg0 != NULL) ? (ULONG)((wcslen(_Arg0) + 1) * sizeof(WCHAR)) : (ULONG)sizeof(L"NULL"));

    EventDataDescCreate(&EventData[1], 
                        (_Arg1 != NULL) ? _Arg1 : L"NULL",
                        (_Arg1 != NULL) ? (ULONG)((wcslen(_Arg1) + 1) * sizeof(WCHAR)) : (ULONG)sizeof(L"NULL"));

    return EventWrite(RegHandle, Descriptor, ARGUMENT_COUNT_zz, EventData);
}
#endif

#endif // MCGEN_DISABLE_PROVIDER_CODE_GENERATION

#if defined(__cplusplus)
};
#endif

#define MSG_level_Critical                   0x50000001L
#define MSG_level_Error                      0x50000002L
#define MSG_level_Warning                    0x50000003L
#define MSG_level_Informational              0x50000004L
#define MSG_OpenSSH_level_Debug_message      0x50000010L
#define MSG_OpenSSH_event_message            0xB0000001L
