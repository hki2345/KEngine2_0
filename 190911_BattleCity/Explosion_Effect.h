#pragma once
#include <KComponent.h>
#include <KVector.h>



class KSprite_Animator;
class Explosion_Effect : public KComponent
{
public:
	Explosion_Effect();
	~Explosion_Effect();

private:
	KSprite_Animator* MyAnimator;

public:
	void create() override;
	void set_bulletexplosion(const KPos2& _Pos);
	void set_tankexplosion(const KPos2& _Pos);

	void update() override;
};

