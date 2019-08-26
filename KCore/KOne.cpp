#include "KOne.h"
#include "KMacro.h"
#include "KComponent.h"



KOne::KOne()
{
}



bool KOne::init() 
{
	mSMapComponent = MapComponent.begin();
	mEMapComponent = MapComponent.end();

	for (; mSMapComponent != mEMapComponent; ++mSMapComponent)
	{
		mSMapComponent->second->init();
	}

	return true;
}

void KOne::update()
{
	mSMapComponent = MapComponent.begin();
	mEMapComponent = MapComponent.end();

	for (; mSMapComponent != mEMapComponent; ++mSMapComponent)
	{
		mSMapComponent->second->update();
	}
}

void KOne::release()
{
	mSMapComponent = MapComponent.begin();
	mEMapComponent = MapComponent.end();

	for (; mSMapComponent != mEMapComponent; ++mSMapComponent)
	{
		mSMapComponent->second->release();
		RELEASE_PTR(mSMapComponent->second);
	}

	MapComponent.clear();
}


KComponent* KOne::set_component(KComponent* _Other)
{
	KComponent* NewCom = new KComponent();
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
	return nullptr;
}