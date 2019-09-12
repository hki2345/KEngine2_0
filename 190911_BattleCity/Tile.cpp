#include "Tile.h"
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

	MyRenderer->set_bit(L"res\\TileSpriteSub.bmp");
	MyRenderer->set_split(3, 5);
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
}

bool& Tile::col_check()
{
	return MyCollider->is_col();
}