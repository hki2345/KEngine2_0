#include "PlayerManager.h"

#include <KFileStream.h>
#include <KOne.h>
#include <KScene.h>
#include "PlayerTank.h"


PlayerManager* PlayerManager::pPlayerManager = nullptr;

void PlayerManager::create(KScene* _GameScene)
{
	KOne* CurSorOne = _GameScene->create_kone(L"PlayerTank");
	pUserTank = CurSorOne->add_component<PlayerTank>();

	iLife = 3;
	iScore = 0;
	load_highscore();
}

void PlayerManager::init()
{
	pUserTank->set_tank({ 220.0f, 500.0f });
}

void PlayerManager::update()
{

}





void PlayerManager::load_highscore()
{
	KFileStream::instance()->read_file(L"res\\highscore.btscore", iHighScore);
}

void PlayerManager::save_highscore()
{
	KFileStream::instance()->write_file(L"res\\highscore.btscore", iHighScore);
}