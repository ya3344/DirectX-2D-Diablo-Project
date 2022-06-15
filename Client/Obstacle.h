#pragma once
#include "Obj.h"
class Obstacle final : public Obj
{
public:
	Obstacle();
	virtual ~Obstacle();

	// Obj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

private:
	bool mCollisionInit = false;
};


