#pragma once
#include "KRenderer.h"


class KBitMap;
class KTransform;
class KSprite_Render : public KRenderer
{
public:
	KSprite_Render();
	~KSprite_Render();

private:
	KBitMap* MyBitMap;


public:
	void set_bit(const wchar_t* _Name = L"NONE");

	bool init() override;
	void update() override;
	void release() override {};
	void render() override;
};

