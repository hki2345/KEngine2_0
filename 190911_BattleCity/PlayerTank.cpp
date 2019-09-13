#include "PlayerTank.h"


#include <KInputManager.h>
#include <KTimeManager.h>

#include <KDebugManager.h>

#include <KSprite_Animator.h>
#include <KRect_Collision.h>
#include <KOne.h>


#include "Bullet.h"



PlayerTank::PlayerTank()
{
}


PlayerTank::~PlayerTank()
{
}

void PlayerTank::create()
{
	Tank::create();

	MyAnimator->set_bit(L"res\\YellowTank.bmp", 10);
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
	update_input();
	Tank::update();
	update_move();	
	update_collisiontile();
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
	   
	KDebugManager::instance()->insert_log(L"Cur Dir: %f, %f", vDir.x, vDir.y);
	KDebugManager::instance()->insert_log(L"Prev Dir: %f, %f", vPrevDir.x, vPrevDir.y);
	KDebugManager::instance()->insert_log(L"Pos: %f, %f", kone()->pos().x, kone()->pos().y);
	KDebugManager::instance()->insert_log(L"Check Pos: %f, %f", vPrevChecPos.x, vPrevChecPos.y);
}

void PlayerTank::update_collisiontile()
{
	if (true == bTileCol)
	{
		kone()->pos(vPrevChecPos);
	}
}