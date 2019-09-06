#include "InGameScene.h"
#include "ComPlayer.h"


#include "MapManager.h"
#include "ObstacleManager.h"
#include "UIManager.h"

#include <KTimeManager.h>
#include <KOne.h>
#include <KMacro.h>


InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}

void InGameScene::create()
{
	KScene::create();

	KOne* OnePlayer = create_kone(L"Player");
	pPlayer = OnePlayer->add_component<ComPlayer>();

	MapManager MManager;
	MManager.create(this, pPlayer);

	pObsManager = new ObstacleManager();
	pObsManager->create(this, pPlayer);

	pUIManager = new UIManager();
	pUIManager->create(this, pPlayer);
}


bool InGameScene::init()
{
	KScene::init();

	fFireTime = .0f; 
	fFireSpwanTime = 2.0f;


	pObsManager->init_fire();
	return true;
}


void InGameScene::update()
{
	KScene::update();
	spwan_fire();


}



void InGameScene::spwan_fire()
{
	fFireTime += KTimeManager::instance()->deltatime();
	if (fFireTime >= fFireSpwanTime)
	{
		pObsManager->init_fire();
		fFireTime = .0f;
	}
}


void InGameScene::update_game()
{

}


void InGameScene::release()
{
	RELEASE_PTR(pUIManager);
	RELEASE_PTR(pObsManager);
	KScene::release();
}