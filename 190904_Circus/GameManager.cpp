#include "GameManager.h"


#include <KResourceManager.h>
#include <KTimeManager.h>
#include <KDebugManager.h>
#include "KBitMap.h"


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

	KResourceManager<KBitMap>::instance()->init();
	KResourceManager<KBitMap>::instance()->load_forder(L"Circus");
	AddFontResourceA("Circus\\DungGeunMo.ttf");

	GameScene = new InGameScene();
	InScene = new IntroScene();

	KSceneManager::instance()->create_scene(GameScene, L"Game");
	KSceneManager::instance()->create_scene(InScene, L"Intro");
	KSceneManager::instance()->change_scene(L"Intro");
}
void GameManager::update()
{
	bool Value = KInputManager::instance()->is_down(0x58);

	if (true == Value)
	{
		KCore::instance()->shut_down();
	}


	KDebugManager::instance()->insert_log(L"FPS: %f", KTimeManager::instance()->fps());
	KDebugManager::instance()->insert_log(L"DeltaTime: %f", KTimeManager::instance()->deltatime());
	KDebugManager::instance()->insert_log(L"Cam X Pos: %f", GameScene->SceneCamPos.x);
}
void GameManager::release()
{
	delete pkGameManager;
}

void GameManager::reset_game()
{
	KSceneManager::instance()->change_scene(L"Game");
}
void GameManager::end_game()
{
	KSceneManager::instance()->change_scene(L"Intro");
}