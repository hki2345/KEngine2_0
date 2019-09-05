#include "KRenderManager.h"
#include "KRenderer.h"
#include "KMacro.h"



void KRenderManager::init()
{
	std::multimap<int, KRenderer*>::iterator SIter = MapKRenderer.begin();
	std::multimap<int, KRenderer*>::iterator EIter = MapKRenderer.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->init();
	}
}

void KRenderManager::render()
{
	std::multimap<int, KRenderer*>::iterator SIter = MapKRenderer.begin();
	std::multimap<int, KRenderer*>::iterator EIter = MapKRenderer.end();

	for (; SIter != EIter; ++SIter)
	{
		if (true == SIter->second->active())
		{
			SIter->second->render();
		}
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