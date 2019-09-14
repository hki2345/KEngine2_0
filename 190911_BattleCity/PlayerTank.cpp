#include "PlayerTank.h"


#include <KInputManager.h>
#include <KTimeManager.h>

#include <KDebugManager.h>

#include <KSprite_Animator.h>
#include <KRect_Collision.h>
#include <KScene.h>
#include <KOne.h>


#include "Bullet.h"
#include "EnemyTank.h"
#include "Shield_Effect.h"


PlayerTank::PlayerTank()
{
}


PlayerTank::~PlayerTank()
{
}

void PlayerTank::create()
{
	Tank::create();
	
	MyCollider->set_rect(1);
	MyAnimator->set_bit(L"res\\YellowTank.bmp", 10);


	MyCollider->insert_stayfunc<PlayerTank>(this, &PlayerTank::stay_tile);
	MyCollider->insert_exitfunc<PlayerTank>(this, &PlayerTank::exit_tile);

	for (size_t i = 0; i < VectorMyBullet.size(); i++)
	{
		VectorMyBullet[i]->set_tank(3);
	}


	MyShieldEffect = kscene()->create_kone(L"Shield")->add_component<Shield_Effect>();
	MyShieldEffect->kone()->active(false);
	MyShieldEffect->set_shield(kone());
}

bool PlayerTank::init()
{
	Tank::init();
	kone()->size({ 40.0f, 40.0f });


	fShieldCurTime = .0f; 
	fShieldTime = 5.0f;

	return true;
}

void PlayerTank::update()
{
	if (Tank::TS_PLAY == eCurState)
	{
		update_shield();
		update_collisiontile();
		update_input();
		Tank::update();
		update_move();
	}
	else
	{
		Tank::update();
	}
}

void PlayerTank::update_respawn()
{
	MyAnimator->change_animation(L"Respawn");
	fRespawnCurTime += KTimeManager::instance()->deltatime();
	if (fRespawnCurTime >= fRespawnTime)
	{
		fRespawnCurTime = .0f;
		eCurState = TANK_STATUS::TS_PLAY;
		fShieldCurTime = .0f;
		MyShieldEffect->kone()->active(true);
		kscene()->passlink_k2dCollider(1, 2);
		kscene()->passlink_k2dCollider(1, 4);
	}
}

void PlayerTank::update_shield()
{
	fShieldCurTime += KTimeManager::instance()->deltatime();
	if (fShieldCurTime >= fShieldTime)
	{
		MyShieldEffect->kone()->active(false);
		kscene()->clearpasslink();
	}
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
		shoot_bullet();
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