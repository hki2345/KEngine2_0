#pragma once
#include <KComponent.h>


class ComPlayer : public KComponent
{
public:
	ComPlayer();
	~ComPlayer();

private:
	enum ACT_STATE
	{
		IDLE = 0,
		JUMP,
		WIN,
		DIE,
	};

private:
	float ePlayerDir;
	ACT_STATE ePlayerAct;

	float fDirWalk[3];
	float fWalkSpeed;
	float fwalk_distance;
	float fmax_distance;

	float fJumpTime;
	float fJumpPower;
	float fbottom;

public:
	bool init() override;
	void update() override;

	bool almost_win();

private:
	void update_input();
	void update_idle();
	void update_jump();
	void update_win();
	void update_die();
};

