#include "Bullet.h"
#include <BattleTile.h>

#include <KSprite_Render.h>
#include <KRect_Collision.h>
#include <K2DCollider.h>
#include <KScene.h>
#include <KOne.h>

#include "Explosion_Effect.h"

#include "TileManager.h"
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
	MyCollider->pivot(KPos2(STARTXPOS * -1.0f, STARTYPOS * -1.0f));

	MyCollider->insert_stayfunc<Bullet>(this, &Bullet::Stay);

	MyEffect = kscene()->create_kone(L"Expolsion")->add_component<Explosion_Effect>();

	kone()->active(false);
}

void Bullet::set_tank(const int& _Layer)
{
	MyCollider->set_rect(_Layer);
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

	bExplosion = false;
}


void Bullet::set_bomb()
{
	kone()->active(false);
}

void Bullet::update()
{
	KComponent::update();

	kone()->moving_delta(vDir * fSpeed);
	update_outofgame();
}



void Bullet::update_outofgame()
{
	if (true == bExplosion)
	{
		set_bomb();
		MyEffect->set_bulletexplosion(kone()->pos());

		return;
	}

	KPos2 Tmp = kone()->pos();
	if (Tmp.x <= TileManager::instance()->tilemap_size().Start.x - kone()->size().x ||
		Tmp.x >= TileManager::instance()->tilemap_size().End.x + kone()->size().x ||
		Tmp.y <= TileManager::instance()->tilemap_size().Start.y - kone()->size().x ||
		Tmp.y >= TileManager::instance()->tilemap_size().End.y + kone()->size().x)
	{
		set_bomb();
		MyEffect->set_bulletexplosion(kone()->pos());
	}
}

void Bullet::Stay(KOne* _Collider)
{
	Tile* CurTile = _Collider->get_component<Tile>();
	if (nullptr != CurTile && true == CurTile->collision_bullet(vDir))
	{
		bExplosion = true;
	}
}