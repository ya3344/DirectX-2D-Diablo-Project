#include "stdafx.h"
#include "ScrollMgr.h"
#include "Player.h"

IMPLEMENT_SINGLETON(ScrollMgr);

ScrollMgr::ScrollMgr()
{
	m_vDistance = { 0.f, 0.f, 0.f };
}


ScrollMgr::~ScrollMgr()
{
}

void ScrollMgr::Update()
{

	if (KeyMgr::GetInstance()->KeyDown(KEY_1))
	{
		m_bFreeScroll = !m_bFreeScroll;
	}

	if (m_bFreeScroll)
	{
		FreeScroll();
	}
	else
	{
		//PlayerScroll();
	}
}

void ScrollMgr::SetScrollX(float scrollX)
{
	// Right
	if (m_pPlayer->GetInfo().vPos.x + mScrollX >= (WINDOW_WIDTH * 0.5f))
	{
		mScrollX -= abs(scrollX);

		if (mScrollX <= -1.f * (((TILE_WIDTH * gTileNumX) - WINDOW_WIDTH - (TILE_WIDTH*0.5f))))
			mScrollX = -1.f * (((TILE_WIDTH * gTileNumX) - WINDOW_WIDTH - (TILE_WIDTH*0.5f)));
	}

	// Left
	if (m_pPlayer->GetInfo().vPos.x + mScrollX <= 0 + (WINDOW_WIDTH * 0.5f))
	{
		mScrollX += abs(scrollX);

		if (mScrollX >= 0)
			mScrollX = 0;
	}

}

void ScrollMgr::SetScrollY(float scrollY)
{
	// Up
	if (m_pPlayer->GetInfo().vPos.y + mScrollY <= 0 + (WINDOW_HEIGHT * 0.5f))
	{
		mScrollY += abs(scrollY);

		if (mScrollY >= 0)
			mScrollY = 0;
	}
	// Down
	if (m_pPlayer->GetInfo().vPos.y + mScrollY >= (WINDOW_HEIGHT * 0.5f))
	{
		mScrollY -= abs(scrollY);

		if (mScrollY <= -1.f * ((TILE_HEIGHT * (gTileNumY - (gTileNumY * 0.5f + 1))) - (WINDOW_HEIGHT)))
			mScrollY = -1.f * ((TILE_HEIGHT * (gTileNumY - (gTileNumY * 0.5f + 1))) - (WINDOW_HEIGHT));
	}
}
void ScrollMgr::FreeScroll()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		mScrollX -= 15;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		mScrollX += 15;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		mScrollY += 15;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		mScrollY -= 15;
	}
}

void ScrollMgr::PlayerScroll()
{
	Obj* pPlayer = ObjMgr::GetInstance()->GetObj(OBJ_PLAYER);
	m_vDistance = pPlayer->GetAttribute().vDistance;


	// Right
	if (pPlayer->GetInfo().vPos.x + mScrollX >= (WINDOW_WIDTH / 2))
	{
		mScrollX -= roundf(m_vDistance.x);

		cout << "Right" << endl;

		if (mScrollX <= -1.f * (((TILE_WIDTH * gTileNumX) - WINDOW_WIDTH - (TILE_WIDTH*0.5f))))
		{
			mScrollX = -1.f * (((TILE_WIDTH * gTileNumX) - WINDOW_WIDTH - (TILE_WIDTH*0.5f)));
			cout << "RightLimit" << endl;
		}
	}

	// Up
	if (pPlayer->GetInfo().vPos.y + mScrollY <= 0 + (WINDOW_HEIGHT / 2))
	{
		mScrollY -= roundf(m_vDistance.y);

		if (m_vDistance.y == 0)
		{
			mScrollY += 5;
		}
		
		cout << "Up" << endl;

		if (mScrollY >= 0)
		{
			mScrollY = 0;
			cout << "UpLimit" << endl;
		}
	}

	// Left
	if (pPlayer->GetInfo().vPos.x + mScrollX <= 0 + (WINDOW_WIDTH / 2))
	{
		mScrollX -= roundf(m_vDistance.x);
		cout << "Left" << endl;
		if (mScrollX >= 0)
		{
			mScrollX = 0;
			cout << "LeftLimit" << endl;
		}
	}


	// Down
	if (pPlayer->GetInfo().vPos.y + mScrollY >= (WINDOW_HEIGHT / 2))
	{
		if (m_vDistance.y == 0)
		{
			mScrollY -= 5;
		}

		cout << "Down" << endl;
		mScrollY -= roundf(m_vDistance.y);
	
		// 51
		if (mScrollY <= -1.f * ((TILE_HEIGHT * (gTileNumY - (gTileNumY * 0.5f + 1))) - (WINDOW_HEIGHT)))
		{
			mScrollY = -1.f * ((TILE_HEIGHT * (gTileNumY - (gTileNumY * 0.5f + 1))) - (WINDOW_HEIGHT));
			cout << "DownLimit" << endl;
		}
			
	}
}

void ScrollMgr::PlayerInitPos(const TCHAR * pSceneName, const D3DXVECTOR3 & vPos)
{
	if (vPos == D3DXVECTOR3(0.f, 0.f, 0.f))
	{
		if (pSceneName == L"Village")
		{
			m_pPlayer->SetPos(D3DXVECTOR3(1500.f, 1300.f, 0.f));
		}
		else if (pSceneName == L"Act1")
		{
			m_pPlayer->SetPos(D3DXVECTOR3(1515.f, 1080.f, 0.f)); // act1
		}
		else if (pSceneName == L"Act4")
		{
			m_pPlayer->SetPos(D3DXVECTOR3(653.f, 1779.f, 0.f)); // act1
			//m_pPlayer->SetPos(D3DXVECTOR3(2669.f, 1507.f, 0.f)); // act1
		}
	}
	else
	{
		m_pPlayer->SetPos(vPos); // act1
	}
	

	InitScrollX((-1.f * m_pPlayer->GetInfo().vPos.x) + (WINDOW_WIDTH * 0.5f));
	InitScrollY((-1.f * m_pPlayer->GetInfo().vPos.y) + (WINDOW_HEIGHT * 0.5f));
}
