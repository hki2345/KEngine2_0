#include "KScene.h"
#include "KWindow.h"

#include "KOne.h"
#include "KMacro.h"
#include "KRenderManager.h"


#include "KCore.h"

KScene::KScene()
{
}

void KScene::create()
{
	if (nullptr == curKRenderMgr)
	{
		curKRenderMgr = new KRenderManager();
		curKRenderMgr->init();

		SceneCamPos = KPos2::Zero;
	}

	std::multimap<std::wstring, KOne*>::iterator SIter = MapKOne.begin();
	std::multimap<std::wstring, KOne*>::iterator EIter = MapKOne.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->create();
	}
}

bool KScene::init()
{
	std::multimap<std::wstring, KOne*>::iterator SIter = MapKOne.begin();
	std::multimap<std::wstring, KOne*>::iterator EIter = MapKOne.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->init();
	}

	return true;
}

void KScene::update()
{
	std::multimap<std::wstring, KOne*>::iterator SIter = MapKOne.begin();
	std::multimap<std::wstring, KOne*>::iterator EIter = MapKOne.end();

	for (; SIter != EIter; ++SIter)
	{
		if (true == SIter->second->active())
		{
			SIter->second->update();
			curKRenderMgr->update_trans(SceneCamPos);
		}		
	}
}

void KScene::out() 
{
	std::multimap<std::wstring, KOne*>::iterator SIter = MapKOne.begin();
	std::multimap<std::wstring, KOne*>::iterator EIter = MapKOne.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->out();
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

	KDebugManager::instance()->render();
}


KOne* KScene::create_kone(KOne* _Other, const wchar_t* _Name /*= "KOne"*/)
{
	if (nullptr == _Other)
	{
		return nullptr;
	}

	_Other->name(_Name);
	_Other->kscene(this);
	_Other->create();

	MapKOne.insert(std::make_pair(_Name, _Other));
	return _Other;
}

KOne* KScene::create_kone(const wchar_t* _Name/*= "KOne"*/)
{
	KOne* Tmp =  new KOne();

	Tmp->name(_Name);
	Tmp->kwindow(kwindow());
	Tmp->kscene(this);
	Tmp->create();


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


bool KScene::insert_krender(KRenderer* _Render, const int& _Key /*= 0*/)
{
	return curKRenderMgr->insert_krenderer(_Render, _Key);
}


KPos2 KScene::outof_screen(KOne* _Target)
{
	float TmpSize = 200.0f;

	if (SceneCamPos.x > _Target->pos().x + TmpSize + _Target->size().x )
	{
		return KPos2::Left;
	}
	else if (SceneCamPos.x + kwindow()->size().x < (_Target->pos().x + TmpSize * -1.0f) + (_Target->size().x))
	{
		return KPos2::Right;
	}

	return KPos2::Zero;
}