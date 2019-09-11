#pragma once
#include <KComponent.h>
#include <BattleTile.h>
#include <KVector.h>

class KSprite_Render;
class KScene;
class KOne;
class Tile : public KComponent
{
public:
	Tile();
	~Tile();


private:
	KSprite_Render* MyRenderer;
	KPos2 ScreenPos;

public:
	void create();
	void set_tile(const KPos2& _Pos, const BATTLECITY_GAMETILE& _Info);
};

