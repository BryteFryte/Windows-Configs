// ==WindhawkMod==
// @id              explorer-nav-pane-classic-expander-margins
// @name            Classic Expander Margins for Explorer Navigation Pane
// @description     Restores the margins used in Windows 7 and 8 for the namespace control tree (navigation pane)
// @version         0.9
// @author          Leymonaide
// @github          https://github.com/Leymonaide
// @twitter         https://twitter.com/Leym0naide
// @homepage        https://leymonaide.github.io/
// @include         *
// @compilerOptions -luser32 -lversion -lcomctl32
// @license         MIT
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Classic Expander Margins for Explorer Navigation Pane

Restores the margins used in Windows 7 and 8 for the namespace control tree (navigation pane) in File Explorer windows.

The old margins had the expander glyph appearing closer to the icon.

| **Before** | **After** |
| :--------- | :-------- |
| ![Before preview](https://raw.githubusercontent.com/Leymonaide/images/refs/heads/main/explorer-nav-pane-classic-expander-margins-before.png) | ![After preview](https://raw.githubusercontent.com/Leymonaide/images/refs/heads/main/explorer-nav-pane-classic-expander-margins-after.png) |

## Credits

- [Aubrey](//github.com/aubymori) and her mod, [Aerexplorer](//windhawk.net/mods/aerexplorer). I lifted some of the signatures
  and logic used for hooks straight from her.
- Nex, Ivan, sakkijarvenpolkkaa, ThatThomasDude (among others) for testing and bug reports.
*/
// ==/WindhawkModReadme==

#include <windhawk_utils.h>

/* Defines */
#ifdef _WIN64
#   define THISCALL  __cdecl
#   define STHISCALL L"__cdecl"

#   define STDCALL  __cdecl
#   define SSTDCALL L"__cdecl"
#else
#   define THISCALL  __thiscall
#   define STHISCALL L"__thiscall"

#   define STDCALL  __stdcall
#   define SSTDCALL L"__stdcall"
#endif

thread_local bool g_creatingNscTreeView = false;
thread_local int g_nscTreeViewSubClassEntryCounter = 0;

using SendMessageW_t = decltype(&SendMessageW);
SendMessageW_t SendMessageW_orig = nullptr;
LRESULT WINAPI SendMessageW_hook(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (g_creatingNscTreeView)
    {
        if (TVM_SETEXTENDEDSTYLE == uMsg)
        {
            // The undocumented extended tree view style 0x1000 controls the additional
            // padding. I removed 0x800 too, because Windows 7 didn't have it.
            DWORD style = (wParam & ~(0x1000 | 0x800));
            style = TVS_EX_DOUBLEBUFFER;
            wParam = lParam = style;
        }
        else if (TVM_SETBORDER == uMsg)
        {
            return 0;
        }
    }

    return SendMessageW_orig(hwnd, uMsg, wParam, lParam);
}

LRESULT (CALLBACK *CNscTree__s_SubClassTreeWndProc_orig)(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) = nullptr;
LRESULT CALLBACK CNscTree__s_SubClassTreeWndProc_hook(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    // Calls this function may nest, so a thread local counter is used
    // instead of a boolean.
    g_nscTreeViewSubClassEntryCounter++;
    LRESULT lr = CNscTree__s_SubClassTreeWndProc_orig(hwnd, uMsg, wParam, lParam, uIdSubclass, dwRefData);
    g_nscTreeViewSubClassEntryCounter--;
    return lr;
}

HWND (THISCALL *CNscTree___CreateTreeView_orig)(void *pThis, HWND hwnd) = nullptr;
HWND THISCALL CNscTree___CreateTreeView_hook(void *pThis, HWND hwnd)
{
    g_creatingNscTreeView = true;
    HWND result = CNscTree___CreateTreeView_orig(pThis, hwnd);
    g_creatingNscTreeView = false;
    return result;
}

const WindhawkUtils::SYMBOL_HOOK explorerframeHooks[] = {
    {
        {
            L"private: struct HWND__ * "
            STHISCALL
            L" CNscTree::_CreateTreeview(struct HWND__ *)"
        },
        &CNscTree___CreateTreeView_orig,
        CNscTree___CreateTreeView_hook,
    },
    {
        {
#ifdef _WIN64
            L"private: static __int64 __cdecl CNscTree::s_SubClassTreeWndProc(struct HWND__ *,unsigned int,unsigned __int64,__int64,unsigned __int64,unsigned __int64)"
#else
            L"private: static long __stdcall CNscTree::s_SubClassTreeWndProc(struct HWND__ *,unsigned int,unsigned int,long,unsigned int,unsigned long)"
#endif
        },
        &CNscTree__s_SubClassTreeWndProc_orig,
        CNscTree__s_SubClassTreeWndProc_hook,
    },
};

/**
 * @brief Hack to push the expander glyph to the right by 1 pixel, which was the
 *        case in Windows 7.
 */
int (FASTCALL *TV_RealDrawPlusMinus_orig)(void *pTree, void *pTreeItem, HDC hdc, int x, int y, int cx, int cy, int idc1, int idc2, int idc3) = nullptr;
int FASTCALL TV_RealDrawPlusMinus_hook(void *pTree, void *pTreeItem, HDC hdc, int x, int y, int cx, int cy, int idc1, int idc2, int idc3)
{
    if (g_nscTreeViewSubClassEntryCounter)
    {
        x += 1;
    }
    return TV_RealDrawPlusMinus_orig(pTree, pTreeItem, hdc, x, y, cx, cy, idc1, idc2, idc3);
}

const WindhawkUtils::SYMBOL_HOOK comctl32Hooks[] = {
    {
        {
            L"int " SSTDCALL " TV_RealDrawPlusMinus(struct _TREE *,struct _TREEITEM *,struct HDC__ *,int,int,int,int,int,int,int)",
        },
        &TV_RealDrawPlusMinus_orig,
        TV_RealDrawPlusMinus_hook,
    },
};

VS_FIXEDFILEINFO* GetModuleVersionInfo(HMODULE hModule, UINT *puPtrLen) 
{ 
    void *pFixedFileInfo = nullptr; 
    UINT uPtrLen = 0; 

    HRSRC hResource = 
        FindResourceW(hModule, MAKEINTRESOURCEW(VS_VERSION_INFO), RT_VERSION); 
    if (hResource)
    { 
        HGLOBAL hGlobal = LoadResource(hModule, hResource); 
        if (hGlobal)
        { 
            void *pData = LockResource(hGlobal); 
            if (pData)
            { 
                if (!VerQueryValueW(pData, L"\\", &pFixedFileInfo, &uPtrLen)
                || uPtrLen == 0)
                { 
                    pFixedFileInfo = nullptr; 
                    uPtrLen = 0; 
                } 
            } 
        } 
    } 

    if (puPtrLen)
    { 
        *puPtrLen = uPtrLen; 
    } 
  
     return (VS_FIXEDFILEINFO *)pFixedFileInfo; 
 } 

/**
  * Loads comctl32.dll, version 6.0.
  * This uses an activation context that uses shell32.dll's manifest
  * to load 6.0, even in apps which don't have the proper manifest for
  * it.
  */
HMODULE LoadComCtlModule(void)
{
    HMODULE hShell32 = LoadLibraryExW(L"shell32.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
    ACTCTXW actCtx = { sizeof(actCtx) };
    actCtx.dwFlags = ACTCTX_FLAG_RESOURCE_NAME_VALID | ACTCTX_FLAG_HMODULE_VALID;
    actCtx.lpResourceName = MAKEINTRESOURCEW(124);
    actCtx.hModule = hShell32;
    HANDLE hActCtx = CreateActCtxW(&actCtx);
    ULONG_PTR ulCookie;
    ActivateActCtx(hActCtx, &ulCookie);
    HMODULE hComCtl = LoadLibraryExW(L"comctl32.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
    /**
      * Certain processes will ignore the activation context and load
      * comctl32.dll 5.82 anyway. If that occurs, just reject it.
      */
    VS_FIXEDFILEINFO *pVerInfo = GetModuleVersionInfo(hComCtl, nullptr);
    if (!pVerInfo || HIWORD(pVerInfo->dwFileVersionMS) < 6)
    {
        FreeLibrary(hComCtl);
        hComCtl = NULL;
    }
    DeactivateActCtx(0, ulCookie);
    ReleaseActCtx(hActCtx);
    FreeLibrary(hShell32);
    return hComCtl;
}

BOOL Wh_ModInit() {
    Wh_Log(L"Init");

    HMODULE hExplorerFrame = LoadLibraryExW(L"ExplorerFrame.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);

    if (!hExplorerFrame)
    {
        Wh_Log(L"Failed to load ExplorerFrame.dll");
        return FALSE;
    }

    HMODULE hComctl32 = LoadComCtlModule();

    if (!hComctl32)
    {
        Wh_Log(L"Failed to load comctl32.dll");
        return FALSE;
    }

    if (!WindhawkUtils::SetFunctionHook(
        (void *)SendMessageW,
        (void *)SendMessageW_hook,
        (void **)&SendMessageW_orig
    ))
    {
        Wh_Log(L"Failed to hook SendMessageW in user32.dll");
        return FALSE;
    }

    if (!WindhawkUtils::HookSymbols(hExplorerFrame, explorerframeHooks, ARRAYSIZE(explorerframeHooks)))
    {
        Wh_Log(L"Failed to hook one or more symbols in ExplorerFrame.dll");
        return FALSE;
    }

    if (!WindhawkUtils::HookSymbols(hComctl32, comctl32Hooks, ARRAYSIZE(comctl32Hooks)))
    {
        Wh_Log(L"Failed to hook one or more symbols in comctl32.dll");
        return FALSE;
    }

    return TRUE;
}

void Wh_ModUninit() {
    Wh_Log(L"Uninit");
}