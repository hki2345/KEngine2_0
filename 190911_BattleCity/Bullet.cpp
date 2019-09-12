#include "Bullet.h"
#include <BattleTile.h>

#include <KSprite_Render.h>
#include <KRect_Collision.h>
#include <K2DCollider.h>
#include <KOne.h>

#include "Tile.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}


void Bullet::create()
{
	KComponent::create();

	sName = L"Bullet";

	MySprite = kone()->add_component<KSprite_Render>();
	MySprite->set_bit(L"res\\Bullet.bmp", 5);
	MySprite->set_split(4, 1);
	fSpeed = 300.0f;

	MyCollider = kone()->add_component<KRect_Collision>();
	MyCollider->set_rect(0);
	MyCollider->pivot(KPos2(STARTXPOS * -1.0f, STARTYPOS * -1.0f));

	MyCollider->insert_enterfunc<Bullet>(L"Bullet Enter", this, &Bullet::Enter);
	MyCollider->insert_stayfunc<Bullet>(L"Bullet Stay", this, &Bullet::Stay);
	MyCollider->insert_exitfunc<Bullet>(L"Bullet Exit", this, &Bullet::Exit);
}



void Bullet::set_bullet(const KPos2& _Pos, const KPos2& _Dir)
{
	kone()->active(true);
	kone()->size({ 20.0f, 40.0f });
	kone()->pos(_Pos);
	vDir = _Dir;

	if (vDir == KPos2::Left)
	{
		MySprite->set_idx(1);
	}
	else if (vDir == KPos2::Right)
	{
		MySprite->set_idx(3);
	}
	else if (vDir == KPos2::Up)
	{
		MySprite->set_idx(2);
	}
	else if (vDir == KPos2::Down)
	{
		MySprite->set_idx(0);
	}

	Explosion = false;
}

void Bullet::update()
{
	KComponent::update();

	kone()->moving_delta(vDir * fSpeed);

	if (true == Explosion)
	{
		kone()->active(false);
	}
}


void Bullet::Enter(KOne* _Collider)
{
	if (true == _Collider->get_component<Tile>()->collision_bullet(vDir))
	{
		Explosion = true;
	}
}
void Bullet::Stay(KOne* _Collider)
{
	this;
	int a = 0;
}
void Bullet::Exit(KOne* _Collider)
{
	this;
	int a = 0;
}