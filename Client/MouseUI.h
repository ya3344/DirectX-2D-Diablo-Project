#pragma once
#include "UI.h"
class MouseUI final : public UI
{
public:
	MouseUI();
	virtual ~MouseUI();

	// UI��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update(void) override;
	virtual void Render(void) override;
	virtual void Collision(void) override;
	virtual void KeyCheck(void) override;
	virtual void Release(void) override;

private:
	POINT mPt = {};
};

