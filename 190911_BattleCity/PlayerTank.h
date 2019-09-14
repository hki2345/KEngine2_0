#pragma once
#include "Tank.h"


class PlayerTank : public Tank
{
public:
	PlayerTank();
	~PlayerTank();

public:
	void create() override;
	bool init() override;
	void update() override;

private:
	void update_input();
	void update_move();
	void update_collisiontile();


	void stay_tile(KOne* _Tile) override;
	void exit_tile(KOne* _Tile) override;
};

