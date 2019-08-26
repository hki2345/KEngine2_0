#include "SceneTest.h"
#include "KOne.h"
#include "ComTest.h"


#include "KCore.h"
#include "KInputManager.h"


SceneTest::SceneTest()
{
	KOne* NONE = create_kone(L"TESTONE");
	NONE->add_component<ComTest>();
}


SceneTest::~SceneTest()
{
	int a = 0;
}


#include <Windows.h>
void SceneTest::update()
{
	KScene::update();

	bool Value = KInputManager::instance()->is_press(0x58);

	if (true == Value)
	{
		KCore::instance()->shut_down();
	}
}