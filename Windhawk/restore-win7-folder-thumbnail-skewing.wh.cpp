// ==WindhawkMod==
// @id              restore-win7-folder-thumbnail-skewing
// @name            Windows 7 Folder Thumbnail Skewing (Public Alpha 2)
// @description     Makes the generated folder thumbnails in Windows Explorer skew like they did in Windows 7.
// @version         0.2
// @author          Leymonaide
// @github          https://github.com/Leymonaide
// @twitter         https://twitter.com/Leym0naide
// @homepage        https://leymonaide.github.io/
// @include         explorer.exe
// @compilerOptions -lgdi32 -lshlwapi
// @license         MIT
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Unfinished.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- style: win7
  $options:
    - win7: Windows Vista, 7, 8, 8.1
    - win10: Windows 10
  $name: Style
*/
// ==/WindhawkModSettings==

#include <windhawk_utils.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <thumbcache.h>
#include <initguid.h>
#include <wrl.h>
#include <wil/resource.h>
#include <wil/result_macros.h>

using Microsoft::WRL::ComPtr;

bool g_windows10Style = false;

// This IID was {0efcaf11-8cc8-43d9-a525-4bed8991b9c2} in Windows 7.
DEFINE_GUID(IID_IShellItemImageFactoryPriv,
    0x8A322201, 0x0A87, 0x46C1, 0x9C,0x77, 0x76,0x20,0xE0,0xCC,0x5B,0xBC);

// https://github.com/WinExperiments/DirectDesktop/blob/e36609ec2586bb63df4a3fa3108be86b14e6f37b/DirectDesktop/DirectDesktop.cpp#L345-L357
enum WTS_STREAMTYPE
{
    WTSST_UNKNOWN = 0,
    WTSST_JPEG = 1,
    WTSST_BMP = 2,
    WTSST_PNG = 3,
};

enum WTS_THUMBNAILTYPE
{
    WTSTT_IMAGE = 0,
    WTSTT_ICON = 1,
};

// https://github.com/WinExperiments/DirectDesktop/blob/e36609ec2586bb63df4a3fa3108be86b14e6f37b/DirectDesktop/DirectDesktop.cpp#L358-L366
MIDL_INTERFACE("8a322201-0a87-46c1-9c77-7620e0cc5bbc")
IShellItemImageFactoryPriv : IShellItemImageFactory
{
    STDMETHOD(GetSharedBitmap)(SIZE, SIIGBF, ISharedBitmap **) PURE;
    STDMETHOD(GetAdornedBitmap)(SIZE, SIIGBF, ISharedBitmap **) PURE;
    STDMETHOD(GetImageStream)(SIZE, SIIGBF, WTS_STREAMTYPE *, WTS_THUMBNAILTYPE*, WTS_CACHEFLAGS *, SIZE *, REFIID, void **) PURE;
    STDMETHOD(GetImageStreamForRequestedIconSize)(SIZE, SIZE, SIIGBF, UINT64, WTS_STREAMTYPE *, WTS_THUMBNAILTYPE *, WTS_CACHEFLAGS *, SIZE *, REFIID, void **) PURE;
};

HRESULT Create32BitHBITMAP(HDC hdc, SIZE *size, void **ppvBits, HBITMAP *phBitmap)
{
    BITMAPINFO pbmi = { { 0 } };
    *phBitmap = nullptr;

    pbmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbmi.bmiHeader.biWidth = size->cx;
    pbmi.bmiHeader.biHeight = size->cy;
    pbmi.bmiHeader.biCompression = 0;
    pbmi.bmiHeader.biBitCount = 32;
    pbmi.bmiHeader.biPlanes = 1;

    HDC actualHdc = hdc ? hdc : GetDC(HWND_DESKTOP);
    if (actualHdc)
    {
        *phBitmap = CreateDIBSection(actualHdc, &pbmi, 0, ppvBits, 0, 0);
        if (hdc != actualHdc)
        {
            ReleaseDC(HWND_DESKTOP, actualHdc);
        }
    }

    return *phBitmap ? S_OK : E_OUTOFMEMORY;
}

