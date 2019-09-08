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
	const int& _Layer /*= 0*/,
	const float& _Speed /*= 0.02f*/,
	const int& _Start /*= 0*/
	)
{
	fSpeed = _Speed;
	iAniIdx = _Start;

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
	std::map<std::wstring, std::vector< KBitMap*>>::iterator FIter = MapVecBit.find(_AniName);

	if (MapVecBit.end() == FIter)
	{
		KASSERT;
	}

	if (CurAniIter != FIter)
	{
		iAniIdx = 0;
		CurAniIter = MapVecBit.find(_AniName);
	}
}



bool KBitMap_Animator::init()
{
	KRenderer::init();
	
	if (iAniIdx >= CurAniIter->second.size())
	{
		iAniIdx = 0;
		fAniTime = .0f;
	}

	return true;
}

void KBitMap_Animator::update()
{
	fAniTime += KTimeManager::instance()->deltatime();

	if (fAniTime > fSpeed)
	{
		iAniIdx += 1;
		fAniTime = .0f;
	}

	if (CurAniIter->second.size() <= iAniIdx)
	{
		iAniIdx = 0;
	}
}
void KBitMap_Animator::render()
{
	if (false == bRender)
	{
		return;
	}

	if (CurAniIter->second.size() <= iAniIdx)
	{
		iAniIdx = 0;
	}

	TransparentBlt(
		kwindow()->bhdc(),
		RenderPos.x,
		RenderPos.y,
		MyTrans->Size.x ,
		MyTrans->Size.y ,
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