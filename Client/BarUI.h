#pragma once
#include "UI.h"

class BarUI final : public UI
{
public:
	BarUI();
	virtual ~BarUI();

	// UI을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update(void) override;
	virtual void Render(void) override;
	virtual void Collision(void) override;
	virtual void KeyCheck(void) override;
	virtual void Release(void) override;

private:
	float maxData = 0.f;
	float currentData = 0.f;


private:
	LPD3DXFONT m_pStatFont = nullptr;

};

