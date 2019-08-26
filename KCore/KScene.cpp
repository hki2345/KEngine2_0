#include "KScene.h"
#include "KOne.h"
#include "KMacro.h"
#include "KRenderManager.h"



KScene::KScene()
{
}


bool KScene::init()
{
	mSOneMap = MapKOne.begin();
	mEOneMap = MapKOne.end();

	for (; mSOneMap != mEOneMap; ++mSOneMap)
	{
		mSOneMap->second->init();
	}

	if (nullptr == curKRenderMgr)
	{
		curKRenderMgr = new KRenderManager();
		curKRenderMgr->init();
	}

	return true;
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


	curKRenderMgr->release();
	RELEASE_PTR(curKRenderMgr);
}


void KScene::render() 
{
	curKRenderMgr->render();
}


KOne* KScene::create_kone(KOne* _Other, const wchar_t* _Name /*= L"KOne"*/)
{
	if (nullptr == _Other)
	{
		return nullptr;
	}

	_Other->name(_Name);
	_Other->kscene(this);


	MapKOne.insert(std::make_pair(_Name, _Other));
	return _Other;
}

KOne* KScene::create_kone(const wchar_t* _Name/*= L"KOne"*/)
{
	KOne* Tmp =  new KOne();
	Tmp->name(_Name);
	Tmp->kscene(this);


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