#include "KEngineinitiator.h"
#include "KSceneManager.h"
#include "GameManager.h"



#include <KResourceManager.h>
#include "KBitMap.h"


KEngineinitiator::KEngineinitiator()
{
}


KEngineinitiator::~KEngineinitiator()
{
	int a = 0;
}


bool KEngineinitiator::init()
{
	KResourceManager<KBitMap>::instance()->init();
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\BackBoard.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\player0.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\player1.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\player2.bmp");

	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\win.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\win2.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\die.bmp");



	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\back.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\back_normal.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\back_normal2.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\back_deco.bmp");
	

	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\enemy_1b.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\enemy_1f.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\enemy_b.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\enemy_f.bmp");

	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\enemy_l_b.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\enemy_l_f.bmp");

	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\front.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\front2.bmp");

	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\end.bmp");

	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\miter.bmp");


	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\star.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\star1.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\star2.bmp");

	GameManager::instance()->init();

	AddFontResourceA("Circus\\DungGeunMo.ttf");
	return true;
}

