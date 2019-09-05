#pragma once
#include <KScene.h>
#include <vector>



class KOne;
class ComPlayer;
class KBitMap_Animator;
class InGameScene : public KScene
{
public:
	InGameScene();
	~InGameScene();


private:
	KOne* OnePlayer;
	std::vector<KOne*> VecBackGround;
	std::vector<KOne*> VecDeco;

public:
	void create() override;


private:
	void create_backboard();
	void create_player();
	void create_wall(ComPlayer* _Player);
	void create_obstacle(ComPlayer* _Player);
	void create_miter(ComPlayer* _Player);

	void create_fire(KOne* _KOne);
	void create_pot(KOne* _KOne);
	void create_winpan(KOne* _KOne);
};

