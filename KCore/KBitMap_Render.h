#pragma once
#include "KRenderer.h"
#include <Windows.h>

class KBitMap;
class KTransform;
class KBitMap_Render : public KRenderer
{
public:
	KBitMap_Render();
	~KBitMap_Render();

private:
	bool bBitRender;

	KBitMap* MyBitMap;

public:
	void set_bit(const wchar_t* _Name = L"NONE", const int& _Key = 0, const bool& _bBitRender = false);
	void change_bit(const wchar_t* _Name = L"NONE", const bool& _bBitRender = false);

	bool init() override;
	void render() override;
	void render(HDC _Hdc);
};

