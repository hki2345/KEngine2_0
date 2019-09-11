#pragma once
#include <KComponent.h>
#include <KVector.h>
#include <vector>


class KSprite_Animator;
class KRect_Collision;
class Bullet;
class Tank : public KComponent
{
public:
	Tank();
	~Tank();

protected:
	std::vector<Bullet*> VectorMyBullet;
	KSprite_Animator* MyAnimator;
	KRect_Collision* MyCollider;

	KPos2 vPrevDir;
	KPos2 vDir;
	float fSpeed;


public:
	virtual bool init() override;
	virtual void create() override;
	virtual void update() override;

protected:
	void update_checkingpos();
	virtual void update_move();
};

