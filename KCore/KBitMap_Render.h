#pragma once
#include "KRenderer.h"


class KBitMap;
class KTransform;
class KBitMap_Render : public KRenderer
{
public:
	KBitMap_Render();
	~KBitMap_Render();

private:
	KBitMap* MyBitMap;

public:
	void set_bit(const wchar_t* _Name = L"NONE", const int& _Key = 0);

	bool init() override;
	void render() override;
};

