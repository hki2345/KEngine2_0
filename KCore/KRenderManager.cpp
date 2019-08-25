#include "KRenderManager.h"
#include "KRenderer.h"
#include "KMacro.h"



void KRenderManager::init()
{
	SMapKRenderer = MapKRenderer.begin();
	EMapKRenderer = MapKRenderer.end();

	for (; SMapKRenderer != EMapKRenderer; ++SMapKRenderer)
	{
		SMapKRenderer->second->init();
	}
}

void KRenderManager::render()
{
	SMapKRenderer = MapKRenderer.begin();
	EMapKRenderer = MapKRenderer.end();

	for (; SMapKRenderer != EMapKRenderer; ++SMapKRenderer)
	{
		SMapKRenderer->second->render();
	}
}

void KRenderManager::release()
{
	MapKRenderer.clear();
}



bool KRenderManager::insert_krenderer( KRenderer* _Other, const int& _Key/* = 0*/)
{
	MapKRenderer.insert(std::make_pair(_Key, _Other));

	return true;
}