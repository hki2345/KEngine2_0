#include "BackDeco.h"
#include "ComPlayer.h"
#include <KBitMap_Animator.h>


#include "KInputManager.h"
#include "KOne.h"
#include <Windows.h>




BackDeco::BackDeco() : bActiveDeco(false)
{
}


BackDeco::~BackDeco()
{
}


bool BackDeco::init()
{
	CircusObject::init();
	KBitMap_Animator* TAni = kone()->get_component<KBitMap_Animator>();

	if (nullptr != TAni)
	{
		TAni->change_animation(L"Idle");
	}

	return true;
}

void BackDeco::update()
{
	CircusObject::update();

	if (true == pPlayer->check_win() && true == bActiveDeco)
	{
		kone()->get_component<KBitMap_Animator>()->change_animation(L"Win");
	}
}