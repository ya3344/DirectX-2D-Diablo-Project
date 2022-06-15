#pragma once
#include "UI.h"
class QuestUI final : public UI
{
public:
	QuestUI();
	virtual ~QuestUI();

	// UI을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update(void) override;
	virtual void Render(void) override;
	virtual void Collision(void) override;
	virtual void KeyCheck(void) override;
	virtual void Release(void) override;

private:
	void FrameRender();
	void QuestIconEnemy_Render();
	void QuestIconDia_Render();
	void DrawFont();

private:
	RECT mCloseRect = {};
	RECT mNpcRect = {};

private:
	float mEnemyDrawID = 0.f;
	float mDiaDrawID = 0.f;
};

