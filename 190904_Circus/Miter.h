#pragma once
#include "CircusObject.h"

class KBitMap_Render;
class Miter : public CircusObject
{
public:
	Miter();
	~Miter();

private:
	KBitMap_Render* pBitRender;

public:
	bool init() override;
	void update() override;
};

