#include "KMacro.h"
#include "KSceneManager.h"
#include "KScene.h"

std::map<std::wstring, KScene*> KSceneManager::MapScene;
std::map<std::wstring, KScene*>::iterator KSceneManager::mSMapScene;
std::map<std::wstring, KScene*>::iterator KSceneManager::mEMapScene;
std::map<std::wstring, KScene*>::iterator KSceneManager::mFMapScene;
KScene* KSceneManager::curscene = nullptr;


void KSceneManager::init()
{
	curscene->init();
}
void KSceneManager::update()
{
	curscene->update();
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
}





KScene* KSceneManager::create_scene(const wchar_t* _Name)
{
	KScene* Tmp = find_scene(_Name);
	if (nullptr != Tmp)
	{
		return Tmp;
	}

	Tmp = new KScene();
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