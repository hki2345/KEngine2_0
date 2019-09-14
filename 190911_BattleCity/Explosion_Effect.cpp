#include "Explosion_Effect.h"

#include <BattleTile.h>
#include <KScene.h>
#include <KOne.h>
#include <KSprite_Animator.h>


Explosion_Effect::Explosion_Effect()
{
}


Explosion_Effect::~Explosion_Effect()
{
}


void Explosion_Effect::create()
{
	kone()->size({ 80.0f, 80.0f });
	kone()->active(false);
	MyAnimator = kone()->add_component<KSprite_Animator>();
	MyAnimator->set_bit(L"res\\BombEffect.bmp", 13);
	MyAnimator->set_split(5, 1);
	MyAnimator->insert_animation(L"Bullet", 0,  2, .05f);
	MyAnimator->insert_animation(L"Bomb", 0,  4, .05f);
}

void Explosion_Effect::set_bulletexplosion(const KPos2& _Pos)
{
	kone()->active(true);
	kone()->pos(_Pos + KPos2( TILEXSIZE * 1.5f, TILEYSIZE) * -1.0f);
	MyAnimator->change_animation(L"Bullet");
	MyAnimator->update_trans(kscene()->SceneCamPos);
}

void Explosion_Effect::set_tankexplosion(const KPos2& _Pos)
{
	kone()->active(true);
	kone()->pos(_Pos + KPos2(TILEXSIZE , TILEYSIZE) * -1.5f);
	MyAnimator->change_animation(L"Bomb"); 
	MyAnimator->update_trans(kscene()->SceneCamPos);
}

void Explosion_Effect::update()
{
	if (true == MyAnimator->isover_animate())
	{
		MyAnimator->reset_animate();
		kone()->active(false);
	}
}