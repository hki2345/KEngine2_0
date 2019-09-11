#pragma once
#include <vector>
#include <BattleTile.h>
#include <KVector.h>



class KScene;
class Tile;
class TileManager
{
private:
	// 본체에서는 해야하니까
	TileManager() {} /* = delete*/;
	TileManager(const TileManager& _Other) = delete;
	TileManager(const TileManager&& _Other) = delete;
	void operator=(const TileManager& _Other) = delete;
	~TileManager() {};
	static TileManager* pKTileManager;

public:
	static TileManager* instance()
	{
		if (nullptr == pKTileManager)
		{
			pKTileManager = new TileManager();
		}

		return pKTileManager;
	}


private:
	KScene* MomScene;
	
	int XSize;
	int YSize;

public:
	void create(KScene* _Scene);
	bool init(const wchar_t* _Name);
	void release();

	inline KRect tilemap_size()
	{
		KRect Tmp;
		Tmp.Start.x = STARTXPOS;
		Tmp.Start.y = STARTYPOS;

		Tmp.Size.x = XSize * ((float)TILEXSIZE - 1.5f) + Tmp.Start.x;
		Tmp.Size.y = YSize * ((float)TILEYSIZE - 1.5f) + Tmp.Start.y;

		return Tmp;
	}
};

