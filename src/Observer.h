#pragma once

#include <vector>


template<typename MSG>
class iObserver
{
public:
	iObserver()									= default;
	iObserver(const iObserver&)					= default;
	iObserver(iObserver&&)						= default;
	iObserver& operator=(const iObserver&)		= default;
	iObserver& operator=(iObserver&&)			= default;
	virtual ~iObserver()						= default;

public:	
	virtual void handleEvent(const MSG& _msg)	= 0;	
};


template<typename MSG>
class iObservable
{
public:
	iObservable()										= default;
	iObservable(const iObservable&)					= default;
	iObservable(iObservable&&)						= default;
	iObservable& operator=(const iObservable&)		= default;
	iObservable& operator=(iObservable&&)			= default;
	virtual ~iObservable()							= default;

public:	
	virtual void attachObs(iObserver<MSG>* _observer)	= 0;
	virtual void detachObs(iObserver<MSG>* _observer)	= 0;
	virtual void notifyEvent(const MSG& _msg)			= 0;
};


template<typename MSG>
class Observable : public iObservable<MSG>
{
public:
	Observable()									= default;
	Observable(const Observable&)				= default;
	Observable(Observable&&)					= default;
	Observable& operator=(const Observable&)	= default;
	Observable& operator=(Observable&&)			= default;
	virtual ~Observable()							= default;

public:	
	virtual void attachObs(iObserver<MSG>* _obs)	override;
	virtual void detachObs(iObserver<MSG>* _obs)	override;
	virtual void notifyEvent(const MSG& _msg)		override;
private:
	std::vector<iObserver<MSG>*> m_observers;
};

template<typename MSG>
void Observable<MSG>::attachObs(iObserver<MSG>* _obs)
{
	auto iobs = std::find(m_observers.begin(), m_observers.end(), _obs);
	if (iobs == m_observers.end())
	{
		m_observers.push_back(_obs);
	}
}

template<typename MSG>
void Observable<MSG>::detachObs(iObserver<MSG>* _obs)
{
	auto iobs = std::find(m_observers.begin(), m_observers.end(), _obs);
	if (iobs != m_observers.end())
	{
		m_observers.erase(iobs);
	}
}

template<typename MSG>
void Observable<MSG>::notifyEvent(const MSG& _msg)
{
	for (auto obs : m_observers)
	{
		obs->handleEvent(_msg);
	}
}