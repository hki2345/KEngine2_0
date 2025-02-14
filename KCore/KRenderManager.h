#pragma once
#include <map>
#include "KVector.h"



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
	void update_trans(const KPos2& _CameraPos);
	void render();
	void release();

	void delete_renderer(KRenderer* _Renderer);


private:
	std::multimap<int, KRenderer*> MapKRenderer;

private:
	bool insert_krenderer(KRenderer* _Other, const int& _Key = 0);
};

