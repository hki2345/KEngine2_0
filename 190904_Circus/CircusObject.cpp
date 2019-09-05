#include "CircusObject.h"
#include "ComPlayer.h"
#include <KOne.h>




CircusObject::CircusObject()
{
}


CircusObject::~CircusObject()
{
}

void CircusObject::create()
{
	MyOriginPos = kone()->pos();
}

bool CircusObject::init()
{
	kone()->pos(MyOriginPos);
	fColHeight = 300.0f;
	fBaseSpeed = 150.0f;
	fObsSpeed = .0f;


	return true;
}
void CircusObject::update()
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
		kone()->moving({ KPos2::Left * (fBaseSpeed)});
	}



	if (KPos2::Left == out_ofscreen())
	{
		kone()->pos(KPos2(800 + kone()->size().x, kone()->pos().y));
	}
	else if (KPos2::Right == out_ofscreen())
	{
		kone()->pos(KPos2(kone()->size().x * -1.0f, kone()->pos().y));
	}
}


KPos2 CircusObject::out_ofscreen()
{
	if (kone()->size().x * -2.0f > kone()->pos().x - kone()->size().x)
	{
		return KPos2::Left;
	}

	else if (800 < kone()->pos().x - kone()->size().x)
	{
		return KPos2::Right;
	}

	return KPos2::Zero;
}