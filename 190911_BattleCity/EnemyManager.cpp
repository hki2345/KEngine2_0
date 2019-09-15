#include "EnemyManager.h"
#include "PlayerManager.h"

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
	EnemyMaxCnt = _EnemyNum;

	VectorRespawnPos = *TileManager::instance()->vector_respawnpos();
	for (int i = 0; i < 50; i++)
	{
		VectorEnemy[i]->kone()->active(false);
	}
	
	set_enemy();

	return true;
}

void EnemyManager::update()
{
	update_respawn();
	update_resetpos();
	update_playerwin();
}


void EnemyManager::update_respawn()
{
	if (EnemyRespawnCnt == EnemyMaxCnt)
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
	for (int i = 0; i < EnemyMaxCnt; i++)
	{
		if (10.0f >= VectorEnemy[i]->kone()->pos().x)
		{
			int XXX = 0;

			XXX = rand() % VectorRespawnPos.size();
			VectorEnemy[i]->kone()->pos(VectorRespawnPos[XXX]);
		}
	}
}

void EnemyManager::update_playerwin()
{
	if (PlayerManager::instance()->iKill == EnemyMaxCnt)
	{
		PlayerManager::instance()->iWin = 1;
	}
}

int EnemyManager::calculate_remain()
{
	return EnemyMaxCnt - EnemyRespawnCnt;
}

void EnemyManager::set_enemy()
{
	int XXX = 0;

	XXX = rand() % VectorRespawnPos.size();

	VectorEnemy[EnemyRespawnCnt]->set_tank(VectorRespawnPos[XXX]);
	EnemyRespawnCnt += 1;
}