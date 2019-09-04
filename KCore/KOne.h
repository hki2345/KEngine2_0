#pragma once
#include "PtrOf_KWindow.h"
#include "PtrOf_KScene.h"
#include "KTransform.h"
#include "KName.h"
#include "KActor.h"


#include <map>
#include <KPathManager.h>


class KState;
class KComponent;
class KOne : 
	public PtrOf_KWindow,
	public PtrOf_KScene,
	public KName,
	public KActor
{
public:
	friend class KScene;

protected:
	KOne();
	KOne(const KOne& _Core) = delete;
	KOne(const KOne&& _Core) = delete;
	void operator=(const KOne& _Core) = delete;
	~KOne()  {};


private:
	std::multimap<std::wstring, KComponent*> MapComponent;

	KTransform* MyTrans;


protected:
	bool init();
	void update();
	void release();


public:
	KComponent* set_component(KComponent* _Other);

	template <typename T>
	T* get_component()
	{
		std::multimap<std::wstring, KComponent*>::iterator SIter = MapComponent.begin();
		std::multimap<std::wstring, KComponent*>::iterator EIter = MapComponent.end();

		for (; SIter != EIter; ++SIter)
		{
			if (typeid(*(SIter->second)).hash_code() == typeid(T).hash_code())
			{
				return dynamic_cast<T*>(SIter->second);
			}
		}

		return nullptr;
	}
	
	template <typename Com>
	Com* add_component()
	{
		Com* NewCom = new Com();
		NewCom->kwindow(kwindow());
		NewCom->kscene(kscene());
		NewCom->kone(this);
		NewCom->init();

		MapComponent.insert(std::make_pair(NewCom->name(), NewCom));
		return NewCom;
	}



	void pos(const KVec2& _Pos);
	void size(const KSize2& _Size);
	void moving(const KSize2& _Value);
};

