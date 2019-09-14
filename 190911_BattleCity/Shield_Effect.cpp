#include "Shield_Effect.h"


#include <BattleTile.h>
#include <KScene.h>
#include <KOne.h>
#include <KSprite_Animator.h>


Shield_Effect::Shield_Effect()
{
}


Shield_Effect::~Shield_Effect()
{
}

void Shield_Effect::create()
{
	kone()->size({40.0f, 40.0f });
	kone()->active(false);
	MyAnimator = kone()->add_component<KSprite_Animator>();
	MyAnimator->set_bit(L"res\\Shield.bmp", 13);
	MyAnimator->set_split(2, 1);
	MyAnimator->insert_animation(L"Shield", 0, 1, .05f);
	MyAnimator->change_animation(L"Shield");
}

void Shield_Effect::set_shield(KOne* _Target)
{
	MyTarget = _Target;
}

void Shield_Effect::update()
{
	kone()->pos(MyTarget->pos());
	MyAnimator->update_trans(kscene()->SceneCamPos);
}