#include "BackDeco.h"
#include "ComPlayer.h"


#include "KInputManager.h"
#include "KOne.h"
#include <Windows.h>




BackDeco::BackDeco()
{
}


BackDeco::~BackDeco()
{
}


bool BackDeco::init()
{
	fWallSpeed = 150.0f;

	return true;
}

void BackDeco::update()
{
	if (nullptr == pPlayer)
	{
		return;
	}

	bool LeftKey = KInputManager::instance()->is_press(VK_LEFT);
	bool RightKey = KInputManager::instance()->is_press(VK_RIGHT);

	if (false == pPlayer->almost_win())
	{
		if (true == LeftKey)
		{
			kone()->moving({ fWallSpeed * 1.0f, 0.0f });
		}
		else if (true == RightKey)
		{
			kone()->moving({ fWallSpeed * -1.0f, 0.0f });
		}
	}


	if (true == RightKey && kone()->size().x * -2.0f > kone()->pos().x - kone()->size().x)
	{
		kone()->pos(KPos2(800 + kone()->size().x, kone()->pos().y));
	}
	


	else if (true == LeftKey && 800 < kone()->pos().x - kone()->size().x)
	{
		kone()->pos(KPos2(kone()->size().x * -1.0f, kone()->pos().y));
	}
}