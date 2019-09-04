#include "GameManager.h"
#include "KSceneManager.h"
#include "KInputManager.h"
#include "KCore.h"

#include "SceneTest.h"
#include "SceneTest2.h"


GameManager* GameManager::pkGameManager = nullptr;

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}



void GameManager::init()
{
	SceneTest* NSCENE = new SceneTest();
	SceneTest2* NSCENE2 = new SceneTest2();

	KSceneManager::instance()->create_scene(NSCENE, L"Test");
	KSceneManager::instance()->create_scene(NSCENE2, L"Test2");
	KSceneManager::instance()->change_scene(L"Test");
}
void GameManager::update()
{
	bool Value = KInputManager::instance()->is_press(0x58);

	if (true == Value)
	{
		KCore::instance()->shut_down();
	}
}
void GameManager::release()
{
	int a = 9;
	delete pkGameManager;
}