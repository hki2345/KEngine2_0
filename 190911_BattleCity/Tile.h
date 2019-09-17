#pragma once
#include <KComponent.h>
#include <BattleTile.h>
#include <KVector.h>
#include <Windows.h>


class KSprite_Render;
class KRect_Collision;
class KScene;
class KOne;
class Tile : public KComponent
{
public:
	Tile();
	~Tile();


private:
	KSprite_Render* MyRenderer;
	KRect_Collision* TankCollider;
	KPos2 ScreenPos;

	BATTLECITY_GAMETILE eTileType;

public:
	void create();
	void set_tile(const BATTLECITY_GAMETILE& _Info);
	void set_tile(const KPos2& _Pos, const BATTLECITY_GAMETILE& _Info);

	void update_trans();
	void render(HDC _Hdc);
	bool collision_bullet(const KPos2& _Dir, const KPos2& _Pos);
	inline BATTLECITY_GAMETILE& tile_type()
	{
		return eTileType;
	}
};

