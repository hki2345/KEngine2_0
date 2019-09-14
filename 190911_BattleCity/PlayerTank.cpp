#include "PlayerTank.h"


#include <KInputManager.h>
#include <KTimeManager.h>

#include <KDebugManager.h>

#include <KSprite_Animator.h>
#include <KRect_Collision.h>
#include <KOne.h>


#include "Bullet.h"
#include "EnemyTank.h"


PlayerTank::PlayerTank()
{
}


PlayerTank::~PlayerTank()
{
}

void PlayerTank::create()
{
	Tank::create();
	
	MyCollider->set_rect(0);
	MyAnimator->set_bit(L"res\\YellowTank.bmp", 10);


	MyCollider->insert_stayfunc<PlayerTank>(this, &PlayerTank::stay_tile);
	MyCollider->insert_exitfunc<PlayerTank>(this, &PlayerTank::exit_tile);
}

bool PlayerTank::init()
{
	Tank::init();

	kone()->pos({ 220.0f, 500.0f });
	kone()->size({ 40.0f, 40.0f });

	return true;
}

void PlayerTank::update()
{
	update_collisiontile();
	update_input();
	Tank::update();
	update_move();	
}


void PlayerTank::update_input()
{
	vDir = KPos2::Zero;
	if (true == KInputManager::instance()->is_press(VK_UP))
	{
		vDir = KPos2::Down;
	}
	else if (true == KInputManager::instance()->is_press(VK_DOWN))
	{
		vDir = KPos2::Up;
	}
	else if (true == KInputManager::instance()->is_press(VK_LEFT))
	{
		vDir = KPos2::Left;
	}
	else if (true == KInputManager::instance()->is_press(VK_RIGHT))
	{
		vDir = KPos2::Right;
	}


	if (true == KInputManager::instance()->is_down(VK_SPACE))
	{
		if (true == VectorMyBullet[0]->kone()->active())
		{
			return;
		}

		if (vPrevDir == KPos2::Left || vPrevDir == KPos2::Right)
		{
			VectorMyBullet[0]->set_bullet(kone()->pos() + kone()->size() * .5f * vPrevDir, vPrevDir);
		}
		else if (vPrevDir == KPos2::Up || vPrevDir == KPos2::Down)
		{
			VectorMyBullet[0]->set_bullet(
				kone()->pos() + kone()->size() * .5f * vPrevDir + KPos2(kone()->size().x * .2f, .0f), vPrevDir);
		}
	}
}

void PlayerTank::update_move()
{
	Tank::update_move();
}

void PlayerTank::update_collisiontile()
{
	if (true == bTileCol || true == bTankCol)
	{
		kone()->pos(vPrevChecPos);
	}
}


void PlayerTank::stay_tile(KOne* _Other)
{
	Tank::stay_tile(_Other);
	   
	EnemyTank* CurTank = _Other->get_component<EnemyTank>();
	if (nullptr != CurTank)
	{
		bTankCol = true;
		PrevColTank = CurTank;
	}
}

void PlayerTank::exit_tile(KOne* _Other)
{
	Tank::exit_tile(_Other);

	EnemyTank* CurTank = _Other->get_component<EnemyTank>();
	if (nullptr != CurTank)
	{
		PrevColTank = nullptr;
		bTankCol = false;
	}
}