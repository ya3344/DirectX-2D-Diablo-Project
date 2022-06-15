#pragma once

class Obj;
class Tile;

#define ROUNDING(x, dig)	( floor((x) * pow(float(10), dig) + 0.5f) / pow(float(10), dig)
class MathMgr
{
	DECLARE_SINGLETON(MathMgr);
private:
	MathMgr();
	~MathMgr();

public:
	float CalDistance(const D3DXVECTOR3& vPos, const D3DXVECTOR3& vTarget);
	float CalDirDegree(const D3DXVECTOR3& vSrcPos, const D3DXVECTOR3& vDestPos);
	float Rounding(float x, int digit);
public:
	D3DXVECTOR3 CalTargetDir(const D3DXVECTOR3& vPos, const D3DXVECTOR3& vTarget);
	D3DXVECTOR3 CalPoint();
	POINT GetMouse();

public:
	D3DXVECTOR3 RandomPos(const D3DXVECTOR3& vPos, float distance = 1.f);
	D3DXVECTOR3 DegreePos(const D3DXVECTOR3& vSrcPos, const D3DXVECTOR3& vDestPos, float distance = 1.f);
	D3DXVECTOR3 Degree360(const D3DXVECTOR3& vSrcPos,  float degree);

public:
	int CalFrame(int dir, float degree);
private:
	enum OBJ_MOTION : size_t
	{
		LEFT = 0,
		LD,
		LU,
		UP,
		RIGHT,
		RU,
		RD,
		DOWN,
		MOTION_END
	};

private:
	size_t mMoveState = MOTION_END;
	D3DXVECTOR3 m_vRandomPos;
	D3DXVECTOR3 m_vDegreePos;
};

