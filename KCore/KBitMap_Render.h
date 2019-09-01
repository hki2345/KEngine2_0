#pragma once
#include "KRenderer.h"


class KBitMap;
class KBitMap_Render : public KRenderer
{
public:
	KBitMap_Render();
	~KBitMap_Render();

private:
	KBitMap* MyBitMap;


public:
	virtual bool init() override;
	virtual void render() override;
};

