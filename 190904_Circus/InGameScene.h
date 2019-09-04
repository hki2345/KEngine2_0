#pragma once
#include <KScene.h>
#include <vector>



class KOne;
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
	bool init() override;
	void update() override;
};

