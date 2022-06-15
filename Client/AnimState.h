#pragma once

class LifeObj;

class AnimState abstract
{
public:
	AnimState();
	virtual ~AnimState();

public:
	virtual void Initialize(int type, wstring& objKey) PURE;
	virtual void FrameUpdate(ATTRIBUTE& attribute, FRAME& frame , wstring& stateKey ) PURE;

protected:
	int mFrameNum[(size_t)MODE::END][2] = {};
};

