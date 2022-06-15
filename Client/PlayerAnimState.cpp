#include "stdafx.h"
#include "PlayerAnimState.h"
#include "LifeObj.h"

PlayerAnimState::PlayerAnimState()
{
}


PlayerAnimState::~PlayerAnimState()
{
}

void PlayerAnimState::Initialize(int type, wstring& objKey)
{
	switch (type)
	{
	case HUMAN:
		objKey = L"Human";

		mFrameNum[(size_t)MODE::NEUTRAL][0] = (size_t)HUMAN_FRAME::NEUTRAL;
		mFrameNum[(size_t)MODE::NEUTRAL][1] = 16;
		mFrameNum[(size_t)MODE::WALK][0] = (size_t)HUMAN_FRAME::WALK;
		mFrameNum[(size_t)MODE::WALK][1] = 16;
		mFrameNum[(size_t)MODE::RUN][0] = (size_t)HUMAN_FRAME::RUN;
		mFrameNum[(size_t)MODE::RUN][1] = 16;
		mFrameNum[(size_t)MODE::ATTACK][0] = (size_t)HUMAN_FRAME::ATTACK;
		mFrameNum[(size_t)MODE::ATTACK][1] = 16;
		mFrameNum[(size_t)MODE::GETHIT][0] = (size_t)HUMAN_FRAME::GETHIT;
		mFrameNum[(size_t)MODE::GETHIT][1] = 16;
		mFrameNum[(size_t)MODE::SKILL_ATTACK][0] = (size_t)HUMAN_FRAME::SKILL_ATTACK;
		mFrameNum[(size_t)MODE::SKILL_ATTACK][1] = 16;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][0] = (size_t)HUMAN_FRAME::SPECIAL_CAST;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][1] = 16;
		break;
	case WOLF:
		objKey = L"Wolf";

		mFrameNum[(size_t)MODE::NEUTRAL][0] = (size_t)WOLF_FRAME::NEUTRAL;
		mFrameNum[(size_t)MODE::NEUTRAL][1] = 8;
		mFrameNum[(size_t)MODE::WALK][0] = (size_t)WOLF_FRAME::WALK;
		mFrameNum[(size_t)MODE::WALK][1] = 8;
		mFrameNum[(size_t)MODE::RUN][0] = (size_t)WOLF_FRAME::RUN;
		mFrameNum[(size_t)MODE::RUN][1] = 8;
		mFrameNum[(size_t)MODE::ATTACK][0] = (size_t)WOLF_FRAME::ATTACK;
		mFrameNum[(size_t)MODE::ATTACK][1] = 8;
		mFrameNum[(size_t)MODE::GETHIT][0] = (size_t)WOLF_FRAME::GETHIT;
		mFrameNum[(size_t)MODE::GETHIT][1] = 8;
		mFrameNum[(size_t)MODE::SKILL_ATTACK][0] = (size_t)WOLF_FRAME::SKILL_ATTACK;
		mFrameNum[(size_t)MODE::SKILL_ATTACK][1] = 8;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][0] = (size_t)WOLF_FRAME::SPECIAL_CAST;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][1] = 16;
		mFrameNum[(size_t)MODE::TRANSFORM][0] = (size_t)WOLF_FRAME::TRANSFORM;
		mFrameNum[(size_t)MODE::TRANSFORM][1] = 1;
		break;
	case BEAR:
		objKey = L"Bear";

		mFrameNum[(size_t)MODE::NEUTRAL][0] = (size_t)BEAR_FRAME::NEUTRAL;
		mFrameNum[(size_t)MODE::NEUTRAL][1] = 16;
		mFrameNum[(size_t)MODE::WALK][0] = (size_t)BEAR_FRAME::WALK;
		mFrameNum[(size_t)MODE::WALK][1] = 16;
		mFrameNum[(size_t)MODE::RUN][0] = (size_t)BEAR_FRAME::RUN;
		mFrameNum[(size_t)MODE::RUN][1] = 16;
		mFrameNum[(size_t)MODE::ATTACK][0] = (size_t)BEAR_FRAME::ATTACK;
		mFrameNum[(size_t)MODE::ATTACK][1] = 16;
		mFrameNum[(size_t)MODE::GETHIT][0] = (size_t)BEAR_FRAME::GETHIT;
		mFrameNum[(size_t)MODE::GETHIT][1] = 16;
		mFrameNum[(size_t)MODE::SKILL_ATTACK][0] = (size_t)BEAR_FRAME::SKILL_ATTACK;
		mFrameNum[(size_t)MODE::SKILL_ATTACK][1] = 8;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][0] = (size_t)BEAR_FRAME::SPECIAL_CAST;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][1] = 8;
		mFrameNum[(size_t)MODE::TRANSFORM][0] = (size_t)BEAR_FRAME::TRANSFORM;
		mFrameNum[(size_t)MODE::TRANSFORM][1] = 1;
		break;
	default:
		break;
	}
}

