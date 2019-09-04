#pragma once
#include <KComponent.h>

class Obstcle : public KComponent
{
public:
	Obstcle();
	~Obstcle();

private:
	float fwalk_distance;
	float fmax_distance;

	float fSpeed;

public:
	bool init() override;
	void update() override;
};

