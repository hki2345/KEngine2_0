#pragma once
#include <KScene.h>
#include <KVector.h>
#include <vector>


class KOne;
class KText_Render;
class OutroScene : public KScene
{
public:
	OutroScene();
	~OutroScene();


private:
	std::vector<KOne*> VectorUI;
	std::vector< KText_Render*> ActionText;

	float fOutCurTime;
	float fOutTime;

public:
	void create() override;
	bool init() override;
	void update() override;
};

