#pragma once
#include <KScene.h>
#include <vector>


class KOne;
class IntroScene : public KScene
{
public:
	IntroScene();
	~IntroScene();

private:
	enum INTRO_STATE
	{
		IS_WAIT,
		IS_PLAY,
	};

private:
	std::vector<KOne*> VectorUI;
	INTRO_STATE eIntroState;
	int UISize;
	float MaxYPos;

public:
	void create() override;
	bool init() override;
	void update() override;
};

