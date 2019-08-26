#include "KMacro.h"
#include "KSceneManager.h"
#include "KScene.h"


KSceneManager* KSceneManager::pKSceneManager = nullptr;

void KSceneManager::init()
{
	if (nullptr == curscene)
	{
		return;
	}
	curscene->init();
}
void KSceneManager::update()
{
	if (nullptr == curscene)
	{
		return;
	}
	curscene->update();
}
void KSceneManager::render()
{
	if (nullptr == curscene)
	{
		return;
	}
	curscene->render();
}


void KSceneManager::release()
{
	mSMapScene = MapScene.begin();
	mEMapScene = MapScene.end();

	for (; mSMapScene != mEMapScene; ++mSMapScene)
	{
		mSMapScene->second->release();
		RELEASE_PTR(mSMapScene->second);
	}

	MapScene.clear();


	RELEASE_PTR(pKSceneManager);
}



KScene* KSceneManager::create_scene(KScene* _Other, const wchar_t* _Name /*= L"KScene"*/)
{
	if (nullptr == _Other)
	{
		return nullptr;
	}

	_Other->name(_Name);
	MapScene.insert(std::make_pair(_Name, _Other));
	return _Other;
}


KScene* KSceneManager::create_scene(const wchar_t* _Name/*= L"KScene"*/)
{
	KScene* Tmp = new KScene();
	Tmp->name(_Name);
	MapScene.insert(std::make_pair(_Name, Tmp));
	return Tmp;
}



KScene* KSceneManager::find_scene(const wchar_t* _Name)
{
	mFMapScene = MapScene.find(_Name);
	if (MapScene.end() != mFMapScene)
	{
		return mFMapScene->second;
	}

	return nullptr;
}

bool KSceneManager::delete_scene(const wchar_t* _Name)
{
	mFMapScene = MapScene.find(_Name);
	if (MapScene.end() == mFMapScene)
	{
		return false;
	}

	mFMapScene->second->release();
	delete mFMapScene->second;
	MapScene.erase(mFMapScene);
	return true;
}

bool KSceneManager::change_scene(const wchar_t* _Name)
{
	KScene* Tmp = find_scene(_Name);
	if (nullptr == Tmp)
	{
		KASSERT;
		return false;
	}

	curscene = Tmp;
	return true;
}