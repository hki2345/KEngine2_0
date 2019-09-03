#pragma once
#include "KScene.h"



class SceneTest : public KScene
{
public:
	SceneTest();
	~SceneTest();

public:
	struct TEST
	{
		float x;
		float y;
		wchar_t Name[24];
		int z;
		int c;

		double o;
	};

private:
	TEST cc;


public:
	bool init() override;
	void update() override;
};

