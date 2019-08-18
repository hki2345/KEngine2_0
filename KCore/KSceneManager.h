#pragma once
#include "KInitiator.h"
#include "KUpdater.h"


class KSceneManager
{
public:
	// ��ü������ �ؾ��ϴϱ�
	KSceneManager() {} /* = delete*/;
	KSceneManager(const KSceneManager& _Core) = delete;
	KSceneManager(const KSceneManager&& _Core) = delete;
	void operator=(const KSceneManager& _Core) = delete;
	~KSceneManager() = delete;


public:
	static void init() ;
	static void update() ;
};

