#pragma once
#include <KScene.h>


class InGameScene : public KScene
{
public:
	InGameScene();
	~InGameScene();

private:
	enum GAMESCENE_STATE
	{
		GSS_WAIT,
		GSS_PLAY,
		GSS_OVER,
	};

private:
	GAMESCENE_STATE eGSState;

public:
	void create() override;
	bool init() override;
	void render() override;
	void update() override;
	void release() override;

private:
	void update_wait();
	void update_play();
	void update_over();
};

