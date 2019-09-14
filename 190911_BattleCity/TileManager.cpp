#include "TileManager.h"
#include "Tile.h"

#include <KDebugManager.h>
#include <KWindow.h>
#include <KMacro.h>
#include <KFileStream.h>
#include <KResourceManager.h>
#include <KScene.h>
#include <KOne.h>
#include <KBitMap.h>



TileManager* TileManager::pKTileManager =nullptr;

void TileManager::create(KScene* _Scene)
{
	XSize = 13 * 2;
	YSize = 13 * 2;
	MomScene = _Scene;


	if (nullptr == MapBit)
	{
		MapBit = KResourceManager<KBitMap>::instance()->load(L"KCore", L"MapBuffer");
		MapHdc = MapBit->kwindow_size({ XSize * 2.0f * TILEXSIZE, YSize * 2.0f * TILEYSIZE });
	}

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	myBrush = CreateSolidBrush(RGB(0,0,0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(MapHdc, myBrush);
	Rectangle(MapHdc, STARTXPOS, STARTYPOS, XSize * (TILEXSIZE), XSize * (TILEXSIZE));
	SelectObject(MapHdc, oldBrush);
	DeleteObject(myBrush);
}

bool TileManager::init(const wchar_t* _Name)
{
	std::vector<BATTLETILE_INFO> TmpVec;

	KFileStream::instance()->read_file(_Name, TmpVec);


	std::vector<BATTLECITY_GAMETILE> VectorTileInfo;
	VectorTileInfo.reserve(13 * 13 * 2 * 2);
	for (int i = 0; i < 13 * 13 * 2 * 2; i++)
	{
		BATTLECITY_GAMETILE TileInfo = BATTLECITY_GAMETILE::BG_NONE;
		VectorTileInfo.push_back(TileInfo);
	}

	for (int y = 0; y < YSize; y++)
	{
		for (int x = 0; x < XSize; x++)
		{

#pragma region TILE_SET
			if (BATTLECITY_TILE::NONE_BLOCK00 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				continue;
			}

			else if (BATTLECITY_TILE::SPAWN_BLOCK00 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorRespawn.push_back(KPos2(x * TILEXSIZE, y * TILEYSIZE ) + KPos2( STARTXPOS, STARTYPOS ));
			}

			else if (BATTLECITY_TILE::BROWN_BLOCK00 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
			}
			else if (BATTLECITY_TILE::BROWN_BLOCK01 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
			}
			else if (BATTLECITY_TILE::BROWN_BLOCK02 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
			}
			else if (BATTLECITY_TILE::BROWN_BLOCK03 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
			}
			else if (BATTLECITY_TILE::BROWN_BLOCK04 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
			}

			else if (BATTLECITY_TILE::STONE_BLOCK00 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_STONE_BLOCK;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_STONE_BLOCK;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_STONE_BLOCK;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_STONE_BLOCK;
			}
			else if (BATTLECITY_TILE::STONE_BLOCK01 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_STONE_BLOCK;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_STONE_BLOCK;
			}
			else if (BATTLECITY_TILE::STONE_BLOCK02 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_STONE_BLOCK;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_STONE_BLOCK;
			}
			else if (BATTLECITY_TILE::STONE_BLOCK03 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_STONE_BLOCK;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_STONE_BLOCK;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
			}
			else if (BATTLECITY_TILE::STONE_BLOCK04 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_STONE_BLOCK;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_STONE_BLOCK;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
			}


			else if (BATTLECITY_TILE::BROWN_SBLOCK01 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
			}
			else if (BATTLECITY_TILE::BROWN_SBLOCK02 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
			}
			else if (BATTLECITY_TILE::BROWN_SBLOCK03 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
			}
			else if (BATTLECITY_TILE::BROWN_SBLOCK04 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_BROWN_BLOCK;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_NONE;
			}

			else if (BATTLECITY_TILE::METAL_BLOCK00 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_METAL_BLOCK;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_METAL_BLOCK;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_METAL_BLOCK;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_METAL_BLOCK;
			}
			else if (BATTLECITY_TILE::WOOD_BLOCK00 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_WOOD_BLOCK;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_WOOD_BLOCK;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_WOOD_BLOCK;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_WOOD_BLOCK;
			}
			else if (BATTLECITY_TILE::WATER_BLOCK01 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_WATER_BLOCK01;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_WATER_BLOCK01;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_WATER_BLOCK01;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_WATER_BLOCK01;
			}


			else if (BATTLECITY_TILE::PHOENIX_BLOCK00 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_PHOENIX01;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_PHOENIX02;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_PHOENIX03;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_PHOENIX04;
			}


			else if (BATTLECITY_TILE::PBROKEN_BLOCK00 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
			{
				VectorTileInfo[(x + 0) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_BROKEN01;
				VectorTileInfo[(x + 1) + (y + 0) * XSize] = BATTLECITY_GAMETILE::BG_BROKEN02;
				VectorTileInfo[(x + 0) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_BROKEN03;
				VectorTileInfo[(x + 1) + (y + 1) * XSize] = BATTLECITY_GAMETILE::BG_BROKEN04;
			}

#pragma endregion

			TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx = BATTLECITY_TILE::NONE_BLOCK00;
		}
	}



	PhoenixTile.reserve(4);
	for (int i = 0; i < XSize * YSize; i++)
	{
		if (BATTLECITY_GAMETILE::BG_NONE == VectorTileInfo[i])
		{
			continue;
		}

		KOne* TOne = MomScene->create_kone(L"Tile");
		Tile* NewTile = TOne->add_component<Tile>();
		NewTile->set_tile({ 
			(float)(i % XSize) * TILEXSIZE, 
			(float)(i / XSize) * TILEYSIZE }, VectorTileInfo[i]);
		VectorTile.push_back(NewTile);


		if (BATTLECITY_GAMETILE::BG_PHOENIX01 == VectorTileInfo[i] ||
			BATTLECITY_GAMETILE::BG_PHOENIX02 == VectorTileInfo[i] ||
			BATTLECITY_GAMETILE::BG_PHOENIX03 == VectorTileInfo[i] || 
			BATTLECITY_GAMETILE::BG_PHOENIX04 == VectorTileInfo[i] )
		{
			PhoenixTile.push_back(NewTile);
		}
	}
	return 0;
}


void TileManager::update_broken()
{
	for (int i = 0; i < (int)PhoenixTile.size(); i++)
	{
		PhoenixTile[i]->set_tile((BATTLECITY_GAMETILE)((int)BATTLECITY_GAMETILE::BG_BROKEN01 + i));
		update_tile(PhoenixTile[i]);
	}
}

void TileManager::update_alltile()
{
	for (size_t i = 0; i < VectorTile.size(); i++)
	{
		if (BATTLECITY_GAMETILE::BG_WOOD_BLOCK != VectorTile[i]->tile_type())
		{
			VectorTile[i]->update_trans();
			VectorTile[i]->render(MapHdc);
		}
	}
}

void TileManager::update_tile(Tile* _Tile)
{
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	myBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(MapHdc, myBrush);
	Rectangle(MapHdc, 
		_Tile->kone()->pos().x, 
		_Tile->kone()->pos().y,
		_Tile->kone()->pos().x + _Tile->kone()->size().x,
		_Tile->kone()->pos().y + _Tile->kone()->size().y);
	SelectObject(MapHdc, oldBrush);
	DeleteObject(myBrush);

	if (false == _Tile->kone()->active())
	{
		return;
	}
	_Tile->render(MapHdc);
}
void TileManager::render()
{
	BitBlt(
		MomScene->kwindow()->bhdc(),
		STARTXPOS,
		STARTYPOS, 
		XSize * (TILEXSIZE), 
		XSize * (TILEXSIZE),
		MapHdc,
		0,
		0, 
		SRCCOPY);
}



void TileManager::release()
{
	RELEASE_PTR(pKTileManager);
}