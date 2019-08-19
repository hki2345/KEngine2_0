#include "KScene.h"
#include "KOne.h"
#include "KMacro.h"




KScene::KScene()
{
}


KScene::~KScene()
{
}



void KScene::init()
{
	mSOneMap = MapKOne.begin();
	mEOneMap = MapKOne.end();

	for (; mSOneMap != mEOneMap; ++mSOneMap)
	{
		mSOneMap->second->init();
	}
}

void KScene::update()
{
	mSOneMap = MapKOne.begin();
	mEOneMap = MapKOne.end();

	for (; mSOneMap != mEOneMap; ++mSOneMap)
	{
		mSOneMap->second->update();
	}
}

void KScene::release()
{
	mSOneMap = MapKOne.begin();
	mEOneMap = MapKOne.end();

	for (; mSOneMap != mEOneMap; ++mSOneMap)
	{
		mSOneMap->second->release();
		RELEASE_PTR(mSOneMap->second);
	}

	MapKOne.clear();
}




KOne* KScene::create_kone(const wchar_t* _Name)
{
	KOne* Tmp = find_kone(_Name);
	if (nullptr != Tmp)
	{
		return Tmp;
	}

	Tmp = new KOne();
	Tmp->name(_Name);
	MapKOne.insert(std::make_pair(_Name, Tmp));
	return Tmp;
}

KOne* KScene::find_kone(const wchar_t* _Name)
{
	mFOneMap = MapKOne.find(_Name);
	if (MapKOne.end() != mFOneMap)
	{
		return mFOneMap->second;
	}

	return nullptr;
}

bool KScene::delete_kone(const wchar_t* _Name)
{
	mFOneMap = MapKOne.find(_Name);
	if (MapKOne.end() == mFOneMap)
	{
		return false;
	}

	mFOneMap->second->release();
	delete mFOneMap->second;
	MapKOne.erase(mFOneMap);
	return true;
}