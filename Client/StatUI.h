#pragma once
#include "UI.h"

class StatUI final : public UI
{
public:
	StatUI();
	virtual ~StatUI();

	// UI을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update(void) override;
	virtual void Render(void) override;
	virtual void Collision(void) override;
	virtual void KeyCheck(void) override;
	virtual void Release(void) override;

private:
	void DialogFont();

private:
	LPD3DXFONT m_pStatFont = nullptr;

};

