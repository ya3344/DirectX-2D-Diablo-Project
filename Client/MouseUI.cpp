#include "stdafx.h"
#include "MouseUI.h"


MouseUI::MouseUI()
{
	mStateKey = L"Mouse";
	mFrame = FRAME(0.f, 8.f, 8);
}


MouseUI::~MouseUI()
{
}


HRESULT MouseUI::Initialize()
{
	ShowCursor(false);

	return S_OK;
}

int MouseUI::Update(void)
{
	GetCursorPos(&mPt);
	ScreenToClient(g_hWnd, &mPt);

	mInfo.vPos.x = (float)(mPt.x);
	mInfo.vPos.y = (float)(mPt.y);

	D3DXMatrixTranslation(&mInfo.matTrans, mInfo.vPos.x, mInfo.vPos.y, mInfo.vPos.z);

	KeyCheck();

	return OBJ_NORMAL;
}

void MouseUI::Render(void)
{
	m_pTextureInfo = TextureMgr::GetInstance()->GetTexture(mObjKey, mStateKey,(int)mFrame.frame);

	mInfo.matWorld = mInfo.matTrans;

	m_pSprite->SetTransform(&mInfo.matWorld);
	m_pSprite->Draw(m_pTextureInfo->pTexture, NULL, &D3DXVECTOR3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(mAlpha, 255, 255, 255));

}

void MouseUI::Collision(void)
{
}

void MouseUI::KeyCheck(void)
{
	if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)
	{
		mFrame.frame += mFrame.count * TimeMgr::GetInstance()->GetTime();
		if (mFrame.frame > mFrame.max)
			mFrame.frame = mFrame.frameInit;
	}
	else
	{
		mFrame.frame = 0;
	}
}

void MouseUI::Release(void)
{
}
