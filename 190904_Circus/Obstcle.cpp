#include "Obstcle.h"
#include "ComPlayer.h"
#include <KOne.h>



Obstcle::Obstcle()
{
}


Obstcle::~Obstcle()
{
}


void Obstcle::set_prop(const int& _Type, const bool& _Fast)
{
	eObType = (OBSTACLE_TYPE)_Type;
	bFast = _Fast;	
}

bool Obstcle::init()
{
	CircusObject::init();
	if (eObType != OBSTACLE_TYPE::OT_FIRE)
	{
		fObsSpeed = .0f;
	}

	else if (true == bFast)
	{
		fObsSpeed = 80.0f;
	}
	else
	{
		fObsSpeed = 50.0f;
	}
	return true;
}

void Obstcle::update()
{
	switch (eObType)
	{
	case Obstcle::OT_FIRE:
		update_fire();
		break;
	case Obstcle::OT_POT:
		update_pot();
		break;
	case Obstcle::OT_WINPAN:
		update_winpan();
		break;
	default:
		break;
	}
	update_colide();
}



void Obstcle::update_fire()
{
	CircusObject::update();
	kone()->moving(KPos2::Left * (fObsSpeed));
}
void Obstcle::update_pot()
{
	CircusObject::update();
}
void Obstcle::update_winpan()
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
}


void Obstcle::update_colide()
{
	float colsize = 30.0f;

	if (pPlayer->kone()->pos().y > 370 && 
		kone()->pos().x - colsize < pPlayer->kone()->pos().x &&
		kone()->pos().x + colsize > pPlayer->kone()->pos().x)
	{
		switch (eObType)
		{
		case Obstcle::OT_FIRE:
		case Obstcle::OT_POT:
			pPlayer->set_failed();
			break;
		case Obstcle::OT_WINPAN:
			pPlayer->set_win();
			break;
		default:
			break;
		}
	}
}