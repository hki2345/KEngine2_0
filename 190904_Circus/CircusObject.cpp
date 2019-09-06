#include "CircusObject.h"
#include "ComPlayer.h"
#include <KScene.h>
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
	if (KPos2::Left == kscene()->outof_screen(kone()))
	{
		kone()->pos(KPos2(kscene()->SceneCamPos.x + 800, kone()->pos().y));
	}
	else if (KPos2::Right == kscene()->outof_screen(kone()))
	{
		kone()->pos(KPos2(kscene()->SceneCamPos.x - kone()->size().x, kone()->pos().y));
	}
}