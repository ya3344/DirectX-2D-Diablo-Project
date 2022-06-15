#pragma once
#include "Obj.h"
class Obstacle final : public Obj
{
public:
	Obstacle();
	virtual ~Obstacle();

	// Obj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

private:
	bool mCollisionInit = false;
};


