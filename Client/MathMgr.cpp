#include "stdafx.h"
#include "Obj.h"
#include "MathMgr.h"

IMPLEMENT_SINGLETON(MathMgr);

MathMgr::MathMgr()
{
	m_vRandomPos = { 0.f, 0.f, 0.f };
	m_vDegreePos = { 0.f, 0.f, 0.f };
}


MathMgr::~MathMgr()
{
}

float MathMgr::CalDistance(const D3DXVECTOR3& vPos, const D3DXVECTOR3& vTarget)
{
	D3DXVECTOR3 targetDir = vTarget - vPos;
	float distance = D3DXVec3Length(&targetDir);

	return distance;
}

float MathMgr::CalDirDegree(const D3DXVECTOR3 & vSrcPos, const D3DXVECTOR3 & vDestPos)
{
	float width = vDestPos.x - vSrcPos.x;
	float height = vDestPos.y - vSrcPos.y;
	float distance = sqrt((width * width) + (height * height));

	float radian = acosf(width / distance);

	// 180도 이후값 각도 보정 acos 0~180도 까지
	if (vDestPos.y > vSrcPos.y)
	{
		//cout << "각도보정" << endl;
		radian *= -1.f;
	}

	float degree = D3DXToDegree(radian);

	if (degree < 0.f)
		degree += 360.f;

	if (degree >= 360.f)
		degree = 0.f;

	degree = roundf(degree);

	return degree;
}

float MathMgr::Rounding(float x, int digit)
{
	return (floor((x)* pow(float(10), digit) + 0.5f) / pow(float(10), digit));
}

D3DXVECTOR3 MathMgr::CalTargetDir(const D3DXVECTOR3& vPos, const D3DXVECTOR3& vTarget)
{
	D3DXVECTOR3 targetDir = vTarget - vPos;
	float distance = D3DXVec3Length(&targetDir);

	D3DXVec3Normalize(&targetDir, &targetDir);

	return targetDir;
}

D3DXVECTOR3 MathMgr::CalPoint()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	float scrollX = ScrollMgr::GetInstance()->GetScrollX();
	float scrollY = ScrollMgr::GetInstance()->GetScrollY();

	float X = (float)((pt.x - scrollX));
	float Y = (float)((pt.y - scrollY));

	D3DXVECTOR3 target = { X, Y, 0.f };

	return target;
}

POINT MathMgr::GetMouse()
{
	POINT	pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return pt;
}

D3DXVECTOR3 MathMgr::RandomPos(const D3DXVECTOR3 & vPos, float distance)
{
	mMoveState = ((rand() % OBJ_MOTION::MOTION_END));

	switch (mMoveState)
	{
	case OBJ_MOTION::DOWN:
		m_vRandomPos.x = vPos.x;
		m_vRandomPos.y = vPos.y + (40 * distance);
		break;
	case OBJ_MOTION::LD:
		m_vRandomPos.y = vPos.y + (40 * distance);
		m_vRandomPos.x = vPos.x - (80 * distance);
		break;
	case OBJ_MOTION::LEFT:
		m_vRandomPos.x = vPos.x - (80 * distance);
		m_vRandomPos.y = vPos.y;
		break;
	case OBJ_MOTION::LU:
		m_vRandomPos.y = vPos.y - (40 * distance);
		m_vRandomPos.x = vPos.x - (80 * distance);
		break;
	case OBJ_MOTION::RD:
		m_vRandomPos.y = vPos.y + (40 * distance);
		m_vRandomPos.x = vPos.x + (80 * distance);
		break;
	case OBJ_MOTION::RIGHT:
		m_vRandomPos.x = vPos.x + (80 * distance);
		m_vRandomPos.y = vPos.y;
		break;
	case OBJ_MOTION::RU:
		m_vRandomPos.y = vPos.y - (40 * distance);
		m_vRandomPos.x = vPos.x + (80 * distance);
		break;
	case OBJ_MOTION::UP:
		m_vRandomPos.x = vPos.x;
		m_vRandomPos.y = vPos.y - (40 * distance);
		break;
	default:
		break;
	}

	return m_vRandomPos;
}

D3DXVECTOR3 MathMgr::DegreePos(const D3DXVECTOR3& vSrcPos, const D3DXVECTOR3& vDestPos, float distance)
{
	float degree = CalDirDegree(vSrcPos, vDestPos);
	int randDegree = (rand() % (int)60);
	int randDir = (rand() % 2);

	if (randDir == 1)
	{
		degree += randDegree;
	}
	else
	{
		degree -= randDegree;
	}
	
	
	m_vDegreePos.x = vSrcPos.x + cosf(D3DXToRadian(degree)) * distance * 100.f;
	m_vDegreePos.y = vSrcPos.y - sinf(D3DXToRadian(degree)) * distance * 100.f;

	return m_vDegreePos;
}

D3DXVECTOR3 MathMgr::Degree360(const D3DXVECTOR3& vSrcPos, float degree)
{
	m_vDegreePos.x = vSrcPos.x + cosf(D3DXToRadian(degree))  * 100.f;
	m_vDegreePos.y = vSrcPos.y - sinf(D3DXToRadian(degree))  * 100.f;

	return m_vDegreePos;
}

int MathMgr::CalFrame(int dir, float degree)
{
	int calDir = 0;

	// 반대방향으로 돌린다.
	calDir = (int)(dir - (degree / (360.f / dir)));


	// 오른쪽기준을 아래쪽기준으로 바꾼다.
	if (dir == 16)
		calDir += 12;
	else
		calDir += 6;

	calDir %= dir;

	return calDir;
}

