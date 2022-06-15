#include "stdafx.h"
#include "Device.h"


IMPLEMENT_SINGLETON(Device);

Device::Device()
{
}


Device::~Device()
{
	Release();
}

HRESULT Device::InitDevice()
{
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 deviceCaps;
	ZeroMemory(&deviceCaps, sizeof(D3DCAPS9));

	if (FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &deviceCaps)))
	{
		MESSAGE_BOX(L"GetDeviceCpas Failed", L"Device::InitDevice()");
		return E_FAIL;
	}

	DWORD vp;

	if (deviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	vp |= D3DCREATE_MULTITHREADED;


	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	SetParameters(d3dpp);

	if (FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &m_pDevice)))
	{
		MESSAGE_BOX(L"CreateDevice Failed", L"Device::InitDevice()");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		MESSAGE_BOX(L"CreateSprite Failed", L"Device::InitDevice()");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
	{
		MESSAGE_BOX(L"CreateLine Failed", L"Device::InitDevice()");
		return E_FAIL;
	}
	

	D3DXFONT_DESC fontInfo;
	fontInfo.Width = 10;
	fontInfo.Height = 15;
	fontInfo.Weight = FW_NORMAL;
	fontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(fontInfo.FaceName, L"고딕");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &fontInfo, &m_pFont)))
	{
		MESSAGE_BOX(L"Font Create Failed", L"Device::InitDevice()");
		return E_FAIL;
	}


	D3DXFONT_DESC statFontInfo;
	statFontInfo.Width = 8;
	statFontInfo.Height = 10;
	statFontInfo.Weight = FW_NORMAL;
	statFontInfo.CharSet = HANGUL_CHARSET;
	statFontInfo.Italic = false;
	lstrcpy(statFontInfo.FaceName, L"고딕");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &statFontInfo, &m_pStatFont)))
	{
		MESSAGE_BOX(L"Font Create Failed", L"Device::InitDevice()");
		return E_FAIL;
	}


	//D3DXFONT_DESC fontInfo;
	//fontInfo.Width = 10;
	//fontInfo.Height = 15;
	//fontInfo.Weight = FW_NORMAL;
	//fontInfo.CharSet = HANGUL_CHARSET;
	//lstrcpy(fontInfo.FaceName, L"고딕");

	//if (FAILED(D3DXCreateFontIndirect(m_pDevice, &fontInfo, &m_pFont)))
	//{
	//	MESSAGE_BOX(L"Font Create Failed", L"Device::InitDevice()");
	//	return E_FAIL;
	//}

	return S_OK;
}

void Device::SetParameters(D3DPRESENT_PARAMETERS & d3dpp)
{
	d3dpp.BackBufferWidth = WINDOW_WIDTH;
	d3dpp.BackBufferHeight = WINDOW_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = false;

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //즉시 재생 (DEFAULT 는 d3d가 적절한 간격을 조정후 재생한다)

}

void Device::Release()
{
	//ULONG	uRefCnt = m_p3D->Release();
	
	SafeRelease(m_pSprite);
	SafeRelease(m_pDevice);
	SafeRelease(m_p3D);
	SafeRelease(m_pFont);

}