void DIBSectionUtil_MakeOpaque(DWORD dwWidth, DWORD dwHeight, RGBQUAD *pRgbQuad)
{
    DWORD pixelCount;
    BYTE *pCurrentAlphaChannel;

    pixelCount = dwHeight * dwWidth;
    if (0 != pixelCount)
    {
        pCurrentAlphaChannel = &pRgbQuad->rgbReserved;
        DWORD i = pixelCount;
        do
        {
            *pCurrentAlphaChannel = -1;
            pCurrentAlphaChannel += sizeof(RGBQUAD);
            --i;
        }
        while (i);
    }
}

struct SkewInfo
{
    SIZE defaultSize;
    POINT primaryThumbnailPoints[3];
    POINT secondaryThumbnailPoints[3];
};

constexpr SkewInfo kSkewInfo7 = {
    // Default size:
    { 512, 512 },

    // Primary thumbnail parallelogram points:
    {
        { 50, 36 },
        { 394, 116 },
        { 50, 402 },
    },

    // Secondary thumbnail parallelogram points:
    {
        { 50, 36 },
        { 266, 140 },
        { 50, 402 },
    },
};

constexpr SkewInfo kSkewInfo10 = {
    // Default size:
    { 256, 256 },

    // Primary thumbnail parallelogram points:
    {
        { 76, 38 },
        { 207, 56 },
        { 76, 216 },
    },

    // Secondary thumbnail parallelogram points:
    {
        { 60, 38 },
        { 161, 74 },
        { 60, 213 },
    },
};

void ScalePlgPoints(POINT sourcePoints[3], SIZE defaultScale, SIZE currentScale)
{
    sourcePoints[0].x = MulDiv(sourcePoints[0].x, currentScale.cx, defaultScale.cx);
    sourcePoints[0].y = MulDiv(sourcePoints[0].y, currentScale.cy, defaultScale.cy);
    sourcePoints[1].x = MulDiv(sourcePoints[1].x, currentScale.cx, defaultScale.cx);
    sourcePoints[1].y = MulDiv(sourcePoints[1].y, currentScale.cy, defaultScale.cy);
    sourcePoints[2].x = MulDiv(sourcePoints[2].x, currentScale.cx, defaultScale.cx);
    sourcePoints[2].y = MulDiv(sourcePoints[2].y, currentScale.cy, defaultScale.cy);
}

