#include "InGameScene.h"
#include "ComPlayer.h"
#include "BackDeco.h"
#include "Obstcle.h"
#include "Miter.h"


#include <KText_Render.h>
#include <KBitMap_Render.h>
#include <KBitMap_Animator.h>
#include <KOne.h>




InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}

void InGameScene::create()
{
	KScene::create();
	create_backboard();
	create_player();
	create_wall(OnePlayer->get_component<ComPlayer>());
	create_obstacle(OnePlayer->get_component<ComPlayer>());
	create_miter(OnePlayer->get_component<ComPlayer>());
}



void InGameScene::create_backboard()
{
	KOne* TOne = create_kone(L"BackBoard");
	TOne->size(KPos2(800, 600));

	KBitMap_Render* BITREN = TOne->add_component<KBitMap_Render>();
	BITREN->set_bit(L"Circus\\BackBoard.bmp", 0);
}

void InGameScene::create_player()
{
	OnePlayer = create_kone(L"Player");
	ComPlayer* ComTmp = OnePlayer->add_component<ComPlayer>();
	OnePlayer->size(KPos2(80, 80));


	KBitMap_Animator* BITREN = OnePlayer->add_component<KBitMap_Animator>();
	std::vector<std::wstring> Tmp;
	Tmp.push_back(L"Circus\\player0.bmp");
	Tmp.push_back(L"Circus\\player1.bmp");
	Tmp.push_back(L"Circus\\player2.bmp");
	BITREN->insert_animation(L"Run", Tmp, 10);

	Tmp.clear();
	Tmp.push_back(L"Circus\\player0.bmp");
	BITREN->insert_animation(L"Idle", Tmp, 10);

	Tmp.clear();
	Tmp.push_back(L"Circus\\player2.bmp");
	BITREN->insert_animation(L"Jump", Tmp, 10);


	Tmp.clear();
	Tmp.push_back(L"Circus\\die.bmp");
	BITREN->insert_animation(L"Die", Tmp, 10);


	Tmp.clear();
	Tmp.push_back(L"Circus\\win.bmp");
	Tmp.push_back(L"Circus\\win2.bmp");
	BITREN->insert_animation(L"Win", Tmp, 10);
}



void InGameScene::create_wall(ComPlayer* _Player)
{
	int BackSize = 15;

	for (int i = 0; i < BackSize; i++)
	{
		VecBackGround.push_back(create_kone(L"BackGround"));
		VecDeco.push_back(create_kone(L"BackDeco"));

		VecBackGround[i]->pos(KPos2((float)i * 95.0f, 270.0f));
		VecDeco[i]->pos(KPos2((float)i * 75.0f, 200.0f));

		VecBackGround[i]->size({ 100.0f, 300.0f });
		VecDeco[i]->size({ 80.0f, 80.0f });
	}

	for (int i = 0; i < BackSize; i++)
	{
		KBitMap_Render* BRE = VecBackGround[i]->add_component<KBitMap_Render>();
		BRE->set_bit(L"Circus\\back.bmp", 5);

		BackDeco* Tmp = VecBackGround[i]->add_component<BackDeco>();
		Tmp->set_player(_Player);

		Tmp = VecDeco[i]->add_component<BackDeco>();
		Tmp->set_player(_Player);

		if (i == 5)
		{
			KBitMap_Render* DRE = VecDeco[i]->add_component<KBitMap_Render>();
			DRE->set_bit(L"Circus\\back_deco.bmp", 6);
		}
		else
		{
			Tmp->set_activedeco();
			KBitMap_Animator* DRE = VecDeco[i]->add_component<KBitMap_Animator>();
			std::vector<std::wstring> Tmp;
			Tmp.push_back(L"Circus\\back_normal.bmp");
			DRE->insert_animation(L"Idle", Tmp, 6);

			Tmp.clear();
			Tmp.push_back(L"Circus\\back_normal.bmp");
			Tmp.push_back(L"Circus\\back_normal2.bmp");
			DRE->insert_animation(L"Win", Tmp, 6);
		}

	}
}






