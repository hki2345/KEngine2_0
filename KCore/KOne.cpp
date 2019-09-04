#include "KOne.h"
#include "KMacro.h"
#include "KComponent.h"
#include "KTransform.h"



KOne::KOne()
{
}



bool KOne::init() 
{
	MyTrans =  add_component<KTransform>();

	return true;
}

void KOne::update()
{
	std::multimap<std::wstring, KComponent*>::iterator SIter = MapComponent.begin();
	std::multimap<std::wstring, KComponent*>::iterator EIter = MapComponent.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->update();
	}
}

void KOne::release()
{
	std::multimap<std::wstring, KComponent*>::iterator SIter = MapComponent.begin();
	std::multimap<std::wstring, KComponent*>::iterator EIter = MapComponent.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->release();
		RELEASE_PTR(SIter->second);
	}

	MapComponent.clear();
}


KComponent* KOne::set_component(KComponent* _Other)
{
	KComponent* NewCom = new KComponent();
	NewCom->kone(this);
	// NewCom->kwindow(kwindow());
	NewCom->kscene(kscene());
	NewCom->init();

	if (false == NewCom->init())
	{
		delete NewCom;
		return nullptr;
	}

	MapComponent.insert(std::make_pair(NewCom->name(), NewCom));
	return NewCom;
	return nullptr;
}



void KOne::pos(const KVec2& _Pos)
{
	MyTrans->pos(_Pos);
}
void KOne::size(const KSize2& _Size)
{
	MyTrans->size(_Size);
}

void KOne::moving(const KSize2& _Value)
{
	MyTrans->moving(_Value);
}