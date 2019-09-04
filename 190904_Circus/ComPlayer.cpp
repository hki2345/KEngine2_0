#include "ComPlayer.h"

#include <KTimeManager.h>
#include <KInputManager.h>
#include "KOne.h"

#include <math.h>
#include <Windows.h>



ComPlayer::ComPlayer()
{
}


ComPlayer::~ComPlayer()
{
}



bool ComPlayer::init()
{
	fDirWalk[0] = -1.0f;
	fDirWalk[1] = 1.0f;
	fDirWalk[2] = .0f;


	fWalkSpeed = 100.0f;
	fwalk_distance = .0f;
	fmax_distance = 5000.0f;


	kone()->pos(KPos2(100, 450));
	fbottom = 450.0f;
	fJumpPower = 250.0f;

	ePlayerAct = ComPlayer::IDLE;
	return true;
}
void ComPlayer::update()
{
	update_input();
	switch (ePlayerAct)
	{
	case ComPlayer::IDLE:
		update_idle();
		break;
	case ComPlayer::JUMP:
		update_jump();
		break;
	case ComPlayer::WIN:
		update_win();
		break;
	case ComPlayer::DIE:
		update_die();
		break;
	default:
		break;
	}
}


bool ComPlayer::almost_win()
{
	if (fwalk_distance > fmax_distance - 300 &&
		fwalk_distance < fmax_distance + 300)
	{
		return true;
	}

	return false;
}


void ComPlayer::update_input()
{
	if (true == KInputManager::instance()->is_press(VK_LEFT))
	{
		ePlayerDir = fDirWalk[0];
	}
	else if (true == KInputManager::instance()->is_press(VK_RIGHT))
	{
		ePlayerDir = fDirWalk[1];
	}
	else
	{
		ePlayerDir = fDirWalk[2];
	}
	if (fwalk_distance < fmax_distance)
	{
		fwalk_distance += fWalkSpeed * ePlayerDir * KTimeManager::instance()->deltatime();
	}


	if (fwalk_distance > fmax_distance - 300 && 
		fwalk_distance < fmax_distance)
	{
		kone()->moving({ fWalkSpeed * ePlayerDir, 0 });
	}
}






void ComPlayer::update_idle()
{
	if (true == KInputManager::instance()->is_press(VK_SPACE))
	{
		ePlayerAct = ACT_STATE::JUMP;
	}
}


void ComPlayer::update_jump()
{
	fJumpTime += KTimeManager::instance()->deltatime();
	float T = cos(fJumpTime * 2);

	kone()->moving({ .0f, (T * fJumpPower) * -1.0f });

	if (fbottom <= kone()->pos().y)
	{
		ePlayerAct = ACT_STATE::IDLE;
		kone()->pos({ kone()->pos().x + 0, fbottom });
		fJumpTime = .0f;
	}
}


void ComPlayer::update_win()
{

}
void ComPlayer::update_die()
{
}