#pragma once
#include "KComponent.h"


class ComTest : public KComponent
{
public:
	ComTest();
	~ComTest();


private:
	int Cnt;

public:
	virtual bool init();
	virtual void update();
	virtual void release();
};

