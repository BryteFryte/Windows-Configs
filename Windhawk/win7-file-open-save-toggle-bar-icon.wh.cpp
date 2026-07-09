// ==WindhawkMod==
// @id              win7-file-open-save-toggle-bar-icon
// @name            Windows 7 File Open/Save Toggle Bar Icon
// @description     Restores the bitmap arrow glyph on the "Toggle Folders" button in open/save dialogs.
// @version         1.0
// @author          Leymonaide
// @github          https://github.com/Leymonaide
// @twitter         https://twitter.com/Lem0naide
// @homepage        https://leymonaide.github.io/
// @include         *
// @compilerOptions -lcomdlg32 -lgdi32
// @license         MIT
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Windows 7 File Open/Save Toggle Bar Icon

Restores the bitmap arrow glyph on the "Toggle Folders" button in open/save dialogs.

This glyph was changed to an icon in later versions of Windows. The icon scaling differs, so it wasn't possible to just
make the icon look like the Windows 7 glyph.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- win7_comdlg32_path: C:\path\to\win7\comdlg32.dll
  $name: Path to Windows 7 comdlg32.dll
  $description: The bitmap will be loaded from this DLL.
*/
// ==/WindhawkModSettings==

#include <string>
#include <windhawk_utils.h>

HMODULE g_hmodComdlg32_7 = nullptr;
std::wstring g_spszComdlg32Path;

bool g_fHighDPIAware = false;
bool g_fHighDPI = false;
int g_iLPX = -1;
int g_iLPY = -1;

void InitDPI(void)
{
  int v0; // eax
  HDC DC; // rax
  HDC v3; // rbx
  int DeviceCaps; // eax

  v0 = IsProcessDPIAware();
  if ( g_iLPX == -1 || g_fHighDPIAware != v0 )
  {
    g_fHighDPIAware = v0;
    DC = GetDC(0);
    v3 = DC;
    if ( DC )
    {
      g_iLPX = GetDeviceCaps(DC, 88);
      DeviceCaps = GetDeviceCaps(v3, 90);
      g_fHighDPI = g_iLPX != 96;
      g_iLPY = DeviceCaps;
      ReleaseDC(0, v3);
    }
  }
}

void __fastcall SHLogicalToPhysicalDPI(int *px, int *py)
{
  InitDPI();
  if ( px )
    *px = MulDiv(*px, g_iLPX, 96);
  if ( py )
    *py = MulDiv(*py, g_iLPY, 96);
}

void (__thiscall *CFileOpenSave__ScaleAndSetToggleBarImageListIfNeeded_orig)(class CFileOpenSave *pThis);

class CFileOpenSave
{
public:
    HWND get_hwndToggleBar()
    {
#ifdef _WIN64
        return *(HWND *)((size_t)this + (70 * 8));
#else
        return *(HWND *)((size_t)this + (79 * 4));
#endif
    }

    void ScaleAndSetToggleBarImageListIfNeeded()
    {
        HWND hwndToggleBar = get_hwndToggleBar();

        int buttonHeight = 21;
        SHLogicalToPhysicalDPI(&buttonHeight, nullptr);

        SendMessageW(hwndToggleBar, TB_SETBUTTONSIZE, 0, MAKELPARAM(150, buttonHeight));
        SendMessageW(hwndToggleBar, TB_SETPADDING, 0, MAKELPARAM(0, buttonHeight - 21));
        SendMessageW(hwndToggleBar, TB_SETBITMAPSIZE, 0, MAKELPARAM(18, 21));
        {
            HBITMAP hbmArrow = LoadBitmapW(g_hmodComdlg32_7, (LPCWSTR)0x241);
            Wh_Log(L"hbmArrow down: %p", hbmArrow);
            TBADDBITMAP tbab {
                .hInst = nullptr,
                .nID = (UINT_PTR)hbmArrow,
            };
            SendMessageW(hwndToggleBar, TB_ADDBITMAP, 1, (LPARAM)&tbab);
        }
        {
            HBITMAP hbmArrow = LoadBitmapW(g_hmodComdlg32_7, (LPCWSTR)0x242);
            Wh_Log(L"hbmArrow up: %p", hbmArrow);
            TBADDBITMAP tbab {
                .hInst = nullptr,
                .nID = (UINT_PTR)hbmArrow,
            };
            SendMessageW(hwndToggleBar, TB_ADDBITMAP, 1, (LPARAM)&tbab);
        }
    }
};

void __thiscall CFileOpenSave__ScaleAndSetToggleBarImageListIfNeeded_hook(class CFileOpenSave *pThis)
{
    return pThis->ScaleAndSetToggleBarImageListIfNeeded();
}

// comdlg32.dll
const WindhawkUtils::SYMBOL_HOOK kComdlg32Hooks[] = {
    {
        {
#ifdef _WIN64
            L"protected: void __cdecl CFileOpenSave::ScaleAndSetToggleBarImageListIfNeeded(void)",
#else
            L"protected: void __thiscall CFileOpenSave::ScaleAndSetToggleBarImageListIfNeeded(void)",
#endif
        },
        &CFileOpenSave__ScaleAndSetToggleBarImageListIfNeeded_orig,
        CFileOpenSave__ScaleAndSetToggleBarImageListIfNeeded_hook,
    },
};

void LoadSettings()
{
    g_spszComdlg32Path = WindhawkUtils::StringSetting::make(L"win7_comdlg32_path");
}

// The mod is being initialized, load settings, hook functions, and do other
// initialization stuff if required.
BOOL Wh_ModInit() {
    Wh_Log(L"Init");

    LoadSettings();

    g_hmodComdlg32_7 = LoadLibraryExW(g_spszComdlg32Path.c_str(), nullptr,
        LOAD_LIBRARY_AS_DATAFILE);

    if (!g_hmodComdlg32_7)
    {
        Wh_Log(L"Path to 7 comdlg32 not specified or the module is invalid.");
    }

    HMODULE hmodComdlg32_10 = LoadLibraryExW(L"comdlg32.dll", nullptr,
        LOAD_LIBRARY_SEARCH_SYSTEM32);

    if (!WindhawkUtils::HookSymbols(hmodComdlg32_10, kComdlg32Hooks, ARRAYSIZE(kComdlg32Hooks)))
    {
        Wh_Log(L"Failed to hook symbols in comdlg32.dll.");
    }

    return TRUE;
}

// The mod is being unloaded, free all allocated resources.
void Wh_ModUninit() {
    Wh_Log(L"Uninit");
}

// The mod setting were changed, reload them.
void Wh_ModSettingsChanged() {
    Wh_Log(L"SettingsChanged");

    LoadSettings();
}
