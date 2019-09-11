#include "KRect_Collision.h"
#include "KScene.h"



KRect_Collision::KRect_Collision()
{
}


KRect_Collision::~KRect_Collision()
{
}


void KRect_Collision::set_rect(const int& _Key)
{
	kscene()->insert_k2dCollider(this, _Key);
}
