#include "InGameScene.h"
#include <KOne.h>
#include <KSprite_Animator.h>
#include <KRenderManager.h>
#include <KMacro.h>

#include "PlayerTank.h"
#include "EnemyTank.h"
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

	KOne* CurSorOne = create_kone(L"PlayerTank");
	MyPlayer = CurSorOne->add_component<PlayerTank>();


	KOne* CurSorEnemy = create_kone(L"EnemyTank");
	CurSorEnemy->add_component<EnemyTank>();

	TileManager::instance()->create(this);

	link_k2dCollider(0, 1);
	link_k2dCollider(0, 0);
}


bool InGameScene::init()
{
	KScene::init();
	TileManager::instance()->init(L"res\\Test2.btd");
	TileManager::instance()->update_alltile();
	return true;
}
void InGameScene::update()
{
	KScene::update();
}

void InGameScene::render()
{
	TileManager::instance()->render();
	KScene::render();
}

void InGameScene::release() 
{
	KScene::release();
	TileManager::instance()->release();
}