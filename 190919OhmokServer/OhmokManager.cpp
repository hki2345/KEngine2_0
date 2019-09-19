#include "OhmokManager.h"
#include "190919OhmokClient.h"

#include <KSceneManager.h>
#include <KScene.h>

#include <KOne.h>
#include <KBitMap_Render.h>
#include <KWindow.h>

OhmokManager* OhmokManager::pOhmokManager = nullptr;

void OhmokManager::create()
{
	MyScene = KSceneManager::instance()->create_scene(L"OhMok");
	KSceneManager::instance()->change_scene(L"OhMok");

	KOne* OhmokPan = MyScene->create_kone(L"Pan");
	OhmokPan->size(MyScene->kwindow()->size());
	OhmokPan->add_component<KBitMap_Render>()->set_bit(L"res\\OhmokPan.bmp");

	OneX = OhmokPan->size().x / (PANLINE + 2);

	VectorBlack.reserve(BLACKSIZE);
	for (int i = 0; i < BLACKSIZE; i++)
	{
		VectorBlack.push_back(MyScene->create_kone(L"BlackDole"));
		VectorBlack[i]->size(OneX + 5);
		VectorBlack[i]->pos(OneX - OneX * .5f);
		VectorBlack[i]->add_component<KBitMap_Render>()->set_bit(L"res\\BlackStone.bmp", 5);
	}

	VectorWhite.reserve(WHITESIZE);
	for (int i = 0; i < WHITESIZE; i++)
	{
		VectorWhite.push_back(MyScene->create_kone(L"WhiteDole"));
		VectorWhite[i]->size(OneX);
		VectorWhite[i]->add_component<KBitMap_Render>()->set_bit(L"res\\WhiteStone.bmp", 5);
	}

}

void OhmokManager::update()
{

}