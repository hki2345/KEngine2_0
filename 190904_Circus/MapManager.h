#pragma once
#include <vector>


class KScene;
class ComPlayer;
class MapManager
{
public:
	MapManager();
	~MapManager();
	
public:
	void create(KScene* _Scene, ComPlayer* _Player);
};

