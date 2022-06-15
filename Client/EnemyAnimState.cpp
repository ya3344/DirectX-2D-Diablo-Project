#include "stdafx.h"
#include "EnemyAnimState.h"


EnemyAnimState::EnemyAnimState()
{
}


EnemyAnimState::~EnemyAnimState()
{
}

void EnemyAnimState::Initialize(int type, wstring& objKey)
{
	switch (type)
	{
	case FALLEN:
		objKey = L"Fallen";

		mFrameNum[(size_t)MODE::ATTACK][0] = (size_t)FALLEN_FRAME::ATTACK;
		mFrameNum[(size_t)MODE::ATTACK][1] = 8;
		mFrameNum[(size_t)MODE::DEATH][0] = (size_t)FALLEN_FRAME::DEATH;
		mFrameNum[(size_t)MODE::DEATH][1] = 1;
		mFrameNum[(size_t)MODE::NEUTRAL][0] = (size_t)FALLEN_FRAME::NEUTRAL;
		mFrameNum[(size_t)MODE::NEUTRAL][1] = 8;
		mFrameNum[(size_t)MODE::REVIVE][0] = (size_t)FALLEN_FRAME::REVIVE;
		mFrameNum[(size_t)MODE::REVIVE][1] = 1;
		mFrameNum[(size_t)MODE::RUN][0] = (size_t)FALLEN_FRAME::RUN;
		mFrameNum[(size_t)MODE::RUN][1] = 8;
		mFrameNum[(size_t)MODE::GETHIT][0] = (size_t)FALLEN_FRAME::GETHIT;
		mFrameNum[(size_t)MODE::GETHIT][1] = 8;
		break;
	case FALLEN_SHAMON:
		objKey = L"FallenShaman";

		mFrameNum[(size_t)MODE::DEATH][0] = (size_t)FALLEN_SHAMAN_FRAME::DEATH;
		mFrameNum[(size_t)MODE::DEATH][1] = 1;
		mFrameNum[(size_t)MODE::GETHIT][0] = (size_t)FALLEN_SHAMAN_FRAME::GETHIT;
		mFrameNum[(size_t)MODE::GETHIT][1] = 8;
		mFrameNum[(size_t)MODE::NEUTRAL][0] = (size_t)FALLEN_SHAMAN_FRAME::NEUTRAL;
		mFrameNum[(size_t)MODE::NEUTRAL][1] = 8;
		mFrameNum[(size_t)MODE::RUN][0] = (size_t)FALLEN_SHAMAN_FRAME::RUN;
		mFrameNum[(size_t)MODE::RUN][1] = 8;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][0] = (size_t)FALLEN_SHAMAN_FRAME::SPECIAL_CAST;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][1] = 8;
		break;
	case COUNCIL:
		objKey = L"Council";

		mFrameNum[(size_t)MODE::ATTACK][0] = (size_t)COUNCIL_FRAME::ATTACK;
		mFrameNum[(size_t)MODE::ATTACK][1] = 8;
		mFrameNum[(size_t)MODE::DEATH][0] = (size_t)COUNCIL_FRAME::DEATH;
		mFrameNum[(size_t)MODE::DEATH][1] = 8;
		mFrameNum[(size_t)MODE::GETHIT][0] = (size_t)COUNCIL_FRAME::GETHIT;
		mFrameNum[(size_t)MODE::GETHIT][1] = 8;
		mFrameNum[(size_t)MODE::NEUTRAL][0] = (size_t)COUNCIL_FRAME::NEUTRAL;
		mFrameNum[(size_t)MODE::NEUTRAL][1] = 8;
		mFrameNum[(size_t)MODE::RUN][0] = (size_t)COUNCIL_FRAME::RUN;
		mFrameNum[(size_t)MODE::RUN][1] = 8;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][0] = (size_t)COUNCIL_FRAME::SPECIAL_CAST;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][1] = 8;
		break;
	case COUNTESS:
		objKey = L"Countess";

		mFrameNum[(size_t)MODE::ATTACK][0] = (size_t)COUNTESS_FRAME::ATTACK;
		mFrameNum[(size_t)MODE::ATTACK][1] = 8;
		mFrameNum[(size_t)MODE::DEATH][0] = (size_t)COUNTESS_FRAME::DEATH;
		mFrameNum[(size_t)MODE::DEATH][1] = 8;
		mFrameNum[(size_t)MODE::GETHIT][0] = (size_t)COUNTESS_FRAME::GETHIT;
		mFrameNum[(size_t)MODE::GETHIT][1] = 8;
		mFrameNum[(size_t)MODE::NEUTRAL][0] = (size_t)COUNTESS_FRAME::NEUTRAL;
		mFrameNum[(size_t)MODE::NEUTRAL][1] = 8;
		mFrameNum[(size_t)MODE::RUN][0] = (size_t)COUNTESS_FRAME::RUN;
		mFrameNum[(size_t)MODE::RUN][1] = 8;
		break;
	case WRAITH:
		objKey = L"Wraith";

		mFrameNum[(size_t)MODE::ATTACK][0] = (size_t)WRAITH_FRAME::ATTACK;
		mFrameNum[(size_t)MODE::ATTACK][1] = 8;
		mFrameNum[(size_t)MODE::DEATH][0] = (size_t)WRAITH_FRAME::DEATH;
		mFrameNum[(size_t)MODE::DEATH][1] = 8;
		mFrameNum[(size_t)MODE::GETHIT][0] = (size_t)WRAITH_FRAME::GETHIT;
		mFrameNum[(size_t)MODE::GETHIT][1] = 8;
		mFrameNum[(size_t)MODE::NEUTRAL][0] = (size_t)WRAITH_FRAME::NEUTRAL;
		mFrameNum[(size_t)MODE::NEUTRAL][1] = 8;
		mFrameNum[(size_t)MODE::RUN][0] = (size_t)WRAITH_FRAME::RUN;
		mFrameNum[(size_t)MODE::RUN][1] = 8;
		break;
	case DEMON:
		objKey = L"Demon";

		mFrameNum[(size_t)MODE::ATTACK][0] = (size_t)DEMON_FRAME::ATTACK;
		mFrameNum[(size_t)MODE::ATTACK][1] = 8;
		mFrameNum[(size_t)MODE::DEATH][0] = (size_t)DEMON_FRAME::DEATH;
		mFrameNum[(size_t)MODE::DEATH][1] = 8;
		mFrameNum[(size_t)MODE::GETHIT][0] = (size_t)DEMON_FRAME::GETHIT;
		mFrameNum[(size_t)MODE::GETHIT][1] = 8;
		mFrameNum[(size_t)MODE::NEUTRAL][0] = (size_t)DEMON_FRAME::NEUTRAL;
		mFrameNum[(size_t)MODE::NEUTRAL][1] = 8;
		mFrameNum[(size_t)MODE::RUN][0] = (size_t)DEMON_FRAME::RUN;
		mFrameNum[(size_t)MODE::RUN][1] = 8;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][0] = (size_t)DEMON_FRAME::SPECIAL_CAST;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][1] = 8;
		break;
	case ANIMAL:
		objKey = L"Animal";

		mFrameNum[(size_t)MODE::ATTACK][0] = (size_t)ANIMAL_FRAME::ATTACK;
		mFrameNum[(size_t)MODE::ATTACK][1] = 8;
		mFrameNum[(size_t)MODE::DEATH][0] = (size_t)ANIMAL_FRAME::DEATH;
		mFrameNum[(size_t)MODE::DEATH][1] = 8;
		mFrameNum[(size_t)MODE::GETHIT][0] = (size_t)ANIMAL_FRAME::GETHIT;
		mFrameNum[(size_t)MODE::GETHIT][1] = 8;
		mFrameNum[(size_t)MODE::NEUTRAL][0] = (size_t)ANIMAL_FRAME::NEUTRAL;
		mFrameNum[(size_t)MODE::NEUTRAL][1] = 8;
		mFrameNum[(size_t)MODE::RUN][0] = (size_t)ANIMAL_FRAME::RUN;
		mFrameNum[(size_t)MODE::RUN][1] = 16;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][0] = (size_t)ANIMAL_FRAME::SPECIAL_CAST;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][1] = 8;
		break;
	case DIABLO:
		objKey = L"Diablo";

		mFrameNum[(size_t)MODE::ATTACK][0] = (size_t)DIABLO_FRAME::ATTACK;
		mFrameNum[(size_t)MODE::ATTACK][1] = 8;

		mFrameNum[(size_t)MODE::DEATH][0] = (size_t)DIABLO_FRAME::DEATH;
		mFrameNum[(size_t)MODE::DEATH][1] = 1;

		mFrameNum[(size_t)MODE::FIRE_CAST][0] = (size_t)DIABLO_FRAME::FIRE_CAST;
		mFrameNum[(size_t)MODE::FIRE_CAST][1] = 8;

		mFrameNum[(size_t)MODE::GETHIT][0] = (size_t)DIABLO_FRAME::GETHIT;
		mFrameNum[(size_t)MODE::GETHIT][1] = 8;

		mFrameNum[(size_t)MODE::NEUTRAL][0] = (size_t)DIABLO_FRAME::NEUTRAL;
		mFrameNum[(size_t)MODE::NEUTRAL][1] = 8;

		mFrameNum[(size_t)MODE::SPECIAL][0] = (size_t)DIABLO_FRAME::SPECIAL;
		mFrameNum[(size_t)MODE::SPECIAL][1] = 8;

		mFrameNum[(size_t)MODE::RUN][0] = (size_t)DIABLO_FRAME::RUN;
		mFrameNum[(size_t)MODE::RUN][1] = 8;

		mFrameNum[(size_t)MODE::SPECIAL_CAST][0] = (size_t)DIABLO_FRAME::SPECIAL_CAST;
		mFrameNum[(size_t)MODE::SPECIAL_CAST][1] = 8;

		mFrameNum[(size_t)MODE::WALK][0] = (size_t)DIABLO_FRAME::WALK;
		mFrameNum[(size_t)MODE::WALK][1] = 8;
		break;
	default:
		break;
	}
}

