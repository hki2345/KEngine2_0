#include "GameManager.h"

#include "KSceneManager.h"
#include "KInputManager.h"
#include "KCore.h"


#include "InGameScene.h"
#include "IntroScene.h"

GameManager* GameManager::pkGameManager = nullptr;

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}



void GameManager::init()
{
	srand(GetTickCount());

	InGameScene* GameScene = new InGameScene();
	IntroScene* InScene = new IntroScene();

	KSceneManager::instance()->create_scene(GameScene, L"Game");
	KSceneManager::instance()->create_scene(InScene, L"Intro");
	KSceneManager::instance()->change_scene(L"Intro");
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

void GameManager::reset_game()
{
	KSceneManager::instance()->change_scene(L"Game");
}