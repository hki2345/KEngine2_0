#pragma once
#include "CircusObject.h"


class Obstcle : public CircusObject
{
public:
	Obstcle();
	~Obstcle();

private:
	enum OBSTACLE_TYPE
	{
		OT_FIRE = 0,
		OT_POT,
		OT_WINPAN,
	};


private:
	KPos2 MyOriginPos;
	OBSTACLE_TYPE eObType;
	bool bFast;

public:
	void set_prop(const int& _Type, const bool& _Fast);

	bool init() override;
	void update() override;

private:
	void update_fire();
	void update_pot();
	void update_winpan();

	void update_colide();
};

