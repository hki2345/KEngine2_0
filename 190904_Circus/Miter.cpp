#include "Miter.h"
#include "ComPlayer.h"

#include <KScene.h>
#include <KOne.h>


#include <KBitMap_Render.h>




Miter::Miter()
{
}


Miter::~Miter()
{
}

bool Miter::init()
{
	CircusObject::init();
	pBitRender = kone()->get_component< KBitMap_Render>();
	return true;
}