HRESULT CFolderThumbnail___SkewThumbnail(bool isSecondItem,
                                         IShellItem* pShellItem,
                                         HDC hdc,
                                         SIZE targetSize)
{
    RETURN_HR_IF_NULL(E_FAIL, pShellItem);

    ComPtr<IShellItemImageFactoryPriv> pImageFactory = nullptr;
    RETURN_IF_FAILED(pShellItem->QueryInterface(IID_IShellItemImageFactoryPriv, (void **)&pImageFactory));

    HBITMAP hBitmap = nullptr;

    SIZE bmSize = { 256, 256 };
    if (g_windows10Style)
    {
        bmSize = { 254, 254 };
    }

    ComPtr<ISharedBitmap> pSharedBitmap = nullptr;
    RETURN_IF_FAILED(pImageFactory->GetSharedBitmap(
        bmSize, 
        g_windows10Style
            ? SIIGBF_CROPTOSQUARE
            : SIIGBF_RESIZETOFIT, 
        &pSharedBitmap
    ));
    RETURN_IF_FAILED(pSharedBitmap->GetSharedBitmap(&hBitmap));

    BITMAP pv;
    RETURN_LAST_ERROR_IF(0 == GetObjectW(hBitmap, sizeof(pv), &pv));

    SIZE size;
    size.cx = pv.bmWidth + 8;
    size.cy = pv.bmHeight + 8;
    HBITMAP hAlphaBitmap;
    RGBQUAD *dibPixels;
    RETURN_IF_FAILED(Create32BitHBITMAP(hdc, &size, (void**)&dibPixels, &hAlphaBitmap));

    wil::unique_hdc shdcThumbnail(CreateCompatibleDC(hdc));
    RETURN_IF_NULL_ALLOC(shdcThumbnail);

    wil::unique_select_object so(SelectObject(shdcThumbnail.get(), hAlphaBitmap));

    // Draw the rectangle outline around the item thumbnail:
    {
        wil::unique_hpen shPen(CreatePen(
            PS_SOLID, 
            8, 
            g_windows10Style
                ? RGB(183, 183, 183)
                : RGB(204, 204, 204)
        ));
        wil::unique_select_object so(SelectObject(shdcThumbnail.get(), shPen.get()));
        Rectangle(shdcThumbnail.get(), 0, 0, size.cx, size.cy);
    }

    // For the Windows 10 style, draw a white background behind the thumbnail:
    if (g_windows10Style)
    {
        wil::unique_hbrush shBrush(CreateSolidBrush(RGB(247, 247, 247)));
        RECT rc;
        rc.left = 1;
        rc.top = 1;
        rc.right = bmSize.cx - (isSecondItem ? 2 : 1) - 1;
        rc.bottom = bmSize.cy - 1;
        FillRect(shdcThumbnail.get(), &rc, shBrush.get());
    }

    DIBSectionUtil_MakeOpaque(size.cx, size.cy, dibPixels);
    wil::unique_hdc shdcOverlay(CreateCompatibleDC(hdc));

    // Blend function for both of the alpha blends used in this function:
    BLENDFUNCTION bf;
    bf.AlphaFormat = AC_SRC_ALPHA;
    bf.SourceConstantAlpha = 0xFF;
    bf.BlendFlags = 0;
    bf.BlendOp = AC_SRC_OVER;

    // Alpha blend the thumbnail into the main overlay DC:
    {
        wil::unique_select_object so(SelectObject(shdcOverlay.get(), hBitmap));

        // TODO: There's some unique positioning logic that Windows 10 does here
        // that is not replicated.

        GdiAlphaBlend(shdcThumbnail.get(), 4, 4, pv.bmWidth, pv.bmHeight,
                        shdcOverlay.get(), 0, 0, pv.bmWidth, pv.bmHeight,
                        bf);
    }

    const SkewInfo *pSkewInfo = g_windows10Style
        ? &kSkewInfo10
        : &kSkewInfo7;

    POINT plgPoints[3];

    if (isSecondItem)
    {
        memcpy_s(plgPoints, sizeof(plgPoints), pSkewInfo->secondaryThumbnailPoints, sizeof(plgPoints));
    }
    else
    {
        memcpy_s(plgPoints, sizeof(plgPoints), pSkewInfo->primaryThumbnailPoints, sizeof(plgPoints));
    }

    ScalePlgPoints(plgPoints, pSkewInfo->defaultSize, targetSize);

    // Only used by the Windows 7 style:
    int plgXOffset = 0;
    if (!g_windows10Style)
    {
        signed int v19 = size.cx + (isSecondItem ? 0 : -50) - size.cy;
        if ((float)size.cx <= (float)((float)size.cy * 1.1))
        {
            plgXOffset = MulDiv(v19 + 32, targetSize.cx, pSkewInfo->defaultSize.cx);
        }
        else
        {
            plgPoints[0].y = MulDiv(106, targetSize.cx, pSkewInfo->defaultSize.cx);
            plgPoints[1].y = MulDiv(
                (isSecondItem ? 140 : 116) + 70,
                targetSize.cx,
                pSkewInfo->defaultSize.cx
            );
            plgXOffset = MulDiv(
                ((float)v19 * 0.80000001),
                targetSize.cx,
                pSkewInfo->defaultSize.cx
            );
        }
    }

    PlgBlt(hdc, plgPoints, shdcThumbnail.get(), plgXOffset, 0, size.cx - plgXOffset,
            size.cy, 0, 0, 0);

    // Blend the shadow of the second item if there are multiple items:
    if (isSecondItem)
    {
        wil::unique_hmodule shell32(LoadLibraryW(L"shell32.dll"));
        
        if (shell32.is_valid())
        {
            HBITMAP hbmShadow = LoadBitmapW(
                shell32.get(),
                (LPCWSTR)0x137);

            if (hbmShadow)
            {
                if (GetObjectW(hbmShadow, sizeof(pv), &pv))
                {
                    wil::unique_select_object so(SelectObject(shdcOverlay.get(), hbmShadow));
                    GdiAlphaBlend(
                        hdc, plgPoints[1].x, plgPoints[1].y,
                        pv.bmWidth, plgPoints[2].y - plgPoints[0].y, shdcOverlay.get(),
                        0, 0, pv.bmWidth, pv.bmHeight, bf);
                }
            }
        }
    }

    return S_OK;
}

