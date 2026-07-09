// ==WindhawkMod==
// @id              disable-async-logoff
// @name            Windows 7 Logoff Sequence
// @description     Bring back Windows 7's logoff sequence, switching to the 'logging off' screen after all apps have been closed
// @version         1.0
// @author          Ingan121
// @github          https://github.com/Ingan121
// @twitter         https://twitter.com/Ingan121
// @homepage        https://www.ingan121.com/
// @include         winlogon.exe
// @architecture    x86-64
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Windows 7 Logoff Sequence
* This mod restores the Windows 7 logoff sequence, where after closing all applications, the system would switch to a 'logging off' screen. In Windows 10 and later, the logoff process is more immediate, and this mod brings back the visual experience of the older logoff sequence.
*/
// ==/WindhawkModReadme==

#include <windhawk_utils.h>

int* p_g_fShutdownResolverDisabled = nullptr;

// void __fastcall ShutdownWindowsWorkerThread(PTP_CALLBACK_INSTANCE Instance, PVOID Context)
typedef void __fastcall (*ShutdownWindowsWorkerThread_t)(void* Instance, void* Context);
ShutdownWindowsWorkerThread_t ShutdownWindowsWorkerThread_original;
void __fastcall ShutdownWindowsWorkerThread_hook(void* Instance, void* Context) {
    if (p_g_fShutdownResolverDisabled) {
        *p_g_fShutdownResolverDisabled = 1; // Disable the async logoff resolver
        Wh_Log(L"ShutdownWindowsWorkerThread_hook: Set g_fShutdownResolverDisabled to 1");
    }
    ShutdownWindowsWorkerThread_original(Instance, Context);
  }

// The mod is being initialized, load settings, hook functions, and do other
// initialization stuff if required.
BOOL Wh_ModInit() {
    Wh_Log(L"Init");

    HMODULE winlogon = GetModuleHandleW(NULL);
    if (winlogon) {
        WindhawkUtils::SYMBOL_HOOK winlogonExeHooks[] = {
            {
                {
                    L"void __cdecl ShutdownWindowsWorkerThread(struct _TP_CALLBACK_INSTANCE *,void *)",
                },
                (void**)&ShutdownWindowsWorkerThread_original,
                (void*)ShutdownWindowsWorkerThread_hook,
                FALSE
            },
            {
                {
                    L"int g_fShutdownResolverDisabled",
                },
                (void**)&p_g_fShutdownResolverDisabled,
                NULL,
                FALSE
            }
        };
        if (!WindhawkUtils::HookSymbols(winlogon, winlogonExeHooks, ARRAYSIZE(winlogonExeHooks))) {
            Wh_Log(L"HookSymbols ShutdownWindowsWorkerThread failed");
            Wh_SetIntValue(L"WinlogonHookFailed", 1);
        } else {
            Wh_SetIntValue(L"WinlogonHookFailed", 0);
        }
    }

    return TRUE;
}

// The mod is being unloaded, free all allocated resources.
void Wh_ModUninit() {
    Wh_Log(L"Uninit"); // Prevent new fades
}