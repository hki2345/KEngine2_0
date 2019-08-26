#pragma once
#include <map>




class KRenderer;
class KRenderManager
{
public:
	friend class KScene;

private:
	KRenderManager() {};
	KRenderManager(const KRenderManager& _Core) = delete;
	KRenderManager(const KRenderManager&& _Core) = delete;
	void operator=(const KRenderManager& _Core) = delete;
	~KRenderManager() {};

private:
	void init();
	void render();
	void release();


private:
	std::multimap<int, KRenderer*> MapKRenderer;

private:
	bool insert_krenderer(KRenderer* _Other, const int& _Key = 0);
};

