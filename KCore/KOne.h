#pragma once
#include "KProgress.h"
#include "PtrOf_KScene.h"
#include <map>


class KState;
class KComponent;
class KOne : public KProgress, PtrOf_KScene
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

	std::multimap<std::wstring, KComponent*> MapComponent;
	std::multimap<std::wstring, KComponent*>::iterator mSMapComponent;
	std::multimap<std::wstring, KComponent*>::iterator mEMapComponent;
	std::multimap<std::wstring, KComponent*>::iterator mFMapComponent;


protected:
	virtual void init() override;
	virtual void update() override;
	virtual void release() override;


public:
	KComponent* set_component(KComponent* _Other);

	template <typename T>
	T* get_component()
	{
		mSMapComponent = MapComponent.begin();
		mEMapComponent = MapComponent.end();

		for (; mSMapComponent != mEMapComponent; ++mSMapComponent)
		{
			
		}
	}
	
	template <typename Com>
	Com* add_component()
	{
		/*if (false == Com::IsMulti(this))
		{
			return nullptr;
		}*/

		Com* NewCom = new Com();
		NewCom->one(this);
		// NewCom->kwindow(kwindow());
		NewCom->kscene(kscene());
		// NewCom->ComInit();

		if (false == NewCom->Init())
		{
			delete NewCom;
			return nullptr;
		}

		MapComponent.insert(std::make_pair(NewCom->name(), NewCom));
		return NewCom;
	}
};

