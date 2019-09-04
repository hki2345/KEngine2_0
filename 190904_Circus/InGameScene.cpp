#include "InGameScene.h"
#include "ComPlayer.h"
#include "BackDeco.h"

#include <KBitMap_Render.h>
#include <KOne.h>




InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}



bool InGameScene::init()
{
	int BackSize = 15;

	KScene::init();


	OnePlayer = create_kone(L"Player");
	ComPlayer* ComTmp = OnePlayer->add_component<ComPlayer>();
	OnePlayer->size(KPos2(80, 80));


	KBitMap_Render* BITREN = OnePlayer->add_component<KBitMap_Render>();
	BITREN->set_bit(L"Circus\\player0.bmp", 10);

	for (int i = 0; i < BackSize; i++)
	{
		VecBackGround.push_back(create_kone(L"BackGround"));
		VecDeco.push_back(create_kone(L"BackDeco"));
	}

	for (int i = 0; i < BackSize; i++)
	{
		KBitMap_Render* BRE = VecBackGround[i]->add_component<KBitMap_Render>();
		BRE->set_bit(L"Circus\\back.bmp", 0);
		KBitMap_Render* DRE = VecDeco[i]->add_component<KBitMap_Render>();

		if (i == 5)
		{
			DRE->set_bit(L"Circus\\back_deco.bmp", 1);
		}
		else
		{
			DRE->set_bit(L"Circus\\back_normal.bmp", 1);
		}

		VecBackGround[i]->pos(KPos2(i * 95, 270));
		VecDeco[i]->pos(KPos2(i * 75, 200));

		VecBackGround[i]->size({ 100, 300 });
		VecDeco[i]->size({ 80, 80 });

		BackDeco* Tmp = VecBackGround[i]->add_component<BackDeco>();
		Tmp->set_player(ComTmp);

		Tmp = VecDeco[i]->add_component<BackDeco>();
		Tmp->set_player(ComTmp);
	}




	return true;
}
void InGameScene::update()
{
	KScene::update();

}