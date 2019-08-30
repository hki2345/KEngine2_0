#include "KScene.h"
#include "KOne.h"
#include "KMacro.h"
#include "KRenderManager.h"



KScene::KScene()
{
}


bool KScene::init()
{
	std::multimap<std::wstring, KOne*>::iterator SIter = MapKOne.begin();
	std::multimap<std::wstring, KOne*>::iterator EIter = MapKOne.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->init();
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
	std::multimap<std::wstring, KOne*>::iterator SIter = MapKOne.begin();
	std::multimap<std::wstring, KOne*>::iterator EIter = MapKOne.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->update();
	}
}

void KScene::release()
{
	std::multimap<std::wstring, KOne*>::iterator SIter = MapKOne.begin();
	std::multimap<std::wstring, KOne*>::iterator EIter = MapKOne.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->release();
		RELEASE_PTR(SIter->second);
	}

	MapKOne.clear();


	if (nullptr != curKRenderMgr)
	{
		curKRenderMgr->release();
	}
	RELEASE_PTR(curKRenderMgr);
}


void KScene::render() 
{
	curKRenderMgr->render();
}


KOne* KScene::create_kone(KOne* _Other, const wchar_t* _Name /*= "KOne"*/)
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

KOne* KScene::create_kone(const wchar_t* _Name/*= "KOne"*/)
{
	KOne* Tmp =  new KOne();
	Tmp->name(_Name);
	Tmp->kscene(this);


	MapKOne.insert(std::make_pair(_Name, Tmp));
	return Tmp;
}

KOne* KScene::find_kone(const wchar_t* _Name)
{
	std::multimap<std::wstring, KOne*>::iterator FIter = MapKOne.find(_Name);
	if (MapKOne.end() != FIter)
	{
		return FIter->second;
	}

	return nullptr;
}

bool KScene::delete_kone(const wchar_t* _Name)
{
	std::multimap<std::wstring, KOne*>::iterator FIter = MapKOne.find(_Name);
	if (MapKOne.end() == FIter)
	{
		return false;
	}

	FIter->second->release();
	delete FIter->second;
	MapKOne.erase(FIter);
	return true;
}