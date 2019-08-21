#pragma once
#include "KProgress.h"
#include <map>


class KState;
class KComponent;
class KOne : public KProgress
{
public:
	friend class KScene;

protected:
	KOne();
	KOne(const KOne& _Core) = delete;
	KOne(const KOne&& _Core) = delete;
	void operator=(const KOne& _Core) = delete;
	~KOne() override;


private:

	std::map<std::wstring, KComponent*> MapComponent;
	std::map<std::wstring, KComponent*>::iterator mSMapComponent;
	std::map<std::wstring, KComponent*>::iterator mEMapComponent;
	std::map<std::wstring, KComponent*>::iterator mFMapComponent;

public:
	template <typename T>
	T* Set_Component()
	{
		mSMapComponent = MapComponent.begin();
		mEMapComponent = MapComponent.end();

		for (; mSMapComponent != mEMapComponent; ++mSMapComponent)
		{

		}
	}

	template <typename T>
	T* Get_Component()
	{
		mSMapComponent = MapComponent.begin();
		mEMapComponent = MapComponent.end();

		for (; mSMapComponent != mEMapComponent; ++mSMapComponent)
		{

		}
	}

protected:
	virtual void init() override;
	virtual void update() override;
	virtual void release() override;
};

