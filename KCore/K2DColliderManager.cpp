#include "K2DColliderManager.h"
#include "K2DCollider.h"



void K2DColliderManager::init()
{
	std::multimap<int, K2DCollider*>::iterator SIter = MapK2DCollider.begin();
	std::multimap<int, K2DCollider*>::iterator EIter = MapK2DCollider.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->init();
	}
}


void K2DColliderManager::update()
{
	std::list <Link>::iterator SLI = ListLink.begin();
	std::list <Link>::iterator ELI = ListLink.end();

	for (; SLI != ELI; ++SLI)
	{
		update_link((*SLI).Key1, (*SLI).Key2);
	}
}


void K2DColliderManager::update_link(const int& _Key1, const int& _Key2)
{
	std::multimap<int, K2DCollider*>::iterator SCI1 = MapK2DCollider.find(_Key1);
	std::multimap<int, K2DCollider*>::iterator SCI2 = MapK2DCollider.find(_Key2);

	for (; SCI1 != MapK2DCollider.end(); ++SCI1)
	{
		if (_Key1 != SCI1->first)
		{
			break;
		}
		for (; SCI2 != MapK2DCollider.end(); ++SCI2)
		{
			if (_Key2 != SCI2->first)
			{
				break;
			}

			if (SCI1->second == SCI2->second)
			{
				continue;
			}

			SCI1->second->update_collision(SCI2->second);
		}
	}
}


void K2DColliderManager::release()
{
	MapK2DCollider.clear();
	ListLink.clear();
}


void K2DColliderManager::link(const int& _Key1, const int& _Key2)
{
	ListLink.push_back({ _Key1, _Key2 });
}

bool K2DColliderManager::insert_kcollider(K2DCollider* _Other, const int& _Key/* = 0*/)
{
	MapK2DCollider.insert(std::make_pair(_Key, _Other));
	return true;
}