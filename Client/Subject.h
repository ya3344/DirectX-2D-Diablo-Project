#pragma once

class Observer;

class Subject
{
public:
	Subject();
	virtual ~Subject();

public:
	virtual void Subscribe(Observer* pObserver);
	virtual void UnSubscribe(Observer* pObserver);
	virtual void Notify(int message, void* pData = nullptr);
	virtual void Release(void);

protected:
	list<Observer*> mObserverSpace;
};

