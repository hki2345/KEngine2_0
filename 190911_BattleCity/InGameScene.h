#pragma once
#include <KScene.h>


class TileManager;
class PlayerTank;
class InGameScene : public KScene
{
public:
	InGameScene();
	~InGameScene();


private:
	PlayerTank* MyPlayer;

public:
	void create() override;
	bool init() override;
	void render() override;
	void update() override;
	void release() override;
};

