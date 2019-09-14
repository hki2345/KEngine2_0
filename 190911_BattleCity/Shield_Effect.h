#pragma once
#include <KComponent.h>
#include <KVector.h>


class KOne;
class KSprite_Animator;
class Shield_Effect : public KComponent
{
public:
	Shield_Effect();
	~Shield_Effect();


private:
	KOne* MyTarget;
	KSprite_Animator* MyAnimator;

public:
	void create() override;
	void set_shield(KOne* _Target);

	void update() override;
};