HRESULT (*CFolderThumbnail___SkewThumbnail_orig)(void *pThis, unsigned int a,
    IShellItem *pShellItem, HDC hdc, SIZE size) = nullptr;
HRESULT CFolderThumbnail___SkewThumbnail_hook(void *pThis, unsigned int a,
    IShellItem *pShellItem, HDC hdc, SIZE size)
{
    return CFolderThumbnail___SkewThumbnail(a, pShellItem, hdc, size);
}

HRESULT (*CFolderThumbnail___SkewThumbnail_orig2)(void *pThis, unsigned int a,
    IShellItem *pShellItem, HDC hdc, SIZE size) = nullptr;
HRESULT CFolderThumbnail___SkewThumbnail_hook2(void *pThis, unsigned int a,
    IShellItem *pShellItem, HDC hdc, SIZE size)
{
    return CFolderThumbnail___SkewThumbnail(a, pShellItem, hdc, size);
}

// shell32.dll
WindhawkUtils::SYMBOL_HOOK shell32Hooks[] =
{
    {
        {
            L"private: long __cdecl CFolderThumbnail::_SkewThumbnail(unsigned int,struct IShellItem *,struct HDC__ *,struct tagSIZE)"
        },
        &CFolderThumbnail___SkewThumbnail_orig,
        CFolderThumbnail___SkewThumbnail_hook,
    },
};

// windows.storage.dll (which is mostly just another copy of shell32's code)
WindhawkUtils::SYMBOL_HOOK windowsStorageDllHooks[] =
{
    {
        {
            L"private: long __cdecl CFolderThumbnail::_SkewThumbnail(unsigned int,struct IShellItem *,struct HDC__ *,struct tagSIZE)"
        },
        &CFolderThumbnail___SkewThumbnail_orig2,
        CFolderThumbnail___SkewThumbnail_hook2,
    },
};

void LoadSettings()
{
    auto style = WindhawkUtils::StringSetting::make(L"style");
    g_windows10Style = 0 == StrCmpIW(style, L"win10");
}

// The mod is being initialized, load settings, hook functions, and do other
// initialization stuff if required.
BOOL Wh_ModInit() {
    Wh_Log(L"Init");

    LoadSettings();

    HMODULE shell32 = LoadLibraryW(L"shell32.dll");
    HMODULE windowsStorageDll = LoadLibraryW(L"windows.storage.dll");

    if (!shell32)
    {
        Wh_Log(L"Failed to load shell32.dll.");
        return FALSE;
    }

    if (!WindhawkUtils::HookSymbols(shell32, shell32Hooks, ARRAYSIZE(shell32Hooks)))
    {
        Wh_Log(L"Failed to hook symbols in shell32.dll.");
        return FALSE;
    }

    if (!WindhawkUtils::HookSymbols(windowsStorageDll, windowsStorageDllHooks, ARRAYSIZE(windowsStorageDllHooks)))
    {
        Wh_Log(L"Failed to hook symbols in windows.storage.dll.");
        return FALSE;
    }

    return TRUE;
}

// The mod is being unloaded, free all allocated resources.
void Wh_ModUninit() {
    Wh_Log(L"Uninit");
}

void Wh_ModSettingsChanged()
{
    LoadSettings();
}