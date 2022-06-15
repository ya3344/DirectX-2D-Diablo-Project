#pragma once
#include "UI.h"



class SkillUI final : public UI
{
public:
	SkillUI();
	virtual ~SkillUI();

	// UI을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update(void) override;
	virtual void Render(void) override;
	virtual void Collision(void) override;
	virtual void KeyCheck(void) override;
	virtual void Release(void) override;

private:
	void InitIcon();
	void FontDraw();
	void SkillSelect();
	void SkillSlotFont();
	void SkillSlotSelect(const TCHAR* pKeyBuf);

	inline void SkillCheck(int checkDrawID, int drawID);
	inline void SkillAdd(int drawID);
private:
	RECT mCloseRect = {};
	RECT mSkillOpenRect = {};
	RECT mFrameRect[3] = {};
	
	//D3DXVECTOR3 mIconPos[3][10];
	//int mIconDrawID[3][10] = {};

	TCHAR mSkillPointBuf[5] = L"";

private:
	static int gFrameIndex;
	static int gSkillPoint;
	static int gFirstSkillCount;
	static int gSecondSkillCount;
	static int gThirdSkillCount;

private:
	enum SKILL_UI
	{
		FIRST_FRAME = 62,
		SECOND_FRAME,
		THIRD_FRAME,
	};
};

