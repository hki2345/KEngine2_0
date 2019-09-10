#include "KBitMap_Render.h"
#include <KResourceManager.h>

#include "KScene.h"
#include "KWindow.h"
#include "KTransform.h"
#include "KBitMap.h"
#include "KOne.h"


#pragma comment(lib, "msimg32.lib")


KBitMap_Render::KBitMap_Render()
{
}


KBitMap_Render::~KBitMap_Render()
{
}


void KBitMap_Render::set_bit(
	const wchar_t* _Name /*= L"NONE"*/,
	const int& _Key /*= 0*/, 
	const bool& _bBitRender)
{
	bBitRender = _bBitRender;
	MyBitMap = KResourceManager<KBitMap>::instance()->find(_Name);
	kscene()->insert_krender(this, _Key);
}


void KBitMap_Render::change_bit(
	const wchar_t* _Name /*= L"NONE"*/, 
	const bool& _bBitRender /*= false*/)
{
	bBitRender = _bBitRender;
	MyBitMap = KResourceManager<KBitMap>::instance()->find(_Name);
}

bool KBitMap_Render::init()
{
	KRenderer::init();
	name(L"BitMap_Render");
		
	return true;
}
void KBitMap_Render::render()
{
	if (false == bRender)
	{
		return;
	}


	if (true == bBitRender)
	{
		BitBlt(
			kwindow()->bhdc(),
			RenderPos.x,
			RenderPos.y,
			MyTrans->Size.x,
			MyTrans->Size.y,
			MyBitMap->MyDC,
			0,
			0,
			SRCCOPY);
	}

	if (false == bBitRender)
	{
		TransparentBlt(
			kwindow()->bhdc(),
			RenderPos.x,
			RenderPos.y,
			MyTrans->Size.x,
			MyTrans->Size.y,
			MyBitMap->MyDC,
			0,
			0,
			MyBitMap->size().x,
			MyBitMap->size().y,
			RGB(255, 0, 255));
	}
}

void KBitMap_Render::render(HDC _Hdc)
{
	if (true == bBitRender)
	{
		BitBlt(
			_Hdc,
			MyTrans->Pos.x,
			MyTrans->Pos.y,
			MyTrans->Size.x,
			MyTrans->Size.y,
			MyBitMap->MyDC,
			0,
			0,
			SRCCOPY);
	}

	if (false == bBitRender)
	{
		TransparentBlt(
			_Hdc,
			MyTrans->Pos.x,
			MyTrans->Pos.y,
			MyTrans->Size.x,
			MyTrans->Size.y,
			MyBitMap->MyDC,
			0,
			0,
			MyBitMap->size().x,
			MyBitMap->size().y,
			RGB(255, 0, 255));
	}
}