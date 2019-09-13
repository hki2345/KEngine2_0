#include "Tile.h"
#include "TileManager.h"


#include <KSprite_Render.h>
#include <KRect_Collision.h>
#include <KScene.h>
#include <KOne.h>


Tile::Tile()
{
}


Tile::~Tile()
{
}



void Tile::create()
{
	sName = L"Tile";

	kone()->size({ TILEXSIZE, TILEYSIZE });
	MyRenderer = kone()->add_component<KSprite_Render>();
	MyRenderer->init();
	MyRenderer->active(false);
	MyCollider = kone()->add_component<KRect_Collision>();
	MyCollider->init();
}
void Tile::set_tile(const KPos2& _Pos, const BATTLECITY_GAMETILE& _Info)
{
	kone()->pos(_Pos);

	if (BATTLECITY_GAMETILE::BG_WOOD_BLOCK == _Info)
	{
		MyRenderer->set_bit(L"res\\TileSpriteSub.bmp", 11);
	}
	else
	{
		MyRenderer->set_bit(L"res\\TileSpriteSub.bmp", 9);
	}
	MyRenderer->set_split(3, 8);
	MyRenderer->set_idx((int)_Info);

	MyCollider->set_rect(1);

	eTileType = _Info;
}

void Tile::update_trans()
{
	MyRenderer->update_trans(MyRenderer->kscene()->SceneCamPos);
}

void Tile::render(HDC _Hdc)
{
	MyRenderer->render(_Hdc);

	MyRenderer->set_idx(0, 5);
}


bool Tile::collision_bullet(const KPos2& _Dir)
{
	switch (eTileType)
	{
	case BG_STONE_BLOCK:
		return true;

	case BG_BROWN_BLOCK:
		if (KPos2::Down == _Dir)
		{
			MyRenderer->set_idx(0, 5);
			eTileType = BG_RECTBROWN01;
		}
		else if (KPos2::Right == _Dir)
		{
			MyRenderer->set_idx(1, 5);
			eTileType = BG_RECTBROWN02;
		}
		else if (KPos2::Left == _Dir)
		{
			MyRenderer->set_idx(2, 5);
			eTileType = BG_RECTBROWN03;
		}
		else if (KPos2::Up == _Dir)
		{
			MyRenderer->set_idx(0, 6);
			eTileType = BG_RECTBROWN04;
		}
		TileManager::instance()->update_tile(this);

		return true;
	case BG_PHOENIX01:
	case BG_PHOENIX02:
	case BG_PHOENIX03:
	case BG_PHOENIX04:
		break;

	case BG_RECTBROWN01:
		if (KPos2::Down == _Dir)
		{
			kone()->active(false);
		}
		else if (KPos2::Up == _Dir)
		{
			kone()->active(false);
		}
		else if (KPos2::Left == _Dir)
		{
			MyRenderer->set_idx(1, 6);
			eTileType = BG_SMALLBROWN01;
		}
		else if (KPos2::Right == _Dir)
		{
			MyRenderer->set_idx(2, 6);
			eTileType = BG_SMALLBROWN02;
		}

		TileManager::instance()->update_tile(this);
		return true;
	case BG_RECTBROWN02:
		if (KPos2::Down == _Dir)
		{
			MyRenderer->set_idx(2, 6);
			eTileType = BG_SMALLBROWN01;
		}
		else if (KPos2::Up == _Dir)
		{
			MyRenderer->set_idx(0, 7);
			eTileType = BG_SMALLBROWN03;
		}
		else if (KPos2::Left == _Dir)
		{
			kone()->active(false);
		}
		else if (KPos2::Right == _Dir)
		{
			kone()->active(false);
		}
		TileManager::instance()->update_tile(this);
		return true;
	case BG_RECTBROWN03:
		if (KPos2::Down == _Dir)
		{
			MyRenderer->set_idx(1, 6);
			eTileType = BG_SMALLBROWN01;
		}
		else if (KPos2::Up == _Dir)
		{
			MyRenderer->set_idx(1, 7);
			eTileType = BG_SMALLBROWN04;
		}
		else if (KPos2::Left == _Dir)
		{
			kone()->active(false);
		}
		else if (KPos2::Right == _Dir)
		{
			kone()->active(false);
		}
		TileManager::instance()->update_tile(this);
		return true;
	case BG_RECTBROWN04:
		if (KPos2::Down == _Dir)
		{
			kone()->active(false);
		}
		else if (KPos2::Up == _Dir)
		{
			kone()->active(false);
		}
		else if (KPos2::Left == _Dir)
		{
			MyRenderer->set_idx(1, 7);
			eTileType = BG_SMALLBROWN04;
		}
		else if (KPos2::Right == _Dir)
		{
			MyRenderer->set_idx(0, 7);
			eTileType = BG_SMALLBROWN03;
		}
		TileManager::instance()->update_tile(this);
		return true;


	case BG_SMALLBROWN01:
	case BG_SMALLBROWN02:
	case BG_SMALLBROWN03:
	case BG_SMALLBROWN04:
		kone()->active(false);
		TileManager::instance()->update_tile(this);
		break;
	case BG_BLOCKNUM:
		break;
	default:
		break;
	}
}