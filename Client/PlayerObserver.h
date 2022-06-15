#pragma once
#include "Observer.h"

class PlayerObserver final : public Observer
{
public:
	PlayerObserver();
	virtual ~PlayerObserver();

public:
	// Observer을(를) 통해 상속됨
	virtual void Update(int message, void * pData) override;


};

