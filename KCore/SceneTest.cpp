#include "SceneTest.h"
#include "KOne.h"
#include "ComTest.h"


#include "KCore.h"
#include "KInputManager.h"
#include "KSceneManager.h"


#include <KFileStream.h>
#include <KPathManager.h>


SceneTest::SceneTest()
{
	
}


SceneTest::~SceneTest()
{
	int a = 0;
}

bool SceneTest::init()
{
	KScene::init();

	KOne* NONE = create_kone(L"TESTONE");
	NONE->add_component<ComTest>();

	cc.c = 3;
	KPathManager::instance()->input_wchar(cc.Name, sizeof(cc.Name), L"ELSA");
	cc.o = 3.4;
	cc.x = 12.3f;
	cc.y = 323.5f;
	cc.z = 1;

	KFileStream::instance()->write_file<TEST>(L"ELSA.elsa", cc);

	TEST dd;

	KFileStream::instance()->read_file<TEST>(L"ELSA.elsa", dd);

	return true;
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

	Value = KInputManager::instance()->is_press(VK_RIGHT);

	if (true == Value)
	{
		KSceneManager::instance()->change_scene(L"Test2");
	}

}