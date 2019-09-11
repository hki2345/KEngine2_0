#include "Tank.h"
#include <KOne.h>
#include <KSprite_Animator.h>
#include <KTimeManager.h>

#include "TileManager.h"
#include "BattleTile.h"


Tank::Tank()
{
}


Tank::~Tank()
{
}


void Tank::create()
{
	MyAnimator = kone()->add_component<KSprite_Animator>();
	MyAnimator->init();
	MyAnimator->set_bit(L"res\\WhiteTank.bmp", 10);
	MyAnimator->set_split(8, 8);
	MyAnimator->insert_animation(L"Idle", 0, 0);
	MyAnimator->insert_animation(L"Up", 0, 1);
	MyAnimator->insert_animation(L"Left", 2, 3);
	MyAnimator->insert_animation(L"Down", 4, 5);
	MyAnimator->insert_animation(L"Right", 6, 7);
	MyAnimator->change_animation(L"Idle");

	fSpeed = 100.0f;
}

void Tank::update() 
{
	if (vDir == KPos2::Zero)
	{
		MyAnimator->change_animation(L"Idle");
	}
	else if (vDir == KPos2::Left)
	{
		MyAnimator->change_animation(L"Left");
	}
	else if (vDir == KPos2::Right)
	{
		MyAnimator->change_animation(L"Right");
	}
	else if (vDir == KPos2::Down)
	{
		MyAnimator->change_animation(L"Up");
	}
	else if (vDir == KPos2::Up)
	{
		MyAnimator->change_animation(L"Down");
	}

	if (vDir != vPrevDir)
	{
		if ((vDir == KPos2::Right || vDir == KPos2::Left || vDir == KPos2::Zero) &&
			(vPrevDir == KPos2::Up || vPrevDir == KPos2::Down))
		{
			KPos2 Tmp = kone()->pos();

			int Nam = (int)Tmp.y % TILEYSIZE;
			int Mok = (int)Tmp.y / TILEYSIZE;

			if (TILEYSIZE / 2 > Nam)
			{
				kone()->pos(KPos2(Tmp.x, Mok * TILEYSIZE));
			}
			else
			{
				kone()->pos(KPos2(Tmp.x, Mok * TILEYSIZE + (TILEYSIZE)));
			}
		}

		if ((vDir == KPos2::Up || vDir == KPos2::Down || vDir == KPos2::Zero) &&
			(vPrevDir == KPos2::Left || vPrevDir == KPos2::Right))
		{
			KPos2 Tmp = kone()->pos();

			int Nam = (int)Tmp.x % TILEXSIZE;
			int Mok = (int)Tmp.x / TILEXSIZE;

			if (TILEXSIZE / 2 > Nam)
			{
				kone()->pos(KPos2(Mok * TILEXSIZE , Tmp.y));
			}
			else
			{
				kone()->pos(KPos2(Mok * TILEXSIZE + (TILEXSIZE), Tmp.y));
			}
		}
		vPrevDir = vDir;
	}
}

void Tank::update_move()
{
	KPos2 Tmp = kone()->pos() + vDir * fSpeed * KTimeManager::instance()->deltatime();
	if (Tmp.x >= TileManager::instance()->tilemap_size().Start.x &&
		Tmp.x <= TileManager::instance()->tilemap_size().Size.x &&
		Tmp.y >= TileManager::instance()->tilemap_size().Start.y &&
		Tmp.y <= TileManager::instance()->tilemap_size().Size.y)
	{
		kone()->moving_pos(Tmp);
	}

}