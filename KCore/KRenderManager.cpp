#include "KRenderManager.h"
#include "KMacro.h"



KRenderManager* KRenderManager::pKRenderManager = nullptr;

void KRenderManager::init()
{
}

void KRenderManager::render()
{
}

void KRenderManager::release()
{
	RELEASE_PTR(pKRenderManager);
}