#include "KBitMap_Render.h"
#include <KResourceManager.h>

#include "KScene.h"
#include "KWindow.h"
#include "KTransform.h"
#include "KBitMap.h"
#include "KOne.h"



KBitMap_Render::KBitMap_Render()
{
}


KBitMap_Render::~KBitMap_Render()
{
}


void KBitMap_Render::set_bit(const wchar_t* _Name /*= L"NONE"*/)
{
	MyBitMap = KResourceManager<KBitMap>::instance()->find(_Name);
	kscene()->insert_krender(this);
}

bool KBitMap_Render::init()
{
	KRenderer::init();
	MyBitMap = nullptr;
	name(L"BitMap_Render");
		
	return true;
}

void KBitMap_Render::update()
{

}

void KBitMap_Render::render()
{
	BitBlt(kwindow()->bhdc(), 
		(int)MyTrans->pos().x,
		(int)MyTrans->pos().y,
		MyBitMap->size().ix,
		MyBitMap->size().iy,
		MyBitMap->MyDC, 0,0,SRCCOPY);
}