#include "BattleCityInitiator.h"

#include <KWindowManager.h>
#include <KResourceManager.h>
#include <KTimeManager.h>
#include <KDebugManager.h>
#include "KBitMap.h"

#include "KSceneManager.h"
#include "InGameScene.h"


BattleCityInitiator::BattleCityInitiator()
{
}


BattleCityInitiator::~BattleCityInitiator()
{
}


bool BattleCityInitiator::init()
{
	srand(GetTickCount());

	KResourceManager<KBitMap>::instance()->init();
	KResourceManager<KBitMap>::instance()->load_forder(L"res");
	AddFontResourceA("res\\DungGeunMo.ttf");

	InGameScene*  GameScene = new InGameScene();

	KSceneManager::instance()->create_scene(GameScene, L"Game");
	KSceneManager::instance()->change_scene(L"Game");

	KWindowManager::instance()->backcolor(RGB(128, 128, 128));

	return true;
}