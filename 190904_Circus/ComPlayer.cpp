#include "ComPlayer.h"
#include <KBitMap_Animator.h>
#include "GameManager.h"

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

void ComPlayer::create()
{
}

bool ComPlayer::init()
{
	if (nullptr == pAnimator) 
	{
		pAnimator = kone()->get_component<KBitMap_Animator>();
	}

	fDirWalk[0] = -1.0f;
	fDirWalk[1] = 1.0f;
	fDirWalk[2] = .0f;


	fWalkSpeed = 100.0f;
	fwalk_distance = .0f;
	fmax_distance = 1000.0f;


	kone()->pos(KPos2(100, 440));
	fbottom = 440.0f;
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
	case ComPlayer::RUN:
		update_run();
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


int ComPlayer::scroll_dir()
{
	if (ACT_STATE::DIE == ePlayerAct ||
		ACT_STATE::WIN == ePlayerAct)
	{
		return 0 ;
	}

	if (fwalk_distance > fmax_distance - 300 &&
		fwalk_distance < fmax_distance + 300)
	{
		return 0;
	}

	return (int)ePlayerDir;
}


void ComPlayer::update_input()
{
	if (ACT_STATE::DIE == ePlayerAct || 
		ACT_STATE::WIN == ePlayerAct)
	{
		return;
	}

	if (ACT_STATE::JUMP == ePlayerAct)
	{
		update_move();
		return;
	}

	if (true == KInputManager::instance()->is_press(VK_LEFT))
	{
		ePlayerDir = fDirWalk[0];
		ePlayerAct = ACT_STATE::RUN;
	}
	else if (true == KInputManager::instance()->is_press(VK_RIGHT) )
	{
		ePlayerDir = fDirWalk[1];
		ePlayerAct = ACT_STATE::RUN;
	}
	else
	{
		ePlayerDir = fDirWalk[2];
		ePlayerAct = ACT_STATE::IDLE;
	}	
}




void ComPlayer::set_win()
{
	ePlayerAct = ACT_STATE::WIN;
	kone()->pos(KPos2(kone()->pos().x, 400));
	if (true == KInputManager::instance()->is_press(VK_SPACE))
	{
		GameManager::instance()->reset_game();
	}
}
void ComPlayer::set_failed()
{
	ePlayerAct = ACT_STATE::DIE;
	if (true == KInputManager::instance()->is_press(VK_SPACE))
	{
		GameManager::instance()->reset_game();
	}
}

bool ComPlayer::check_win()
{
	if (ePlayerAct == ACT_STATE::WIN)
	{
		return true;
	}

	return false;
}

void ComPlayer::update_idle()
{
	pAnimator->change_animation(L"Idle");
}

void ComPlayer::update_run()
{
	pAnimator->change_animation(L"Run");
	update_move();
	if (true == KInputManager::instance()->is_press(VK_SPACE))
	{
		ePlayerAct = ACT_STATE::JUMP;
	}
}

void ComPlayer::update_jump()
{
	pAnimator->change_animation(L"Jump");
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
	pAnimator->change_animation(L"Win");
	if (true == KInputManager::instance()->is_press(VK_SPACE))
	{
		GameManager::instance()->reset_game();
	}

}
void ComPlayer::update_die()
{
	pAnimator->change_animation(L"Die"); 
	if (true == KInputManager::instance()->is_press(VK_SPACE))
	{
		GameManager::instance()->reset_game();
	}
}

void ComPlayer::update_move()
{
	if (fwalk_distance < fmax_distance)
	{
		fwalk_distance += fWalkSpeed * ePlayerDir * KTimeManager::instance()->deltatime();
	}

	else
	{
		fwalk_distance = fmax_distance;
	}


	if (fwalk_distance > fmax_distance - 300 &&
		fwalk_distance <= fmax_distance)
	{
		kone()->moving({ fWalkSpeed * ePlayerDir, 0 });
	}
}