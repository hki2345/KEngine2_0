#pragma once

class KRenderManager
{
public:
	friend class KCore;

public:
	KRenderManager() {};
	KRenderManager(const KRenderManager& _Core) = delete;
	KRenderManager(const KRenderManager&& _Core) = delete;
	void operator=(const KRenderManager& _Core) = delete;
	~KRenderManager() = delete;


private:
	static void init();
	static void render();
	static void release();
};

