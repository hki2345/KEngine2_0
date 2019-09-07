#pragma once
#include <KComponent.h>

struct SCORE_INFO
{
	int Life;
	int Score;
};

class KBitMap_Animator;
class ComPlayer : public KComponent
{
public:
	ComPlayer();
	~ComPlayer();

private:
	enum ACT_STATE
	{
		WAIT = 0,
		IDLE,
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

	SCORE_INFO sScoreInfo;

public:
	void create() override;
	bool init() override;
	void update() override;

	// -1 왼쪽 0 정지 1 오른쪽
	int scroll_dir();
	void set_play();
	void set_win();
	void set_failed();
	void set_item();
	void set_score();
	bool check_win();
	bool check_acting();

	inline SCORE_INFO& score_info()
	{
		return sScoreInfo;
	}

private:
	void update_input();

	void update_wait();
	void update_idle();
	void update_run();
	void update_jump();
	void update_win();
	void update_die();

	void update_move();
};

