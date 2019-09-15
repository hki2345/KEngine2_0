#pragma once
#include <KScene.h>
#include <KVector.h>
#include <vector>


class KOne;
class OutroScene : public KScene
{
public:
	OutroScene();
	~OutroScene();


private:
	std::vector<KOne*> VectorUI;

	float fOutCurTime;
	float fOutTime;

public:
	void create() override;
	bool init() override;
	void update() override;
};

