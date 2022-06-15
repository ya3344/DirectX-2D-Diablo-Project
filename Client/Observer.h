#pragma once
class Observer abstract
{
public:
	Observer();
	virtual ~Observer();

public:
	virtual void Update(int message, void* pData) PURE;

public:
	const ATTRIBUTE* GetAttribute(void) const { return &mAttribute; };

protected:
	ATTRIBUTE mAttribute;
};

