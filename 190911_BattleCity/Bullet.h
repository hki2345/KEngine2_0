#pragma once
#include <KComponent.h>
#include <KVector.h>



class KSprite_Render;
class KRect_Collision;
class K2DCollider;
class Bullet : public KComponent
{
public:
	Bullet();
	~Bullet();

private:
	KSprite_Render* MySprite;
	KRect_Collision* MyCollider;
	KPos2 vDir;
	float fSpeed;

	bool Explosion;

public:
	void create() override;
	void set_bullet(const KPos2& _Pos, const KPos2& _Dir);
	void update() override;

private:
	void update_outofgame();

	void Enter(KOne* _Collider);
	void Stay(KOne* _Collider);
	void Exit(KOne* _Collider);
};

