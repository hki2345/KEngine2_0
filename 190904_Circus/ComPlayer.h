#pragma once
#include <KComponent.h>


class KBitMap_Animator;
class ComPlayer : public KComponent
{
public:
	ComPlayer();
	~ComPlayer();

private:
	enum ACT_STATE
	{
		IDLE = 0,
		RUN,
		JUMP,
		WIN,
		DIE,
	};

private:
	KBitMap_Animator* pAnimator;
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
	void create() override;
	bool init() override;
	void update() override;

	// -1 왼쪽 0 정지 1 오른쪽
	int scroll_dir();
	void set_win();
	void set_failed();
	bool check_win();

private:
	void update_input();
	void update_idle();
	void update_run();
	void update_jump();
	void update_win();
	void update_die();

	void update_move();
};