void EnemyAnimState::FrameUpdate(ATTRIBUTE & attribute, FRAME & frame, wstring & stateKey)
{
	float dieCount = 0.f;

	if (mFrameNum[(size_t)attribute.mode][1] == 1)
	{
		attribute.frameDir = 0;
	}

	if (attribute.frameDir >= mFrameNum[(size_t)attribute.mode][1])
	{
		attribute.frameDir = 0;
		cout << "frame Error" << endl;
	}

	if (attribute.type == DIABLO)
	{
		dieCount = 0.1f;
	}
	else
	{
		dieCount = 0.5f;
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
			, mFrameNum[(size_t)MODE::RUN][0] * 1.7f
			, (attribute.frameDir * mFrameNum[(size_t)MODE::RUN][0]) + mFrameNum[(size_t)MODE::RUN][0]);

		frame.dirNum[(size_t)MODE::RUN] = mFrameNum[(size_t)MODE::RUN][1];

		frame.dirNum[(size_t)MODE::FIRE_CAST] = mFrameNum[(size_t)MODE::FIRE_CAST][1];
		break;

	case MODE::ATTACK:
		stateKey = L"Attack";
		frame = FRAME((float)(attribute.frameDir * mFrameNum[(size_t)MODE::ATTACK][0])
			, mFrameNum[(size_t)MODE::ATTACK][0] * 1.5f
			, (attribute.frameDir * mFrameNum[(size_t)MODE::ATTACK][0]) + mFrameNum[(size_t)MODE::ATTACK][0]);

		frame.dirNum[(size_t)MODE::ATTACK] = mFrameNum[(size_t)MODE::ATTACK][1];

		frame.dirNum[(size_t)MODE::FIRE_CAST] = mFrameNum[(size_t)MODE::FIRE_CAST][1];
		break;

	case MODE::GETHIT:
		stateKey = L"GetHit";
		frame = FRAME((float)(attribute.frameDir * mFrameNum[(size_t)MODE::GETHIT][0])
			, mFrameNum[(size_t)MODE::GETHIT][0] * 2.5f
			, (attribute.frameDir * mFrameNum[(size_t)MODE::GETHIT][0]) + mFrameNum[(size_t)MODE::GETHIT][0]);

		frame.dirNum[(size_t)MODE::GETHIT] = mFrameNum[(size_t)MODE::GETHIT][1];
		break;

	case MODE::SPECIAL_CAST:
		stateKey = L"SpecialCast";
		frame = FRAME((float)(attribute.frameDir * mFrameNum[(size_t)MODE::SPECIAL_CAST][0])
			, mFrameNum[(size_t)MODE::SPECIAL_CAST][0] * 1.f
			, (attribute.frameDir * mFrameNum[(size_t)MODE::SPECIAL_CAST][0]) + mFrameNum[(size_t)MODE::SPECIAL_CAST][0]);

		frame.dirNum[(size_t)MODE::SPECIAL_CAST] = mFrameNum[(size_t)MODE::SPECIAL_CAST][1];
		break;

	case MODE::SPECIAL:
		stateKey = L"Special";
		frame = FRAME((float)(attribute.frameDir * mFrameNum[(size_t)MODE::SPECIAL][0])
			, mFrameNum[(size_t)MODE::SPECIAL][0] * 1.f
			, (attribute.frameDir * mFrameNum[(size_t)MODE::SPECIAL][0]) + mFrameNum[(size_t)MODE::SPECIAL][0]);

		frame.dirNum[(size_t)MODE::SPECIAL] = mFrameNum[(size_t)MODE::SPECIAL][1];
		break;

	case MODE::FIRE_CAST:
		stateKey = L"FireCast";
		frame = FRAME((float)(attribute.frameDir * mFrameNum[(size_t)MODE::FIRE_CAST][0])
			, mFrameNum[(size_t)MODE::FIRE_CAST][0] * 1.f
			, (attribute.frameDir * mFrameNum[(size_t)MODE::FIRE_CAST][0]) + mFrameNum[(size_t)MODE::FIRE_CAST][0]);

		frame.dirNum[(size_t)MODE::FIRE_CAST] = mFrameNum[(size_t)MODE::FIRE_CAST][1];
		break;

	case MODE::DEATH:
		stateKey = L"Death";
		frame = FRAME((float)(attribute.frameDir * mFrameNum[(size_t)MODE::DEATH][0])
			, mFrameNum[(size_t)MODE::DEATH][0] * dieCount
			, (attribute.frameDir * mFrameNum[(size_t)MODE::DEATH][0]) + mFrameNum[(size_t)MODE::DEATH][0]);

		frame.dirNum[(size_t)MODE::DEATH] = mFrameNum[(size_t)MODE::DEATH][1];
		break;
	}
}
