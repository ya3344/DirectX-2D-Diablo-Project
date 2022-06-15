#pragma once

#include "Obj.h"

class ObjBridge final : public Obj
{
public:
	ObjBridge();
	virtual ~ObjBridge();

	// Obj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

