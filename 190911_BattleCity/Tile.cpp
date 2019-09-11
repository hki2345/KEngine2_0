#include "Tile.h"
#include <KSprite_Render.h>
#include <KSprite_Render.h>
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
	ScreenPos = { STARTXPOS , STARTYPOS };
	kone()->size({ TILEXSIZE, TILEYSIZE });
	MyRenderer = kone()->add_component<KSprite_Render>();
	MyRenderer->init();
}
void Tile::set_tile(const KPos2& _Pos, const BATTLECITY_GAMETILE& _Info)
{
	kone()->pos(_Pos + ScreenPos);

	MyRenderer->set_bit(L"res\\TileSpriteSub.bmp");
	MyRenderer->set_split(3, 5);
	MyRenderer->set_idx((int)_Info);
}