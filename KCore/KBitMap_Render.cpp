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


void KBitMap_Render::set_bit(const wchar_t* _Name /*= L"NONE"*/, const int& _Key /*= 0*/)
{
	MyBitMap = KResourceManager<KBitMap>::instance()->find(_Name);
	kscene()->insert_krender(this, _Key);
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