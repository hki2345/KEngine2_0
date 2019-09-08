#include "KDebugManager.h"
#include "KWindowManager.h"

#include <Windows.h>
#include <KMacro.h>


void KDebugManager::init()
{
	VectorLog.clear();
}

void KDebugManager::render()
{
	SetTextAlign(KWindowManager::instance()->back_hdc(), TA_LEFT);

	for (size_t i = 0; i < VectorLog.size(); i++)
	{
		TextOutW(KWindowManager::instance()->back_hdc(), 20, 20 + (20 * i), VectorLog[i].c_str(), VectorLog[i].size());
	}

	VectorLog.clear();
}

void KDebugManager::release()
{
	VectorLog.clear();
}