#include "EnemyManager.h"

#include <KTimeManager.h>
#include <KScene.h>
#include <KOne.h>

#include "TileManager.h"
#include "EnemyTank.h"

EnemyManager* EnemyManager::pKEnemyManager = nullptr;

void EnemyManager::create(KScene* _Scene)
{
	MomScene = _Scene;

	VectorEnemy.reserve(50);

	for (int i = 0; i < 50; i++)
	{
		KOne* CurSorEnemy = MomScene->create_kone(L"EnemyTank");
		EnemyTank* Enemy = CurSorEnemy->add_component<EnemyTank>();

		VectorEnemy.push_back(Enemy);
		Enemy->kone()->active(false);
	}
}


bool EnemyManager::init(const int& _EnemyNum)
{
	fRespawnCurTime = .0f;
	fRespawnTime = 5.0f;
	EnemyRespawnCnt = _EnemyNum;

	VectorRespawnPos = *TileManager::instance()->vector_respawnpos();
	set_enemy();

	return true;
}

void EnemyManager::update()
{
	update_respawn();
	update_resetpos();
}


void EnemyManager::update_respawn()
{
	if (EnemyRespawnCnt == VectorEnemy.size())
	{
		return;
	}

	fRespawnCurTime += KTimeManager::instance()->deltatime();
	if (fRespawnCurTime >= fRespawnTime)
	{
		fRespawnCurTime = .0f;
		set_enemy();
	}
}

void EnemyManager::update_resetpos()
{
	for (int i = 0; i < EnemyRespawnCnt; i++)
	{
		if (10.0f >= VectorEnemy[i]->kone()->pos().x)
		{
			int XXX = 0;

			XXX = rand() % VectorRespawnPos.size();
			VectorEnemy[i]->kone()->pos(VectorRespawnPos[XXX]);
		}
	}
}

void EnemyManager::set_enemy()
{
	int XXX = 0;

	XXX = rand() % VectorRespawnPos.size();

	VectorEnemy[EnemyRespawnCnt]->set_tank(VectorRespawnPos[XXX]);
	EnemyRespawnCnt += 1;
}