#pragma once
#include "Observer.h"

class PlayerObserver final : public Observer
{
public:
	PlayerObserver();
	virtual ~PlayerObserver();

public:
	// Observer��(��) ���� ��ӵ�
	virtual void Update(int message, void * pData) override;


};

