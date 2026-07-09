// ==WindhawkMod==
// @id              dwm-desktop-wallpaper
// @name            DWM Desktop Wallpaper
// @description     Makes DWM render a custom image in background when Explorer isn't running
// @version         1.0
// @author          Ingan121
// @github          https://github.com/Ingan121
// @twitter         https://twitter.com/Ingan121
// @homepage        https://www.ingan121.com/
// @include         dwm.exe
// @architecture    x86-64
// @compilerOptions -lgdi32 -lgdiplus
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# DWM Desktop Wallpaper
* Makes DWM render a custom image in background when Explorer isn't running
* The wallpaper file must reside in DWM-accessible paths, such as `C:\Windows\Web`. This does not include the `C:\Users` directory. Only background color will be shown if the image cannot be loaded.
* You must also set the wallpaper style (center, fill, etc.) in the mod settings, as DWM cannot access the user's wallpaper style settings in the registry.
* As of now, multi-monitor setups are not fully supported. The image will only be drawn on the primary monitor.
## ⚠ Important usage note ⚠

In order to use this mod, you must allow Windhawk to inject into the **dwm.exe**
system process. To do so, add it to the process inclusion list in the advanced
settings. If you do not do this, it will silently fail to inject.

![Advanced settings screenshot](https://i.imgur.com/LRhREtJ.png)
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- wallpaperstyle: fill
  $name: Wallpaper style
  $name:ko-KR: 배경 화면 스타일
  $options:
    - center: Center
    - tile: Tile
    - stretch: Stretch
    - fit: Fit
    - fill: Fill
    - span: Span
  $options:ko-KR:
    - center: 가운데
    - tile: 바둑판식 배열
    - stretch: 확대
    - fit: 맞춤
    - fill: 채우기
    - span: 스팬
*/
// ==/WindhawkModSettings==

#include <windhawk_utils.h>
#include <wincodec.h>
#include <gdiplus.h>
#include <fstream>
#include <cstdint>

enum WallpaperStyle {
    WP_STYLE_CENTER,
    WP_STYLE_TILE,
    WP_STYLE_STRETCH,
    WP_STYLE_FIT,
    WP_STYLE_FILL,
    WP_STYLE_SPAN
};

HBITMAP g_wpBitmap;
WallpaperStyle g_wpStyle = WP_STYLE_FILL;

void LoadWallpaper()
{
	// Load the wallpaper image
	wchar_t wallpaperPath[MAX_PATH] = { 0 };
    SystemParametersInfoW(SPI_GETDESKWALLPAPER, MAX_PATH, wallpaperPath, 0);

    if (wallpaperPath[0] == NULL) {
        g_wpBitmap = NULL;
        return;
    }

    std::ifstream file(wallpaperPath);
    if (!file.good()) {
        // File doesn't exist or isn't accessible by the DWM user
        g_wpBitmap = NULL;
        return;
    }
    file.close();

	// Try loading as BMP first
	g_wpBitmap = (HBITMAP)LoadImageW(NULL, wallpaperPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (g_wpBitmap) {
		return;
	}

	// Initialize GDI+
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Load the image
	Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile(wallpaperPath);
	if (bitmap && bitmap->GetLastStatus() == Gdiplus::Ok)
	{
		bitmap->GetHBITMAP(NULL, &g_wpBitmap);
	}

	// Cleanup
	delete bitmap;
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

void PaintWallpaper(HDC hdc, RECT rect)
{
    FillRect(hdc, &rect, (HBRUSH)(COLOR_DESKTOP + 1));

    if (!g_wpBitmap) {
        return;
    }

    int primaryMonitorOffsetX = -GetSystemMetrics(SM_XVIRTUALSCREEN);
    int primaryMonitorOffsetY = -GetSystemMetrics(SM_YVIRTUALSCREEN);
    int primaryMonitorWidth = GetSystemMetrics(SM_CXSCREEN);
    int primaryMonitorHeight = GetSystemMetrics(SM_CYSCREEN);

    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, g_wpBitmap);
    BITMAP bm;
    GetObject(g_wpBitmap, sizeof(bm), &bm);
    SetStretchBltMode(hdc, HALFTONE);
    SetBrushOrgEx(hdc, 0, 0, NULL);
    switch (g_wpStyle)
    {
    case WP_STYLE_CENTER:
    {
        int x = primaryMonitorOffsetX + (primaryMonitorWidth - bm.bmWidth) / 2;
        int y = primaryMonitorOffsetY + (primaryMonitorHeight - bm.bmHeight) / 2;
        BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
        break;
    }
    case WP_STYLE_TILE:
    {
        for (int x = 0; x < primaryMonitorWidth; x += bm.bmWidth)
        {
            for (int y = 0; y < primaryMonitorHeight; y += bm.bmHeight)
            {
                BitBlt(hdc, primaryMonitorOffsetX + x, primaryMonitorOffsetY + y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
            }
        }
        break;
    }
    case WP_STYLE_STRETCH:
    {
        StretchBlt(hdc, primaryMonitorOffsetX, primaryMonitorOffsetY, primaryMonitorWidth, primaryMonitorHeight, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
        break;
    }
    case WP_STYLE_FIT:
    {
        if (bm.bmWidth > primaryMonitorWidth || bm.bmHeight > primaryMonitorHeight)
        {
            double ratio = (double)bm.bmWidth / bm.bmHeight;
            int newWidth = primaryMonitorWidth;
            int newHeight = (int)(primaryMonitorWidth / ratio);
            if (newHeight > primaryMonitorHeight)
            {
                newHeight = primaryMonitorHeight;
                newWidth = (int)(primaryMonitorHeight * ratio);
            }
            int x = primaryMonitorOffsetX + (primaryMonitorWidth - newWidth) / 2;
            int y = primaryMonitorOffsetY + (primaryMonitorHeight - newHeight) / 2;
            StretchBlt(hdc, x, y, newWidth, newHeight, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
        }
        else
        {
            int x = primaryMonitorOffsetX + (primaryMonitorWidth - bm.bmWidth) / 2;
            int y = primaryMonitorOffsetY + (primaryMonitorHeight - bm.bmHeight) / 2;
            BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
        }
        break;
    }
    case WP_STYLE_FILL:
    case WP_STYLE_SPAN: // No multi-monitor support yet!
    {
        if (bm.bmWidth < primaryMonitorWidth || bm.bmHeight < primaryMonitorHeight)
        {
            double ratio = (double)bm.bmWidth / bm.bmHeight;
            int newWidth = primaryMonitorWidth;
            int newHeight = (int)(primaryMonitorWidth / ratio);
            if (newHeight < primaryMonitorHeight)
            {
                newHeight = primaryMonitorHeight;
                newWidth = (int)(primaryMonitorHeight * ratio);
            }
            int x = (primaryMonitorWidth - newWidth) / 2;
            int y = (primaryMonitorHeight - newHeight);
            if (g_wpStyle == WP_STYLE_SPAN)
            {
                y /= 2;
            }
            else
            {
                y /= 3; // idk why but Windows does this
            }
            StretchBlt(hdc, primaryMonitorOffsetX + x, primaryMonitorOffsetY + y, newWidth, newHeight, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
        }
        else
        {
            double ratio = (double)bm.bmWidth / bm.bmHeight;
            int newHeight = primaryMonitorHeight;
            int newWidth = (int)(primaryMonitorHeight * ratio);
            if (newWidth < primaryMonitorWidth)
            {
                newWidth = primaryMonitorWidth;
                newHeight = (int)(primaryMonitorWidth / ratio);
            }
            int x = primaryMonitorOffsetX + (primaryMonitorWidth - newWidth) / 2;
            int y = primaryMonitorOffsetY + (primaryMonitorHeight - newHeight);
            if (g_wpStyle == WP_STYLE_SPAN)
            {
                y /= 2;
            }
            else
            {
                y /= 3; // idk why but Windows does this
            }
            StretchBlt(hdc, x, y, newWidth, newHeight, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
        }
        break;
    }
    }
    SelectObject(hdcMem, hbmOld);
    DeleteDC(hdcMem);
}

typedef HRESULT(WINAPI *WICCreateImagingFactory_Proxy_t)(UINT SDKVersion, IWICImagingFactory **ppIImagingFactory);
WICCreateImagingFactory_Proxy_t WICCreateImagingFactory_Proxy;

typedef long(__cdecl *CBitmapSource_Create_t)(IWICBitmap *, struct MARGINS const *, void **);
CBitmapSource_Create_t CBitmapSource_Create;

typedef long(__cdecl *CDrawImageInstruction_Create_t)(void *, RECT const *, void **);
CDrawImageInstruction_Create_t CDrawImageInstruction_Create;

typedef long(__cdecl *CRenderDataVisual_AddInstruction_t)(void *, void *);
CRenderDataVisual_AddInstruction_t CRenderDataVisual_AddInstruction;

typedef long(__cdecl *CDesktopWindowReplacement_AddDrawSolidBackgroundInstructions_t)(void *, unsigned long);
CDesktopWindowReplacement_AddDrawSolidBackgroundInstructions_t CDesktopWindowReplacement_AddDrawSolidBackgroundInstructions_original;
long __cdecl CDesktopWindowReplacement_AddDrawSolidBackgroundInstructions_hook(void *thisptr, unsigned long color) {
    Wh_Log(L"CDesktopWindowReplacement::AddDrawSolidBackgroundInstructions called, color: 0x%08X", color);
    IWICImagingFactory *wicFactory = nullptr;
    HRESULT hr = WICCreateImagingFactory_Proxy(WINCODEC_SDK_VERSION, &wicFactory);
    if (wicFactory) {
        IWICBitmap *bitmap = nullptr;
        
        int vx = GetSystemMetrics(SM_XVIRTUALSCREEN);
        int vy = GetSystemMetrics(SM_YVIRTUALSCREEN);
        int vw = GetSystemMetrics(SM_CXVIRTUALSCREEN);
        int vh = GetSystemMetrics(SM_CYVIRTUALSCREEN);

        HDC hOffscreenDC = CreateCompatibleDC(NULL);

        BITMAPINFO bmi = {};
        bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
        bmi.bmiHeader.biWidth = vw;
        bmi.bmiHeader.biHeight = -vh;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;

        uint32_t* dibPixels = nullptr;
        HBITMAP hbBgImg = (hOffscreenDC) ? CreateDIBSection(hOffscreenDC, &bmi, DIB_RGB_COLORS, reinterpret_cast<void**>(&dibPixels), NULL, 0) : NULL;
        HBITMAP hbmOld = (hbBgImg && hOffscreenDC) ? (HBITMAP)SelectObject(hOffscreenDC, hbBgImg) : NULL;

        if (hbBgImg && hbmOld) {
            RECT paintRect = { 0, 0, vw, vh };
            LoadWallpaper();
            PaintWallpaper(hOffscreenDC, paintRect);

            // OpenGlass hooks CreateBitmapFromHBITMAP to force the premultiplied alpha mode, so make the bitmap appear opaque in that mode.
            if (dibPixels) {
                const size_t pixelCount = static_cast<size_t>(vw) * static_cast<size_t>(vh);
                for (size_t i = 0; i < pixelCount; ++i) {
                    dibPixels[i] |= 0xFF000000u;
                }
            }

            SelectObject(hOffscreenDC, hbmOld);
        }

        if (hOffscreenDC) {
            DeleteDC(hOffscreenDC);
        }

        if (hbBgImg) {
            hr = wicFactory->CreateBitmapFromHBITMAP(hbBgImg, NULL, WICBitmapUsePremultipliedAlpha, &bitmap);
            DeleteObject(hbBgImg);
            if (SUCCEEDED(hr)) {
                void *bitmapSource = nullptr;
                hr = CBitmapSource_Create(bitmap, NULL, &bitmapSource);
                if (SUCCEEDED(hr)) {
                    void *drawImageInstruction = nullptr;
                    RECT rect = { vx, vy, vx + vw, vy + vh };
                    hr = CDrawImageInstruction_Create(bitmapSource, &rect, &drawImageInstruction);
                    if (SUCCEEDED(hr)) {
                        hr = CRenderDataVisual_AddInstruction(thisptr, drawImageInstruction);
                        if (SUCCEEDED(hr)) {
                            Wh_Log(L"OK!, hr=%d", hr);
                            bitmap->Release();
                            wicFactory->Release();
                            // Don't call the original function - that would draw the solid color background which we don't want
                            return 0;
                        } else {
                            Wh_Log(L"CRenderDataVisual::AddInstruction failed: 0x%08X", hr);
                        }
                    } else {
                        Wh_Log(L"CDrawImageInstruction::Create failed: 0x%08X", hr);
                    }
                } else {
                    Wh_Log(L"CBitmapSource::Create failed: 0x%08X", hr);
                }
                bitmap->Release();
            } else {
                Wh_Log(L"CreateBitmapFromHBITMAP failed: 0x%08X", hr);
            }
        } else {
            Wh_Log(L"LoadImageW failed: %d", GetLastError());
        }
        wicFactory->Release();
    } else {
        Wh_Log(L"WIC factory initialization failed: 0x%08X", hr);
    }
    return CDesktopWindowReplacement_AddDrawSolidBackgroundInstructions_original(thisptr, color);
}

void LoadSettings() {
    LPCWSTR wallpaperStyleStr = Wh_GetStringSetting(L"wallpaperstyle");
    if (wcscmp(wallpaperStyleStr, L"center") == 0) {
        g_wpStyle = WP_STYLE_CENTER;
    } else if (wcscmp(wallpaperStyleStr, L"tile") == 0) {
        g_wpStyle = WP_STYLE_TILE;
    } else if (wcscmp(wallpaperStyleStr, L"stretch") == 0) {
        g_wpStyle = WP_STYLE_STRETCH;
    } else if (wcscmp(wallpaperStyleStr, L"fit") == 0) {
        g_wpStyle = WP_STYLE_FIT;
    } else if (wcscmp(wallpaperStyleStr, L"fill") == 0) {
        g_wpStyle = WP_STYLE_FILL;
    } else if (wcscmp(wallpaperStyleStr, L"span") == 0) {
        g_wpStyle = WP_STYLE_SPAN;
    } else {
        g_wpStyle = WP_STYLE_FILL;
    }
    Wh_FreeStringSetting(wallpaperStyleStr);
}

BOOL Wh_ModInit() {
    Wh_Log(L"Init");

    LoadSettings();

    HMODULE hWindowsCodecs = LoadLibraryW(L"windowscodecs.dll");
    WICCreateImagingFactory_Proxy = (WICCreateImagingFactory_Proxy_t)GetProcAddress(hWindowsCodecs, "WICCreateImagingFactory_Proxy");

    HMODULE hUDwmDll = GetModuleHandleW(L"udwm.dll");
    WindhawkUtils::SYMBOL_HOOK udwmDllHooks[] = {
        {
            {
                L"public: static long __cdecl CBitmapSource::Create(struct IWICBitmap *,struct _MARGINS const *,class CBitmapSource * *)"
            },
            (void**)&CBitmapSource_Create,
            NULL,
            FALSE
        },
        {
            {
                L"public: static long __cdecl CDrawImageInstruction::Create(class CBitmapSource *,struct tagRECT const *,class CDrawImageInstruction * *)"
            },
            (void**)&CDrawImageInstruction_Create,
            NULL,
            FALSE
        },
        {
            {
                L"public: long __cdecl CRenderDataVisual::AddInstruction(class CRenderDataInstruction *)"
            },
            (void**)&CRenderDataVisual_AddInstruction,
            NULL,
            FALSE
        },
        {
            {
                L"public: long __cdecl CDesktopWindowReplacement::AddDrawSolidBackgroundInstructions(unsigned long)"
            },
            (void**)&CDesktopWindowReplacement_AddDrawSolidBackgroundInstructions_original,
            (void*)CDesktopWindowReplacement_AddDrawSolidBackgroundInstructions_hook,
            FALSE
        }
    };
    if (!WindhawkUtils::HookSymbols(hUDwmDll, udwmDllHooks, ARRAYSIZE(udwmDllHooks))) {
        Wh_Log(L"HookSymbols failed");
        return FALSE;
    }

    Wh_Log(L"OK");
    return TRUE;
}

void Wh_ModUninit() {
    Wh_Log(L"Uninit");
}

void Wh_ModSettingsChanged() {
    LoadSettings();
}