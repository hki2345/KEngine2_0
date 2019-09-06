#pragma once
#include <vector>


class KScene;
class ComPlayer;
class KOne;
class ObstacleManager
{
public:
	ObstacleManager();
	~ObstacleManager();


private:
	std::vector<KOne*> VecFire;
	std::vector<KOne*> VecPot;


public:
	void create(KScene* _Scene, ComPlayer* _Player);
	void init_fire();
	void init_pot();

private:
	KOne* create_fire(KScene* _Scene, ComPlayer* _Player);
	KOne* create_pot(KScene* _Scene, ComPlayer* _Player);
	void create_winpan(KScene* _Scene, ComPlayer* _Player);
};