void InGameScene::create_obstacle(ComPlayer* _Player)
{
	for (size_t i = 0; i < 4; i++)
	{
		KOne* TOne = create_kone(L"Obstacle");
			   		 
		if (i < 2)
		{
			TOne->size({ 30.0f, 150.0f });
			TOne->pos({ 400.0f + i * 350.0f, 290.0f });


			Obstcle* ComTmp = TOne->add_component<Obstcle>();
			ComTmp->set_player(_Player);
			ComTmp->set_prop(0, false);
			create_fire(TOne);
		}
		else if(i == 2)
		{
			TOne->size({ 30.0f, 150.0f });
			TOne->pos({ 400.0f + i * 350.0f, 290.0f });

			Obstcle* ComTmp = TOne->add_component<Obstcle>();
			ComTmp->set_player(_Player);
			ComTmp->set_prop(0, true);
			create_fire(TOne);
		}
		else if (i > 2)
		{
			TOne->size({ 70.0f, 70.0f });
			TOne->pos({ .0f + i * 350.0f, 440.0f });

			Obstcle* ComTmp = TOne->add_component<Obstcle>();
			ComTmp->set_player(_Player);
			ComTmp->set_prop(1, false);
			create_pot(TOne);
		}
	}


	KOne* TOne = create_kone(L"WinPan");
	TOne->size({ 120.0f, 70.0f });
	TOne->pos({ 1500.0f, 460.0f });

	Obstcle* ComTmp = TOne->add_component<Obstcle>();
	ComTmp->set_player(_Player);
	ComTmp->set_prop(2, false);
	create_winpan(TOne);
}

void InGameScene::create_fire(KOne* _KOne)
{
	KBitMap_Animator* BRE = _KOne->add_component<KBitMap_Animator>();
	std::vector<std::wstring> Tmp;
	Tmp.push_back(L"Circus\\enemy_1b.bmp");
	Tmp.push_back(L"Circus\\enemy_b.bmp");
	BRE->insert_animation(L"Idle", Tmp, 9);
	BRE->pivot(KPos2(-15.0f, 0.0f));

	BRE = _KOne->add_component<KBitMap_Animator>();
	Tmp.clear();
	Tmp.push_back(L"Circus\\enemy_1f.bmp");
	Tmp.push_back(L"Circus\\enemy_f.bmp");
	BRE->insert_animation(L"Idle", Tmp, 11);
	BRE->pivot(KPos2(15.0f, 0.0f));
}


void InGameScene::create_pot(KOne* _KOne)
{
	KBitMap_Animator* BRE = _KOne->add_component<KBitMap_Animator>();
	std::vector<std::wstring> Tmp;
	Tmp.push_back(L"Circus\\front.bmp");
	Tmp.push_back(L"Circus\\front2.bmp");
	BRE->insert_animation(L"Idle", Tmp, 9);
}


void InGameScene::create_winpan(KOne* _KOne)
{
	KBitMap_Animator* BRE = _KOne->add_component<KBitMap_Animator>();
	std::vector<std::wstring> Tmp;
	Tmp.push_back(L"Circus\\end.bmp");
	BRE->insert_animation(L"Idle", Tmp, 9);
}



void InGameScene::create_miter(ComPlayer* _Player)
{
	for (size_t i = 0; i < 4; i++)
	{
		KOne* TOne = create_kone(L"Miter");
		TOne->size({ 100.0f, 30.0f });
		TOne->pos({ 400.0f + i * 400.0f, 520.0f });


		Miter* ComTmp = TOne->add_component<Miter>();
		ComTmp->set_player(_Player);

		KBitMap_Render* BRE = TOne->add_component<KBitMap_Render>();
		BRE->set_bit(L"Circus\\miter.bmp", 6);


		KText_Render* TRE = TOne->add_component<KText_Render>();
		TRE->set_text(std::to_wstring(40 - (i + 1) * 10).c_str(), L"DungGeunMo", 15, 7);
		TRE->pivot(KPos2(50, 7));
	}
}