#include "Miter.h"
#include "ComPlayer.h"
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

void Miter::update()
{
	if (nullptr == pPlayer)
	{
		return;
	}

	int Tmp = pPlayer->scroll_dir();
	if (-1 == Tmp)
	{
		kone()->moving(KPos2::Right * (fBaseSpeed));
	}
	else if (1 == Tmp)
	{
		kone()->moving({ KPos2::Left * (fBaseSpeed) });
	}



	if (KPos2::Left == out_ofscreen())
	{
		pBitRender->active(false);
	}
	else if (KPos2::Right == out_ofscreen())
	{
		pBitRender->active(false);
	}
	else if(false == pBitRender->active())
	{
		pBitRender->active(true);
	}
}