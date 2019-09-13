#pragma once
#include <KComponent.h>
#include "Tank.h"


class KOne;
class PlayerTank : public Tank
{
public:
	PlayerTank();
	~PlayerTank();

private:

public:
	void create() override;
	bool init() override;
	void update() override;

private:
	void update_input();
	void update_move();
	void update_collisiontile();
};

