#include "KBitMap_Animator.h"
#include <KResourceManager.h>
#include "KTimeManager.h"
#include "KWindow.h"
#include "KTransform.h"

#include "KBitMap.h"
#include "KScene.h"



KBitMap_Animator::KBitMap_Animator()
{
}


KBitMap_Animator::~KBitMap_Animator()
{
}



void KBitMap_Animator::insert_animation(
	const wchar_t* _AniName,
	const std::vector<std::wstring>& _Source,
	const int& _Layer)
{
	fSpeed = 10.0f;
	iAniIdx = 0;

	std::vector<KBitMap*> TmpVec;


	for (size_t i = 0; i < _Source.size(); i++)
	{
		KBitMap* Tmp = KResourceManager<KBitMap>::instance()->find(_Source[i].c_str());

		assert(Tmp);
		TmpVec.push_back(Tmp);
	}

	MapVecBit.insert(std::make_pair(_AniName, TmpVec));
	CurAniIter = MapVecBit.begin();
	kscene()->insert_krender(this, _Layer);
}

void KBitMap_Animator::change_animation(const wchar_t* _AniName)
{
	CurAniIter = MapVecBit.find(_AniName);

	if (MapVecBit.end() == CurAniIter)
	{
		KASSERT;
	}

	iAniIdx = 0;
	fAniTime = .0f;
}



bool KBitMap_Animator::init()
{
	KRenderer::init();
	MapVecBit.clear();

	return true;
}


void KBitMap_Animator::update()
{
	fAniTime += KTimeManager::instance()->deltatime() * fSpeed;
	iAniIdx = (int)fAniTime;

	if (CurAniIter->second.size() <= iAniIdx)
	{
		iAniIdx = 0;
		fAniTime = .0f;
	}
}
void KBitMap_Animator::render()
{
	TransparentBlt(
		kwindow()->bhdc(),
		MyTrans->pos().x,
		MyTrans->pos().y,
		MyTrans->size().x,
		MyTrans->size().y,
		CurAniIter->second[iAniIdx]->MyDC,
		0,
		0,
		CurAniIter->second[iAniIdx]->size().x,
		CurAniIter->second[iAniIdx]->size().y,
		RGB(255, 0, 255));
	
}
void KBitMap_Animator::release()
{
	MapVecBit.clear();
}