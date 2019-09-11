#include "InGameScene.h"
#include <KOne.h>
#include <KSprite_Animator.h>
#include <KMacro.h>

#include "PlayerTank.h"
#include "TileManager.h"



InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}



void InGameScene::create()
{
	KScene::create();

	KOne* CurSorOne = create_kone(L"Cursor Tile");
	MyPlayer = CurSorOne->add_component<PlayerTank>();


	TileManager::instance()->create(this);
}


bool InGameScene::init()
{
	KScene::init();
	TileManager::instance()->init(L"res\\Test2.btd");


	return true;
}
void InGameScene::update()
{
	KScene::update();
}

void InGameScene::release() 
{
	KScene::release();
	TileManager::instance()->release();
}