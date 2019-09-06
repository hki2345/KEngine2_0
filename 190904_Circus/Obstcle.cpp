#include "Obstcle.h"
#include "ComPlayer.h"

#include <KScene.h>
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
		fObsSpeed = 100.0f;
	}
	else
	{
		fObsSpeed = 80.0f;
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
		//update_winpan();
		break;
	default:
		break;
	}
	update_colide();
}



void Obstcle::update_fire()
{
	if (KPos2::Left == kscene()->outof_screen(kone()))
	{
		kone()->active(false);
	}

	kone()->moving_delta(KPos2::Left * (fObsSpeed));


}
void Obstcle::update_pot()
{
	if (KPos2::Left == kscene()->outof_screen(kone()))
	{
		kone()->active(false);
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