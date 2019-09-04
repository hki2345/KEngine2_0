#include "GameManager.h"

#include "KSceneManager.h"
#include "KInputManager.h"
#include "KCore.h"


#include "InGameScene.h"

GameManager* GameManager::pkGameManager = nullptr;

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}



void GameManager::init()
{
	InGameScene* GameScene = new InGameScene();

	KSceneManager::instance()->create_scene(GameScene, L"Game");
	KSceneManager::instance()->change_scene(L"Game");
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
	delete pkGameManager;
}