void PlayerAnimState::FrameUpdate(ATTRIBUTE& attribute, FRAME& frame, wstring& stateKey)
{
	if (mFrameNum[(size_t)attribute.mode][1] == 1)
	{
		attribute.frameDir = 0;
	}

	if (attribute.frameDir >= mFrameNum[(size_t)attribute.mode][1])
	{
		attribute.frameDir = 0;
	}

	switch (attribute.mode)
	{
	case MODE::NEUTRAL:
		stateKey = L"Neutral";
		frame = FRAME((float)(attribute.frameDir * mFrameNum[(size_t)MODE::NEUTRAL][0])
			, mFrameNum[(size_t)MODE::NEUTRAL][0] * 1.f
			, (attribute.frameDir * mFrameNum[(size_t)MODE::NEUTRAL][0]) + mFrameNum[(size_t)MODE::NEUTRAL][0]);
		
		frame.dirNum[(size_t)MODE::NEUTRAL] = mFrameNum[(size_t)MODE::NEUTRAL][1];

		break;
	case MODE::WALK:
		stateKey = L"Walk";
		frame = FRAME((float)(attribute.frameDir * mFrameNum[(size_t)MODE::WALK][0])
			, mFrameNum[(size_t)MODE::WALK][0] * 1.5f
			, (attribute.frameDir * mFrameNum[(size_t)MODE::WALK][0]) + mFrameNum[(size_t)MODE::WALK][0]);
		
	
		frame.dirNum[(size_t)MODE::WALK] = mFrameNum[(size_t)MODE::WALK][1];
		break;
	case MODE::RUN:
		stateKey = L"Run";
		frame = FRAME((float)(attribute.frameDir * mFrameNum[(size_t)MODE::RUN][0])
			, mFrameNum[(size_t)MODE::RUN][0] * 1.8f
			, (attribute.frameDir * mFrameNum[(size_t)MODE::RUN][0]) + mFrameNum[(size_t)MODE::RUN][0]);

		frame.dirNum[(size_t)MODE::RUN] = mFrameNum[(size_t)MODE::RUN][1];
		break;

	case MODE::ATTACK:
		stateKey = L"Attack";
		frame = FRAME((float)(attribute.frameDir * mFrameNum[(size_t)MODE::ATTACK][0])
			, mFrameNum[(size_t)MODE::ATTACK][0] * 2.f
			, (attribute.frameDir * mFrameNum[(size_t)MODE::ATTACK][0]) + mFrameNum[(size_t)MODE::ATTACK][0]);

		frame.dirNum[(size_t)MODE::ATTACK] = mFrameNum[(size_t)MODE::ATTACK][1];
		break;
	case MODE::GETHIT:
		stateKey = L"GetHit";
		frame = FRAME((float)(attribute.frameDir * mFrameNum[(size_t)MODE::GETHIT][0])
			, mFrameNum[(size_t)MODE::GETHIT][0] * 2.5f
			, (attribute.frameDir * mFrameNum[(size_t)MODE::GETHIT][0]) + mFrameNum[(size_t)MODE::GETHIT][0]);

		frame.dirNum[(size_t)MODE::GETHIT] = mFrameNum[(size_t)MODE::GETHIT][1];
		break;
	case MODE::SKILL_ATTACK:
		stateKey = L"SkillAttack";
		frame = FRAME((float)(attribute.frameDir * mFrameNum[(size_t)MODE::SKILL_ATTACK][0])
			, mFrameNum[(size_t)MODE::SKILL_ATTACK][0] * 2.f
			, (attribute.frameDir * mFrameNum[(size_t)MODE::SKILL_ATTACK][0]) + mFrameNum[(size_t)MODE::SKILL_ATTACK][0]);

		frame.dirNum[(size_t)MODE::SKILL_ATTACK] = mFrameNum[(size_t)MODE::SKILL_ATTACK][1];
		break;
	case MODE::SPECIAL_CAST:
		stateKey = L"SpecialCast";

		
		frame = FRAME((float)(attribute.frameDir * mFrameNum[(size_t)MODE::SPECIAL_CAST][0])
			, mFrameNum[(size_t)MODE::SPECIAL_CAST][0] * 2.f
			, (attribute.frameDir * mFrameNum[(size_t)MODE::SPECIAL_CAST][0]) + mFrameNum[(size_t)MODE::SPECIAL_CAST][0]);

		if (frame.max > 79)
		{
			int a = 0;
		}
		frame.dirNum[(size_t)MODE::SPECIAL_CAST] = mFrameNum[(size_t)MODE::SPECIAL_CAST][1];
		break;

	case MODE::TRANSFORM:
		stateKey = L"Transform";
		frame = FRAME((float)(attribute.frameDir * mFrameNum[(size_t)MODE::TRANSFORM][0])
			, mFrameNum[(size_t)MODE::TRANSFORM][0] * 1.f
			, (attribute.frameDir * mFrameNum[(size_t)MODE::TRANSFORM][0]) + mFrameNum[(size_t)MODE::TRANSFORM][0]);

		frame.dirNum[(size_t)MODE::TRANSFORM] = mFrameNum[(size_t)MODE::TRANSFORM][1];

		break;
	}
}
