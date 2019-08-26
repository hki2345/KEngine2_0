#pragma once
#include "KComponent.h"


class ComTest : public KComponent
{
public:
	ComTest();
	~ComTest();


public:
	virtual bool init();
	virtual void update();
	virtual void release();
};

