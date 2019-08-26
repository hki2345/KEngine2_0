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
	~KOne() override {};


private:
	std::multimap<std::wstring, KComponent*> MapComponent;

protected:
	virtual bool init() override;
	virtual void update() override;
	virtual void release() override;


public:
	KComponent* set_component(KComponent* _Other);

	template <typename T>
	T* get_component()
	{
		std::multimap<std::wstring, KComponent*>::iterator SIter = MapComponent.begin();
		std::multimap<std::wstring, KComponent*>::iterator EIter = MapComponent.end();

		for (; SIter != EIter; ++SIter)
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

		if (false == NewCom->init())
		{
			delete NewCom;
			return nullptr;
		}

		MapComponent.insert(std::make_pair(NewCom->name(), NewCom));
		return NewCom;
	}
};

