#include "stdafx.h"
#include "DebugMgr.h"

IMPLEMENT_SINGLETON(DebugMgr);

DebugMgr::DebugMgr()
{
	D3DXMatrixIdentity(&mFontMatrix);
	m_pSprite = Device::GetInstance()->GetSprite();
	m_pFont = Device::GetInstance()->GetFont();
}


DebugMgr::~DebugMgr()
{
}

void DebugMgr::DebugText(const TCHAR * pFontBuf, D3DXVECTOR3 vPos)
{
	mFontMatrix._41 = vPos.x;
	mFontMatrix._42 = vPos.y;

	m_pSprite->SetTransform(&mFontMatrix);

	m_pFont->DrawTextW(m_pSprite, pFontBuf, lstrlen(pFontBuf), nullptr, 0
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void DebugMgr::DrawRectange(float x, float y, float widht, float height)
{
	if (g_bCollingDraw == false)
		return;

	m_pSprite->End(); //m_pd3dd로 도형을 그리려면 m_pspr으로 그리는 것을 끝내야한다.
	
	Device::GetInstance()->GetDevice()->SetRenderState(D3DRS_ZENABLE, false);
	Device::GetInstance()->GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE );

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	Device::GetInstance()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	Device::GetInstance()->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	Device::GetInstance()->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	Device::GetInstance()->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	RECTANGLE rectangle[4] =
	{
		x - 0.5f, y - 0.5f, 1.f, 1.f, D3DCOLOR_ARGB(150, 255, 0, 0),
		x + widht - 0.5f, y - 0.5f, 1.f, 1.f, D3DCOLOR_ARGB(150, 255, 0, 0),
		x - 0.5f, y + height - 0.5f, 1.f, 1.f, D3DCOLOR_ARGB(150, 255, 0, 0),
		x + widht - 0.5f, y + height - 0.5f, 1.f, 1.f, D3DCOLOR_ARGB(150, 255, 0, 0)
	};

	if (FAILED(Device::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, rectangle, sizeof(RECTANGLE))))
	{
		MESSAGE_BOX(L"Draw Rectangle Error!", L"DebugMgr::DrawRectange");
	}

	m_pSprite->End();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

}
