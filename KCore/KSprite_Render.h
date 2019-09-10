#pragma once
#include "KRenderer.h"
#include <Windows.h>
#include <vector>

class KBitMap;
class KTransform;
class KSprite_Render : public KRenderer
{
public:
	KSprite_Render();
	~KSprite_Render();

private:
	struct KSplit
	{
		KPos2 Start;
		KPos2 End;
	};

private:
	KBitMap* MyBitMap;
	std::vector<KSplit> VectorMySplit;
	int SplitX;
	int SplitY;
	int idx;

public:
	void set_bit(const wchar_t* _Name = L"NONE", const int& _Key = 0);
	void change_bit(const wchar_t* _Name = L"NONE");
	void set_split(const int& _X, const int& _Y);
	void set_idx(const int& _X, const int& _Y);

	bool init() override;
	void render() override;
	void render(HDC _Hdc);
};

