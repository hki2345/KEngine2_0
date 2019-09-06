#include "MapManager.h"

#include "BackDeco.h"
#include "Miter.h"

#include <KScene.h>
#include <KOne.h>


#include <KText_Render.h>
#include <KBitMap_Render.h>
#include <KBitMap_Animator.h>


MapManager::MapManager()
{
}


MapManager::~MapManager()
{
}

void MapManager::create(KScene* _Scene, ComPlayer* _Player)
{
	int BackSize = 12;

	std::vector<KOne*> VecBackGround;
	std::vector<KOne*> VecDeco;


	for (int i = 0; i < BackSize; i++)
	{
		VecBackGround.push_back(_Scene->create_kone(L"BackGround"));
		VecDeco.push_back(_Scene->create_kone(L"BackDeco"));

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



	for (size_t i = 0; i < 4; i++)
	{
		KOne* TOne = _Scene->create_kone(L"Miter");
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