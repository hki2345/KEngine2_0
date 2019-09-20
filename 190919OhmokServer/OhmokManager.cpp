#include "OhmokManager.h"
#include "190919OhmokClient.h"

#include <KInputManager.h>
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

	LineSize = KPos2(OhmokPan->size().x / (PANLINE + 1), OhmokPan->size().y / (PANLINE + 1));

	VectorBlack.reserve(BLACKSIZE);
	for (int i = 0; i < BLACKSIZE; i++)
	{
		VectorBlack.push_back(MyScene->create_kone(L"BlackDole"));
		VectorBlack[i]->size(DOLESIZE);
		VectorBlack[i]->add_component<KBitMap_Render>()->set_bit(L"res\\BlackStone.bmp", 5);
		VectorBlack[i]->active(false);
	}

	VectorWhite.reserve(WHITESIZE);
	for (int i = 0; i < WHITESIZE; i++)
	{
		VectorWhite.push_back(MyScene->create_kone(L"WhiteDole"));
		VectorWhite[i]->size(DOLESIZE);
		VectorWhite[i]->add_component<KBitMap_Render>()->set_bit(L"res\\WhiteStone.bmp", 5);
		VectorWhite[i]->active(false);
	}


	VectorPan.reserve(PANSIZE);
	for (int i = 0; i < PANSIZE; i++)
	{
		Dole NewDole;
		NewDole.x = i % PANLINE;
		NewDole.y = i / PANLINE;
		NewDole.color = VOIDDOLE;
		NewDole.set = SETOFF;
		VectorPan.push_back(NewDole);
	}


	eOState = OHMOKSTATE::BLACK;
}

void OhmokManager::update()
{
	update_dole();
	update_input();
}


void OhmokManager::update_dole()
{
	for (int i = 0; i < PANSIZE; i++)
	{
		if (VOIDDOLE == VectorPan[i].color)
		{
			continue;
		}
		else if (BLACKDOLE == VectorPan[i].color && SETOFF == VectorPan[i].set)
		{
			update_black(i % PANLINE, i / PANLINE);
			VectorPan[i].set = SETON;
		}
		else if (WHITEDOLE == VectorPan[i].color && SETOFF == VectorPan[i].set)
		{
			update_white(i % PANLINE, i / PANLINE);
			VectorPan[i].set = SETON;
		}
	}
}


void OhmokManager::update_input()
{
	if (true == KInputManager::instance()->is_down(VK_LBUTTON))
	{
		put_dole(KInputManager::instance()->pos_mouse());
		
		if (OHMOKSTATE::BLACK == eOState)
		{
			eOState = OHMOKSTATE::WHITE;
		}
		else if (OHMOKSTATE::WHITE == eOState)
		{
			eOState = OHMOKSTATE::BLACK;
		}
	}
}


void OhmokManager::update_black(const int& _X, const int& _Y)
{
	for (int i = 0; i < BLACKSIZE; i++)
	{
		if (false == VectorBlack[i]->active())
		{
			VectorBlack[i]->pos(pan_topos(_X, _Y));
			VectorBlack[i]->active(true);
			break;
		}
	}
}
void OhmokManager::update_white(const int& _X, const int& _Y)
{
	for (int i = 0; i < WHITESIZE; i++)
	{
		if (false == VectorWhite[i]->active())
		{
			VectorWhite[i]->pos(pan_topos(_X, _Y));
			VectorWhite[i]->active(true);
			break;
		}
	}
}


KPos2 OhmokManager::pan_topos(const int& _X, const int& _Y)
{
	KPos2 Tmp = { _X, _Y } ;
	Tmp *= LineSize;
	Tmp += LineSize * .5f;

	return Tmp;
}

void OhmokManager::put_dole(const KPos2& _Pos)
{
	int x = (int)((_Pos.x - LineSize.x * .5f) / (LineSize.x));
	int y = (int)((_Pos.y - LineSize.y * .5f) / (LineSize.y));

	for (int i = 0; i < PANSIZE; i++)
	{
		if (x == VectorPan[i].x && y == VectorPan[i].y)
		{
			switch (eOState)
			{
			case OhmokManager::BLACK:
				VectorPan[i].color = BLACKDOLE;
				break;
			case OhmokManager::WHITE:
				VectorPan[i].color = WHITEDOLE;
				break;
			case OhmokManager::DONE:
				break;
			default:
				break;
			}
			update_dole();
			return;
		}
	}
}