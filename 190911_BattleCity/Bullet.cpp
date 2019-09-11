#include "Bullet.h"
#include <KSprite_Render.h>
#include <KOne.h>


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}


void Bullet::create()
{
	KComponent::create();


	MySprite = kone()->add_component<KSprite_Render>();
	MySprite->set_bit(L"res\\Bullet.bmp", 5);
	MySprite->set_split(4, 1);
	fSpeed = 300.0f;
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
}

void Bullet::update()
{
	KComponent::update();

	kone()->moving_delta(vDir * fSpeed);
}