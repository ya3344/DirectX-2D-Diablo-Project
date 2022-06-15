#include "stdafx.h"
#include "BarUI.h"
#include "PlayerObserver.h"

BarUI::BarUI()
{
	mStateKey = L"Bar";
	m_pStatFont = Device::GetInstance()->GetStatFont();
}


BarUI::~BarUI()
{
	Release();
}

HRESULT BarUI::Initialize()
{
	m_pObserver = new PlayerObserver;
	SubjectMgr::GetInstance()->Subscribe(m_pObserver);
	SubjectMgr::GetInstance()->Notify(PLAYER_DATA);


	return S_OK;
}

int BarUI::Update(void)
{
	m_pTextureInfo = TextureMgr::GetInstance()->GetTexture(mObjKey, mStateKey, mDrawID);

	switch (mDrawID)
	{
	case HP_BAR:
		maxData = m_pObserver->GetAttribute()->maxHP;
		currentData = m_pObserver->GetAttribute()->currentHP;

		mInfo.centerX = m_pTextureInfo->imgInfo.Width * 0.5f;
		mInfo.centerY = m_pTextureInfo->imgInfo.Height * 1.f;


		mCollisionRect = { 25, 513, 25 + 80, 513 + 80 };
		
		break;
	case MP_BAR:
		maxData = m_pObserver->GetAttribute()->maxMP;
		currentData = m_pObserver->GetAttribute()->currentMP;

		mInfo.centerX = m_pTextureInfo->imgInfo.Width * 0.5f;
		mInfo.centerY = m_pTextureInfo->imgInfo.Height * 1.f;

		mCollisionRect = { 703, 519, 703 + 80, 519 + 80 };
		break;
	case SP_BAR:
		maxData = m_pObserver->GetAttribute()->maxSP;
		currentData = m_pObserver->GetAttribute()->currentSP;

		mInfo.centerX = m_pTextureInfo->imgInfo.Width * 0.f;
		mInfo.centerY = m_pTextureInfo->imgInfo.Height * 0.5f;

		mCollisionRect = { 274, 574, (LONG)(274 + m_pTextureInfo->imgInfo.Width), 
			(LONG)(574 + m_pTextureInfo->imgInfo.Height) };

		break;
	case FRAME_BAR:
		mInfo.centerX = m_pTextureInfo->imgInfo.Width * 0.5f;
		mInfo.centerY = m_pTextureInfo->imgInfo.Height * 0.5f;

		break;
	default:
		break;
	}
	

	if (mDrawID == MP_BAR || mDrawID == HP_BAR)
	{
		scale = currentData / maxData;
		scale -= 1;
		scale *= -1;

		if (scale < 0)
			scale = 0;

		mRect = { 0, (long)m_pTextureInfo->imgInfo.Height, (long)m_pTextureInfo->imgInfo.Width, 
			(long)(m_pTextureInfo->imgInfo.Height * scale) };
	}
	else if (mDrawID == SP_BAR)
	{
		scale = currentData / maxData;

		mRect = { 0, 0, (long)(m_pTextureInfo->imgInfo.Width * scale),
			(long)(m_pTextureInfo->imgInfo.Height) };

	}
	else
	{
		mRect = { 0, 0, (long)m_pTextureInfo->imgInfo.Width,
			(long)(m_pTextureInfo->imgInfo.Height) };
	}


	return OBJ_NORMAL;
}

void BarUI::Render(void)
{
	D3DXMatrixTranslation(&mInfo.matTrans, mInfo.vPos.x, mInfo.vPos.y, mInfo.vPos.z);

	mInfo.matWorld = mInfo.matTrans;
	
	m_pSprite->SetTransform(&mInfo.matWorld);
	m_pSprite->Draw(m_pTextureInfo->pTexture, &mRect, &D3DXVECTOR3(mInfo.centerX, mInfo.centerY, 0.f), nullptr, D3DCOLOR_ARGB(mAlpha, 255, 255, 255));

	Collision();
}



void BarUI::Collision(void)
{
	TCHAR ValueBuf[128] = L"";
	D3DXMatrixIdentity(&mMatFont);

	//if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	//{
	//	cout << "X=" << MathMgr::GetInstance()->GetMouse().x << endl;
	//	cout << "Y=" << MathMgr::GetInstance()->GetMouse().y << endl;
	//}


	if (PtInRect(&mCollisionRect, MathMgr::GetInstance()->GetMouse()))
	{
		if (mDrawID == HP_BAR)
		{
			wsprintf(ValueBuf, L"%d/%d", (int)m_pObserver->GetAttribute()->currentHP,
				(int)m_pObserver->GetAttribute()->maxHP);
		}
		else if (mDrawID == MP_BAR)
		{
			wsprintf(ValueBuf, L"%d/%d", (int)m_pObserver->GetAttribute()->currentMP,
				(int)m_pObserver->GetAttribute()->maxMP);
		}
		else if (mDrawID == SP_BAR)
		{
			wsprintf(ValueBuf, L"%d/%d", (int)m_pObserver->GetAttribute()->currentSP,
				(int)m_pObserver->GetAttribute()->maxSP);
		}

		if (mDrawID == SP_BAR)
		{
			D3DXMatrixTranslation(&mMatFont, mInfo.vPos.x + 15, mInfo.vPos.y - 7, 0.f);
		}
		else
		{
			D3DXMatrixTranslation(&mMatFont, mInfo.vPos.x - 40, mInfo.vPos.y - 130, 0.f);
		}
		
		dynamic_cast<LifeObj*>(m_pPlayer)->SetMoveCheck(false); 

		m_pSprite->SetTransform(&mMatFont);
		m_pStatFont->DrawTextW(m_pSprite
			, ValueBuf, lstrlen(ValueBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		if (PtInRect(&mUIRect, MathMgr::GetInstance()->GetMouse()))
		{
			if (m_bStatDialog)
			{
				dynamic_cast<LifeObj*>(m_pPlayer)->SetMoveCheck(false);
				
			}
			else
			{
				dynamic_cast<LifeObj*>(m_pPlayer)->SetMoveCheck(true);
			}
			
			//cout << "MoveTrue" << endl;
		}
	}
}

void BarUI::Release(void)
{
	SafeDelete<Observer*>(m_pObserver);
}

void BarUI::KeyCheck(void)
{

}
