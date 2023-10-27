#pragma once
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <comdef.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

_COM_SMARTPTR_TYPEDEF(ID2D1Factory, __uuidof(ID2D1Factory));
_COM_SMARTPTR_TYPEDEF(ID2D1RenderTarget, __uuidof(ID2D1RenderTarget));
_COM_SMARTPTR_TYPEDEF(ID2D1HwndRenderTarget, __uuidof(ID2D1HwndRenderTarget));
_COM_SMARTPTR_TYPEDEF(ID2D1SolidColorBrush, __uuidof(ID2D1SolidColorBrush));

_COM_SMARTPTR_TYPEDEF(IDWriteFactory, __uuidof(IDWriteFactory));
_COM_SMARTPTR_TYPEDEF(IDWriteTextFormat, __uuidof(IDWriteTextFormat));
_COM_SMARTPTR_TYPEDEF(IDWriteTextLayout, __uuidof(IDWriteTextLayout));