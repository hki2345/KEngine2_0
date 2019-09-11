#pragma once
#include <KComponent.h>
#include <KVector.h>

class KSprite_Animator;
class Tank : public KComponent
{
public:
	Tank();
	~Tank();

protected:
	KSprite_Animator* MyAnimator;

	KPos2 vPrevDir;
	KPos2 vDir;
	float fSpeed;


public:
	virtual void create() override;
	virtual void update() override;

protected:
	virtual void update_move();
};

