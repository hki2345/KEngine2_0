#pragma once
#include "KVector.h"
#include <map>
#include <list>



class K2DCollider;
class K2DColliderManager
{
public:
	friend class KScene;

private:
	K2DColliderManager() {};
	K2DColliderManager(const K2DColliderManager& _Other) = delete;
	K2DColliderManager(const K2DColliderManager&& _Other) = delete;
	void operator=(const K2DColliderManager& _Other) = delete;
	~K2DColliderManager() {};

private:
	struct Link
	{
		int Key1;
		int Key2;
	};

private:
	void init();
	void update();
	void release();


private:
	void update_link(const int& _Key1, const int& _Key2);

private:
	std::multimap<int, K2DCollider*> MapK2DCollider;
	std::list <Link> ListLink;

private:
	void link(const int& _Key1, const int& _Key2);
	bool insert_kcollider(K2DCollider* _Other, const int& _Key = 0);
};

