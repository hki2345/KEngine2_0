#pragma once
#include "KUpdater.h"
class KEngineUpdater :public KUpdater
{
public:
	KEngineUpdater();
	~KEngineUpdater();

public:
	void update() override;
};

 