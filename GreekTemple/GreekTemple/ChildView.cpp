/**
 *
 * Greek Temple
 *
 * MIT License
 *
 * Copyright (c) 2023 Retro Technique
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "pch.h"
#include "framework.h"
#include "GreekTemple.h"
#include "ChildView.h"
#include "Constants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma region Constructors

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}

#pragma endregion
#pragma region Overridables

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
	{
		return FALSE;
	}

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

#pragma endregion
#pragma region Messages

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CChildView::OnPaint()
{
	CPaintDC dc(this);

	// TODO: ajoutez ici le code de votre gestionnaire de messages
	MakeCurrent(&dc);

	ClearColor({ 32, 32, 32 });
	Clear();

	Flush();
	::SwapBuffers(dc);

	UnmakeCurrent();
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRenderWindow::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	static constexpr const struct
	{
		LPCTSTR lpszFileName;
		UINT	uID;
		INT		nLevels;

	} TEXTURES[] = 
	{
		{ _T("C:\\Users\\olivi\\Downloads\\Moteur3Db\\textures\\herbe0.png"), ETextureID_Grass, 0 },
		{ _T("C:\\Users\\olivi\\Downloads\\Moteur3Db\\textures\\herbe1.png"), ETextureID_Grass, 1 },
		{ _T("C:\\Users\\olivi\\Downloads\\Moteur3Db\\textures\\herbe2.png"), ETextureID_Grass, 2 },
		{ _T("C:\\Users\\olivi\\Downloads\\Moteur3Db\\textures\\herbe3.png"), ETextureID_Grass, 3 },
		{ _T("C:\\Users\\olivi\\Downloads\\Moteur3Db\\textures\\ciel.png"), ETextureID_Sky, 0 },
		{ _T("C:\\Users\\olivi\\Downloads\\Moteur3Db\\textures\\caillou.png"), ETextureID_Pebble, 0 },
		{ _T("C:\\Users\\olivi\\Downloads\\Moteur3Db\\textures\\pierres.png"), ETextureID_Stone, 0 },
		{ _T("C:\\Users\\olivi\\Downloads\\Moteur3Db\\textures\\lattes.png"), ETextureID_Slat, 0 },
		{ _T("C:\\Users\\olivi\\Downloads\\Moteur3Db\\textures\\marbre0.png"), ETextureID_Marble, 0 },
		{ _T("C:\\Users\\olivi\\Downloads\\Moteur3Db\\textures\\marbre1.png"), ETextureID_Marble, 1 },
		{ _T("C:\\Users\\olivi\\Downloads\\Moteur3Db\\textures\\marbre2.png"), ETextureID_Marble, 2 },
		{ _T("C:\\Users\\olivi\\Downloads\\Moteur3Db\\textures\\marbre3.png"), ETextureID_Marble, 3 },
		{ _T("C:\\Users\\olivi\\Downloads\\Moteur3Db\\textures\\water.png"), ETextureID_Water, 0 }
	};
	static constexpr const UINT TEXTURE_COUNT = ARRAYSIZE(TEXTURES);

	for (UINT i = 0; i < TEXTURE_COUNT; i++)
	{
		LoadTextureToGPU(TEXTURES[i].lpszFileName, TEXTURES[i].uID, TEXTURES[i].nLevels);
	}

	return 0;
}

void CChildView::OnDestroy()
{
	CRenderWindow::OnDestroy();
}

#pragma endregion
#pragma region Implementations

HRESULT CChildView::LoadTextureToGPU(LPCTSTR lpszFileName, UINT uID, INT nLevels)
{
	ASSERT(lpszFileName);

	IWICBitmap* pBitmap = NULL;
	HRESULT hr = LoadTextureFromFile(lpszFileName, &pBitmap);
	if (FAILED(hr))
	{
		return hr;
	}

	UINT uImgHeight = 0;
	UINT uImgWidth = 0;
	hr = pBitmap->GetSize(&uImgWidth, &uImgHeight);
	if (FAILED(hr))
	{
		return hr;
	}

	IWICBitmapLock* pLock = NULL;
	hr = pBitmap->Lock(NULL, WICBitmapLockRead, &pLock);
	if (FAILED(hr))
	{
		return hr;
	}

	UINT uBufferSize = 0;
	BYTE* pBytes = NULL;
	hr = pLock->GetDataPointer(&uBufferSize, &pBytes);
	if (FAILED(hr))
	{
		return NULL;
	}

	MakeCurrent(GetDC());

	Enable(retro::gl::EFeatureType_Texture_2D);
	BindTexture(retro::gl::ETextureType_2D, uID);
	TexParameteri(retro::gl::ETextureType_2D, retro::gl::ETextureParameter_Wrap_S, 0x2901);
	TexParameteri(retro::gl::ETextureType_2D, retro::gl::ETextureParameter_Wrap_T, 0x2901);
	TexParameteri(retro::gl::ETextureType_2D, retro::gl::ETextureParameter_Mag_Filter, 0x2600);
	TexParameteri(retro::gl::ETextureType_2D, retro::gl::ETextureParameter_Min_Filter, 0x2600);
	//TexEnvf
	TexImage2D(nLevels, 4, retro::core::TVector2i(retro::core::TVector2u(uImgWidth, uImgHeight)), 0, retro::gl::EFormatType_RGBA, retro::gl::EDataType_Unsigned_Byte, pBytes);
	Disable(retro::gl::EFeatureType_Texture_2D);

	UnmakeCurrent();

	if (pBitmap)
	{
		pBitmap->Release();
		pBitmap = NULL;
	}

	return S_OK;
}

HRESULT CChildView::LoadTextureFromFile(LPCTSTR lpszFileName, IWICBitmap** ppBitmap) const
{
	ASSERT(lpszFileName);

	IWICImagingFactory* pFactory = theApp.GetWICFactory();
	ASSERT(pFactory);

	HRESULT hr = S_OK;
	IWICStream* pStream = NULL;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pFrame = NULL;
	IWICFormatConverter* pConverterFrame = NULL;

	do
	{
		hr = pFactory->CreateStream(&pStream);
		if (FAILED(hr))
		{
			break;
		}

		hr = pStream->InitializeFromFilename(lpszFileName, GENERIC_READ);
		if (FAILED(hr))
		{
			break;
		}

		hr = pFactory->CreateDecoderFromFilename(lpszFileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
		if (FAILED(hr))
		{
			break;
		}

		hr = pDecoder->GetFrame(0, &pFrame);
		if (FAILED(hr))
		{
			break;
		}

		hr = pFactory->CreateFormatConverter(&pConverterFrame);
		if (FAILED(hr))
		{
			break;
		}

		hr = pConverterFrame->Initialize(pFrame,
			GUID_WICPixelFormat32bppRGBA,
			WICBitmapDitherTypeNone,
			NULL,
			0.,
			WICBitmapPaletteTypeCustom);
		if (FAILED(hr))
		{
			break;
		}

		hr = pFactory->CreateBitmapFromSource(pConverterFrame, WICBitmapCacheOnDemand, ppBitmap);
		if (FAILED(hr))
		{
			break;
		}

	} while (RETRO_NULL_WHILE_LOOP_CONDITION);

	if (pConverterFrame)
	{
		pConverterFrame->Release();
		pConverterFrame = NULL;
	}

	if (pFrame)
	{
		pFrame->Release();
		pFrame = NULL;
	}

	if (pDecoder)
	{
		pDecoder->Release();
		pDecoder = NULL;
	}

	if (pStream)
	{
		pStream->Release();
		pStream = NULL;
	}

	return hr;
}

#pragma endregion