#include "ObstacleManager.h"
#include <KOne.h>
#include <KScene.h>
#include "Obstcle.h"


#include <KBitMap_Render.h>
#include <KBitMap_Animator.h>




ObstacleManager::ObstacleManager()
{
}


ObstacleManager::~ObstacleManager()
{
}


void ObstacleManager::create(KScene* _Scene, ComPlayer* _Player)
{
	for (size_t i = 0; i < 10; i++)
	{
		VecFire.push_back(create_fire(_Scene, _Player));
		VecPot.push_back(create_pot(_Scene, _Player));
	}

	for (size_t i = 0; i < 10; i++)
	{
		VecFire[i]->pos(KPos2(1000.0f, .0f));
		VecPot[i]->pos(KPos2(1000.0f, .0f));
		VecFire[i]->active(false);
		VecPot[i]->active(false);
	}

	create_winpan(_Scene, _Player);
}



void ObstacleManager::init_fire()
{
	for (size_t i = 0; i < VecFire.size(); i++)
	{
		if (false == VecFire[i]->active())
		{
			VecFire[i]->pos({ 800.0f + VecFire[i]->kscene()->SceneCamPos.x, 290.0f });
			VecFire[i]->active(true);
			return;
		}
	}

}

void ObstacleManager::init_pot()
{
	for (size_t i = 0; i < VecPot.size(); i++)
	{
		if (false == VecPot[i])
		{
			VecPot[i]->pos({ 800.0f + VecFire[i]->kscene()->SceneCamPos.x, 450.0f });
			VecFire[i]->active(true);
			return;
		}
	}
}

KOne* ObstacleManager::create_fire(KScene* _Scene, ComPlayer* _Player)
{
	KOne* TOne = _Scene->create_kone(L"Fire");
	TOne->size({ 30.0f, 150.0f });

	Obstcle* ComTmp = TOne->add_component<Obstcle>();
	ComTmp->set_player(_Player);
	ComTmp->set_prop(0, false);

	KBitMap_Animator* BRE = TOne->add_component<KBitMap_Animator>();
	std::vector<std::wstring> Tmp;
	Tmp.push_back(L"Circus\\enemy_1b.bmp");
	Tmp.push_back(L"Circus\\enemy_b.bmp");
	BRE->insert_animation(L"Idle", Tmp, 9);
	BRE->pivot(KPos2(-15.0f, 0.0f));

	BRE = TOne->add_component<KBitMap_Animator>();
	Tmp.clear();
	Tmp.push_back(L"Circus\\enemy_1f.bmp");
	Tmp.push_back(L"Circus\\enemy_f.bmp");
	BRE->insert_animation(L"Idle", Tmp, 11);
	BRE->pivot(KPos2(15.0f, 0.0f));

	return TOne;
}


KOne* ObstacleManager::create_pot(KScene* _Scene, ComPlayer* _Player)
{
	KOne* TOne = _Scene->create_kone(L"Pot");
	TOne->size({ 50.0f, 50.0f });

	Obstcle* ComTmp = TOne->add_component<Obstcle>();
	ComTmp->set_player(_Player);
	ComTmp->set_prop(1, false);

	KBitMap_Animator* BRE = TOne->add_component<KBitMap_Animator>();
	std::vector<std::wstring> Tmp;
	Tmp.push_back(L"Circus\\front.bmp");
	Tmp.push_back(L"Circus\\front2.bmp");
	BRE->insert_animation(L"Idle", Tmp, 9);

	return TOne;
}


void ObstacleManager::create_winpan(KScene* _Scene, ComPlayer* _Player)
{
	KOne* TOne = _Scene->create_kone(L"WinPan");
	TOne->size({ 120.0f, 70.0f });
	TOne->pos({ 1500.0f, 460.0f });

	Obstcle* ComTmp = TOne->add_component<Obstcle>();
	ComTmp->set_player(_Player);
	ComTmp->set_prop(2, false);

	KBitMap_Render* BRE = TOne->add_component<KBitMap_Render>();
	BRE->set_bit(L"Circus\\end.bmp", 9);
}