#include "GameManager.h"


#include <KResourceManager.h>
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
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\player0.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\player1.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\player2.bmp");

	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\win.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\win2.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\die.bmp");



	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\back.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\back_normal.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\back_normal2.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\back_deco.bmp");


	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\enemy_1b.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\enemy_1f.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\enemy_b.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\enemy_f.bmp");

	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\enemy_l_b.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\enemy_l_f.bmp");

	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\front.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\front2.bmp");

	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\end.bmp");

	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\miter.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\cash.bmp");

	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\icon.bmp");

	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\star.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\star1.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\star2.bmp");

	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\BackBoard.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\ScoreBoard.bmp");

	AddFontResourceA("Circus\\DungGeunMo.ttf");



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
void GameManager::end_game()
{
	KSceneManager::instance()->change_scene(L"Intro");
}