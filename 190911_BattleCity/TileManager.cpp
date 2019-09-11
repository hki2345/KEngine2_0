#include "TileManager.h"
#include "Tile.h"


#include <KMacro.h>
#include <KFileStream.h>
#include <KScene.h>
#include <KOne.h>




TileManager* TileManager::pKTileManager =nullptr;

void TileManager::create(KScene* _Scene)
{
	XSize = 13 * 2;
	YSize = 13 * 2;
	MomScene = _Scene;
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

			if (BATTLECITY_TILE::BROWN_BLOCK00 == TmpVec[x / 2 + ((XSize / 2) * (y / 2))].Idx)
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




	for (int i = 0; i < XSize * YSize; i++)
	{
		KOne* TOne = MomScene->create_kone(L"Tile");
		Tile* NewTile = TOne->add_component<Tile>();
		NewTile->set_tile({ (float)(i % XSize) * TILEXSIZE, (float)(i / XSize) * TILEYSIZE }, VectorTileInfo[i]);
	}
	return 0;
}


void TileManager::release()
{
	RELEASE_PTR(pKTileManager);
}