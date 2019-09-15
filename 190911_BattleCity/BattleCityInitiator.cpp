#include "BattleCityInitiator.h"

#include <KWindowManager.h>
#include <KSceneManager.h>
#include <KResourceManager.h>
#include <KTimeManager.h>
#include <KDebugManager.h>
#include <KBitMap.h>

#include "InGameScene.h"
#include "IntroScene.h"


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

	IntroScene*  NewIntroScene = new IntroScene();
	InGameScene*  NewGameScene = new InGameScene();

	KSceneManager::instance()->create_scene(NewIntroScene, L"Intro");
	KSceneManager::instance()->create_scene(NewGameScene, L"Game");
	KSceneManager::instance()->change_scene(L"Intro");
	return true;
}