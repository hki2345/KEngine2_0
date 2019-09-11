#include "KSprite_Animator.h"
#include "KSprite_Render.h"
#include "KTimeManager.h"
#include "KOne.h"

#include <KMacro.h>


KSprite_Animator::KSprite_Animator()
{
}


KSprite_Animator::~KSprite_Animator()
{
}


void KSprite_Animator::insert_animation(
	const wchar_t* _AniName,
	const int& _Start,
	const int& _End,
	const float& _Speed /*= 0.1f*/ // 초당 약 10장
)
{
	Clip NewClip;
	NewClip.fSpeed = _Speed;
	NewClip.Start = _Start;
	NewClip.End = _End;
	NewClip.fAniTime = .0f;

	MapClip.insert(std::make_pair(_AniName, NewClip));
}
void KSprite_Animator::change_animation(const wchar_t* _AniName)
{
	std::map<std::wstring, Clip>::iterator FIter = MapClip.find(_AniName);

	if (MapClip.end() != FIter)
	{
		CurClip = FIter;
	}
}

void KSprite_Animator::set_bit(const wchar_t* _Name /*= L"NONE"*/, const int& _Key /*= 0*/)
{
	pSprite->set_bit(_Name, _Key);
}
void KSprite_Animator::change_bit(const wchar_t* _Name /*= L"NONE"*/)
{
	pSprite->change_bit(_Name);
}
void KSprite_Animator::set_split(const int& _X, const int& _Y)
{
	pSprite->set_split(_X, _Y);
}

void KSprite_Animator::create()
{
	KComponent::create();

	pSprite = kone()->add_component<KSprite_Render>();
}
void KSprite_Animator::update()
{
	CurClip->second.fAniTime += KTimeManager::instance()->deltatime();

	if (CurClip->second.fAniTime > CurClip->second.fSpeed)
	{
		CurClip->second.iAniIdx += 1;
		CurClip->second.fAniTime = .0f;
	}

	if (CurClip->second.End <= CurClip->second.iAniIdx)
	{
		CurClip->second.iAniIdx = CurClip->second.Start;
	}

	pSprite->set_idx(CurClip->second.iAniIdx);
}
void KSprite_Animator::render()
{
	pSprite->render();
}

void KSprite_Animator::render(HDC _Hdc)
{
	pSprite->render(_Hdc);
}
void KSprite_Animator::release()
{
	RELEASE_PTR(pSprite);
}