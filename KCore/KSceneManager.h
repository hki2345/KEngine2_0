#pragma once
#include "KInitiator.h"
#include "KUpdater.h"


class KSceneManager
{
public:
	// 본체에서는 해야하니까
	KSceneManager() {} /* = delete*/;
	KSceneManager(const KSceneManager& _Core) = delete;
	KSceneManager(const KSceneManager&& _Core) = delete;
	void operator=(const KSceneManager& _Core) = delete;
	~KSceneManager() = delete;


public:
	static void init() ;
	static void update() ;
};

