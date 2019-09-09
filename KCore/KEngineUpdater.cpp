#include "KEngineUpdater.h"
#include "KInputManager.h"
#include "KCore.h"


KEngineUpdater::KEngineUpdater()
{
}


KEngineUpdater::~KEngineUpdater()
{
}


void KEngineUpdater::update()
{
	bool Value = KInputManager::instance()->is_press(0x58);

	if (true == Value)
	{
		KCore::instance()->shut_down();
	}
}