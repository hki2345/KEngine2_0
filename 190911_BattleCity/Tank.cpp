#include "Tank.h"
#include <KOne.h>
#include <KScene.h>

#include <KSprite_Animator.h>
#include <KRect_Collision.h>
#include <KTimeManager.h>

#include "Tile.h"
#include "Bullet.h"
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
	sName = L"Tank";

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

	MyCollider = kone()->add_component<KRect_Collision>();
	MyCollider->set_rect(0);
	MyCollider->pivot(KPos2(STARTXPOS * -1.0f, STARTYPOS * -1.0f));
	MyCollider->insert_stayfunc<Tank>(this, &Tank::stay_tile);
	MyCollider->insert_exitfunc<Tank>(this, &Tank::exit_tile);


	for (size_t i = 0; i < 2; i++)
	{
		KOne* NewBullet = kscene()->create_kone(L"Bullet");
		VectorMyBullet.push_back(NewBullet->add_component<Bullet>());
	}
}

bool Tank::init()
{
	vDir = KPos2::Up;
	vPrevDir = KPos2::Up;
	bTileCol = false;

	PrevColTile = nullptr;

	return true;
}


void Tank::update() 
{
	if (vPrevDir == KPos2::Zero)
	{
		MyAnimator->change_animation(L"Idle");
	}
	else if (vPrevDir == KPos2::Left)
	{
		MyAnimator->change_animation(L"Left");
	}
	else if (vPrevDir == KPos2::Right)
	{
		MyAnimator->change_animation(L"Right");
	}
	else if (vPrevDir == KPos2::Down)
	{
		MyAnimator->change_animation(L"Up");
	}
	else if (vPrevDir == KPos2::Up)
	{
		MyAnimator->change_animation(L"Down");
	}

	update_checkingpos();
	update_coltile();
}

void Tank::update_coltile()
{
	if (nullptr != PrevColTile && false == PrevColTile->kone()->active())
	{
		PrevColTile = nullptr;
		bTileCol = false;
	}
}

void Tank::update_checkingpos()
{
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

		else if ((vDir == KPos2::Up || vDir == KPos2::Down || vDir == KPos2::Zero) &&
			(vPrevDir == KPos2::Left || vPrevDir == KPos2::Right))
		{
			KPos2 Tmp = kone()->pos();

			int Nam = (int)Tmp.x % TILEXSIZE;
			int Mok = (int)Tmp.x / TILEXSIZE;

			if (TILEXSIZE / 2 > Nam)
			{
				kone()->pos(KPos2(Mok * TILEXSIZE, Tmp.y));
			}
			else
			{
				kone()->pos(KPos2(Mok * TILEXSIZE + (TILEXSIZE), Tmp.y));
			}
		}

		if (vDir != KPos2::Zero)
		{
			vPrevDir = vDir;
		}
	}
}

void Tank::update_move()
{
	vPrevChecPos = kone()->pos();
	KPos2 Tmp = kone()->pos() + vDir * fSpeed * KTimeManager::instance()->deltatime();
	if (Tmp.x >= TileManager::instance()->tilemap_size().Start.x &&
		Tmp.x <= TileManager::instance()->tilemap_size().Size.x &&
		Tmp.y >= TileManager::instance()->tilemap_size().Start.y &&
		Tmp.y <= TileManager::instance()->tilemap_size().Size.y)
	{
		kone()->moving_pos(Tmp);
	}
}


void Tank::stay_tile(KOne* _Tile)
{
	Tile* CurTile = _Tile->get_component<Tile>();
	if (nullptr != CurTile && 
		BATTLECITY_GAMETILE::BG_METAL_BLOCK != CurTile->tile_type())
	{
		bTileCol = true;
		PrevColTile = CurTile;
	}
}
void Tank::exit_tile(KOne* _Tile)
{
	Tile* CurTile = _Tile->get_component<Tile>();
	if (nullptr != CurTile)
	{
		PrevColTile = nullptr;
		bTileCol = false;
	}
}