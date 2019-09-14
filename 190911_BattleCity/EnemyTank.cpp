#include "EnemyTank.h"
#include <KTimeManager.h>

#include <KSprite_Animator.h>
#include <KRect_Collision.h>
#include <KOne.h>
#include "Bullet.h"
#include "PlayerTank.h"


EnemyTank::EnemyTank()
{
}


EnemyTank::~EnemyTank()
{
}

void EnemyTank::create()
{
	Tank::create();

	MyCollider->set_rect(0);
	MyAnimator->set_bit(L"res\\WhiteTank.bmp", 10);

	MyCollider->insert_stayfunc<EnemyTank>(this, &EnemyTank::stay_tile);
	MyCollider->insert_exitfunc<EnemyTank>(this, &EnemyTank::exit_tile);
}

bool EnemyTank::init()
{
	Tank::init();

	kone()->pos({ 220.0f, 300.0f });
	kone()->size({ 40.0f, 40.0f });

	fDirChangeCurTime = .0f;
	fDirChangeTime = 2.0f;

	fShootCurTime = .0f;
	fShootTime = 1.0f;

	return true;
}

void EnemyTank::update()
{
	update_collisiontile();
	update_AI();
	Tank::update();
	update_move();
}


void EnemyTank::update_AI()
{

	if (fDirChangeCurTime <= fDirChangeTime)
	{
		fDirChangeCurTime += KTimeManager::instance()->deltatime();
	}
	else
	{
		int XXX = 0;
		fDirChangeCurTime = .0f;
		XXX = rand() % 4;

		if (0 == XXX)
		{
			vDir = KPos2::Down;
		}
		else if (1 == XXX)
		{
			vDir = KPos2::Up;
		}
		else if (2 == XXX)
		{
			vDir = KPos2::Left;
		}
		else if (3 == XXX)
		{
			vDir = KPos2::Right;
		}
	}




	if (fShootCurTime <= fShootTime)
	{
		fShootCurTime += KTimeManager::instance()->deltatime();
	}
	else
	{
		int XXX = 0;

		fShootCurTime = .0f;
		XXX = rand() % 10;

		// if (3 < XXX)
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


	
}

void EnemyTank::update_move()
{
	Tank::update_move();

}

void EnemyTank::update_collisiontile()
{
	if (true == bTileCol || true == bTankCol)
	{
		kone()->pos(vPrevChecPos);
	}
}


void EnemyTank::stay_tile(KOne* _Other)
{
	Tank::stay_tile(_Other);

	PlayerTank* CurTank = _Other->get_component<PlayerTank>();
	if (nullptr != CurTank)
	{
		bTankCol = true;
		PrevColTank = CurTank;
	}
}

void EnemyTank::exit_tile(KOne* _Other)
{
	Tank::exit_tile(_Other);

	PlayerTank* CurTank = _Other->get_component<PlayerTank>();
	if (nullptr != CurTank)
	{
		PrevColTank = nullptr;
		bTankCol = false;
	}
}