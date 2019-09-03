#include "KBitMap_Render.h"
#include <KResourceManager.h>
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
}

bool KBitMap_Render::init()
{
	MyBitMap = nullptr;
	
	return true;
}

void KBitMap_Render::update()
{
}

void KBitMap_Render::release()
{

}
void KBitMap_Render::render()
{

}