#include "OutroScene.h"
#include <KText_Render.h>
#include <KOne.h>

#include <KWindowManager.h>
#include <KSceneManager.h>
#include <KInputManager.h>
#include <KTimeManager.h>

#include "PlayerManager.h"


OutroScene::OutroScene()
{
}


OutroScene::~OutroScene()
{
}



void OutroScene::create()
{
	KScene::create();
	for (int i = 0; i < 15; i++)
	{
		VectorUI.push_back(create_kone(L"OutroUI"));
	}
	int FSize = 20;

	KText_Render* Text1 = VectorUI[0]->add_component< KText_Render>();
	Text1->set_font(L"�ְ� ����", FSize, 10, L"DungGeunMo", RGB(255, 94, 0));

	ActionText.push_back(VectorUI[1]->add_component< KText_Render>());
	ActionText[0]->set_font(L"����", FSize, 10, L"DungGeunMo", RGB(255, 187, 0));

	ActionText.push_back(VectorUI[2]->add_component< KText_Render>());
	ActionText[1]->set_font(L"�������� ", FSize, 10, L"DungGeunMo", RGB(255, 255, 255));

	Text1 = VectorUI[3]->add_component< KText_Render>();
	Text1->set_font(L"�÷��̾�1 ", FSize, 10, L"DungGeunMo", RGB(255, 94, 0), TA_RIGHT);

	ActionText.push_back(VectorUI[4]->add_component< KText_Render>());
	ActionText[2]->set_font(L"���� ����", FSize, 10, L"DungGeunMo", RGB(255, 187, 0), TA_RIGHT);



	ActionText.push_back(VectorUI[5]->add_component< KText_Render>());
	ActionText[3]->set_font(L"1456 ��", FSize, 10, L"DungGeunMo", RGB(255, 255, 255), TA_RIGHT);
	ActionText.push_back(VectorUI[6]->add_component< KText_Render>());
	ActionText[4]->set_font(L"14 ų", FSize, 10, L"DungGeunMo", RGB(255, 255, 255), TA_LEFT);


	Text1 = VectorUI[7]->add_component< KText_Render>();
	Text1->set_font(L"�հ� ", FSize, 10, L"DungGeunMo", RGB(255, 255, 255), TA_RIGHT);
	ActionText.push_back(VectorUI[8]->add_component< KText_Render>());
	ActionText[5]->set_font(L"123455", FSize, 10, L"DungGeunMo", RGB(255, 255, 255), TA_LEFT);
}
bool OutroScene::init()
{
	KScene::init();
	KWindowManager::instance()->backcolor(RGB(0, 0, 0));


	VectorUI[0]->pos({ 300.0f, 50.0f });
	VectorUI[1]->pos({ 550.0f, 50.0f });
	VectorUI[2]->pos({ 400.0f, 100.0f });

	VectorUI[3]->pos({ 280.0f, 150.0f });
	VectorUI[4]->pos({ 280.0f, 200.0f });

	VectorUI[5]->pos({ 280.0f, 250.0f });
	VectorUI[6]->pos({ 300.0f, 250.0f });

	VectorUI[7]->pos({ 280.0f, 450.0f });
	VectorUI[8]->pos({ 300.0f, 450.0f });


	fOutCurTime = .0f;
	fOutTime = 20.0f;

	ActionText[0]->set_text(std::to_wstring(PlayerManager::instance()->iHighScore).c_str());


	std::wstring Tmp = L"";

	Tmp = L"�������� ";
	Tmp += std::to_wstring(PlayerManager::instance()->iStage).c_str();
	ActionText[1]->set_text(Tmp.c_str());

	Tmp = std::to_wstring(PlayerManager::instance()->iScore).c_str();
	Tmp += L"";
	ActionText[2]->set_text(Tmp.c_str());


	Tmp = std::to_wstring(PlayerManager::instance()->iScore).c_str();
	Tmp += L" ��";
	ActionText[3]->set_text(Tmp.c_str());


	Tmp = std::to_wstring(PlayerManager::instance()->iKill).c_str();
	Tmp += L" ų";
	ActionText[4]->set_text(Tmp.c_str());


	Tmp = std::to_wstring(PlayerManager::instance()->iKill).c_str();
	Tmp += L" ų";
	ActionText[5]->set_text(Tmp.c_str());


	return true;
}
void OutroScene::update()
{
	KScene::update();
	fOutCurTime += KTimeManager::instance()->deltatime();
	if (
		fOutCurTime >= fOutTime ||
		true == KInputManager::instance()->is_down(VK_EXECUTE))
	{
		fOutCurTime = .0f;
		KSceneManager::instance()->change_scene(L"Intro");
	}
}