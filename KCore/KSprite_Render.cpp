#include "KSprite_Render.h"
#include <KResourceManager.h>

#include "KWindow.h"
#include "KTransform.h"
#include "KScene.h"
#include "KBitMap.h"



KSprite_Render::KSprite_Render()
{
}


KSprite_Render::~KSprite_Render()
{
}



void KSprite_Render::set_bit(
	const wchar_t* _Name /*= L"NONE"*/,
	const int& _Key /*= 0*/)
{
	MyBitMap = KResourceManager<KBitMap>::instance()->find(_Name);
	kscene()->insert_krender(this, _Key);

}
void KSprite_Render::change_bit(
	const wchar_t* _Name /*= L"NONE"*/)
{
	MyBitMap = KResourceManager<KBitMap>::instance()->find(_Name);
}
void KSprite_Render::set_split(const int& _X, const int& _Y)
{
	SplitX = _X;
	SplitY = _Y;

	VectorMySplit.clear();
	int SplitSizeX = ((int)MyBitMap->size().x / _X);
	int SplitSizeY = ((int)MyBitMap->size().y / _Y);

	for (int i = 0; i < _Y; i++)
	{
		for (int j = 0; j < _X; j++)
		{
			VectorMySplit.push_back(
				{ KPos2(j * SplitSizeX, i * SplitSizeY), KPos2((j + 1) * SplitSizeX , (i + 1) * SplitSizeY) });
		}
	}
}
void KSprite_Render::set_idx(const int& _X, const int& _Y)
{
	idx = _X + SplitX * _Y;
}


bool KSprite_Render::init()
{
	KRenderer::init();
	idx = 0;
	name(L"KSprite_Render");

	return true;
}

void KSprite_Render::render()
{
	TransparentBlt(
		kwindow()->bhdc(),
		RenderPos.x,
		RenderPos.y,
		MyTrans->Size.x,
		MyTrans->Size.y,
		MyBitMap->MyDC,
		VectorMySplit[idx].Start.x,
		VectorMySplit[idx].Start.y,
		VectorMySplit[idx].End.x,
		VectorMySplit[idx].End.y,
		RGB(255, 0, 255));
}
void KSprite_Render::render(HDC _Hdc)
{
	TransparentBlt(
		_Hdc,
		RenderPos.x,
		RenderPos.y,
		MyTrans->Size.x,
		MyTrans->Size.y,
		MyBitMap->MyDC,
		VectorMySplit[idx].Start.x,
		VectorMySplit[idx].Start.y,
		VectorMySplit[idx].End.x,
		VectorMySplit[idx].End.y,
		RGB(255, 0, 255));
}