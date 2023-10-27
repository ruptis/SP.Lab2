#include "Utils.h"
#include <wincodec.h>
#pragma comment(lib, "windowscodecs.lib")
#include <Windowsx.h>

namespace WinApiWrapper
{
    Point LParam2Point(const LPARAM lParam)
    {
        return {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
    }

    Rect ToRect(const Size& size)
    {
        return {0, 0, size.cx, size.cy};
    }

    float WParam2Float(const WPARAM wParam)
    {
        return static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam)) / WHEEL_DELTA;
    }

    ID2D1Bitmap* LoadImageFromFile(const std::wstring& path, ID2D1RenderTarget& renderTarget)
    {
        ID2D1Bitmap* bmp = nullptr;

        IWICImagingFactory* wicFactory = nullptr;
        HRESULT hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_IWICImagingFactory,
            reinterpret_cast<LPVOID*>(&wicFactory));

        IWICBitmapDecoder* wicDecoder = nullptr;
        hr = wicFactory->CreateDecoderFromFilename(
            path.c_str(),
            nullptr,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &wicDecoder);

        IWICBitmapFrameDecode* wicFrame = nullptr;
        hr = wicDecoder->GetFrame(0, &wicFrame);

        IWICFormatConverter* wicConverter = nullptr;
        hr = wicFactory->CreateFormatConverter(&wicConverter);

        hr = wicConverter->Initialize(
            wicFrame,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            nullptr,
            0.0,
            WICBitmapPaletteTypeCustom);

        renderTarget.CreateBitmapFromWicBitmap(
            wicConverter,
            nullptr,
            &bmp
        );

        if (wicFactory) wicFactory->Release();
        if (wicDecoder) wicDecoder->Release();
        if (wicConverter) wicConverter->Release();
        if (wicFrame) wicFrame->Release();

        return bmp;
    }
}
