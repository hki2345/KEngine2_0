#pragma once
#include <KScene.h>
#include <vector>



class ObstacleManager;
class UIManager;
class ComPlayer;
class InGameScene : public KScene
{
public:
	InGameScene();
	~InGameScene();


private:
	ComPlayer* pPlayer;
	ObstacleManager* pObsManager;
	UIManager* pUIManager;

	float fFireTime;
	float fFireSpwanTime;

public:
	void create() override;
	bool init() override;
	void update() override;
	void release() override;

private:
	void spwan_fire();
	void update_game();
};

