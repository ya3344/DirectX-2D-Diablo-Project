#pragma once

#include "Obj.h"

class Observer;

class UI : public Obj
{
public:
	UI();
	virtual ~UI();

	// Obj을(를) 통해 상속됨
	virtual HRESULT Initialize() PURE;
	virtual int Update(void) PURE;
	virtual void Render(void) PURE;
	virtual void Collision(void) PURE;
	virtual void KeyCheck(void) PURE;
	virtual void Release(void) PURE;

public:
	void SetType(const int type) { mType = type; }
	int GetType() const { return mType; }
protected:
	Observer* m_pObserver = nullptr;
	wstring mStateKey = L"";

protected:
	float data = 0.f;
	float scale = 0.f;
	int mType = 0;

protected:
	static bool m_bStatDialog;
	static bool m_bQuestDialog;
	static bool m_bSkillDialog;
	static bool m_bSkillIcon;

protected:
	D3DXMATRIX mMatFont;
	RECT mRect = {};
	RECT mCollisionRect = {};
	RECT mUIRect = {};

protected:
	Obj* m_pPlayer = nullptr;
	LPD3DXFONT m_pFont = nullptr;
};

