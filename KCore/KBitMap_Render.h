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
	void set_bit(const wchar_t* _Name = L"NONE");

	bool init() override;
	void update() override;
	void release() override {};
	void render() override;
};

