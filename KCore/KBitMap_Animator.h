#pragma once
#include <map>
#include <vector>
#include <string>
#include "KRenderer.h"


class KBitMap;
class KBitMap_Animator : public KRenderer
{
public:
	KBitMap_Animator();
	~KBitMap_Animator();

private:
	float fSpeed;
	float fAniTime;
	bool bBitRender;
	int iAniIdx;

	std::map<std::wstring, std::vector< KBitMap*>>::iterator CurAniIter;
	std::map<std::wstring, std::vector< KBitMap*>> MapVecBit;

public:
	void insert_animation(
		const wchar_t* _AniName, 
		const std::vector<std::wstring>& _Source,
		const int& _Layer = 0,
		const float& _Speed = 0.1f, // 초당 약 10장
		const int& _Start = 0,
		const bool& _BitRender = false);
	void change_animation(const wchar_t* _AniName);

	bool init() override;
	void update() override;
	void render() override;
	void release() override;
};

