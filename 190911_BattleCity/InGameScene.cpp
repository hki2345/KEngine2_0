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
	MyPlayer->set_tank({ 220.0f, 500.0f });

	KOne* CurSorEnemy = create_kone(L"EnemyTank");
	EnemyTank* Enemy = CurSorEnemy->add_component<EnemyTank>();
	Enemy->set_tank({ 40.0f, 20.0f });

	TileManager::instance()->create(this);

	// 0 Å¸ÀÏ
	// 1 ÇÃ·¹ÀÌ¾î ÅÊÅ©
	// 2 Àû ÅÊÅ©
	// 3 ÇÃ·¹ÀÌ¾î ÃÑ
	// 4 Àû ÃÑ
	link_k2dCollider(0, 1);
	link_k2dCollider(0, 2);
	link_k2dCollider(0, 3);
	link_k2dCollider(0, 4);

	link_k2dCollider(1, 2);
	link_k2dCollider(1, 4);
	link_k2dCollider(2, 3);
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