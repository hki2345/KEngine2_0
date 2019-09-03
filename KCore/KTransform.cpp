#include "KTransform.h"
#include "KTimeManager.h"




KTransform::KTransform()
{
}


KTransform::~KTransform()
{
}



bool KTransform::init()
{
	name(L"KTransform");
	return true;
}
void KTransform::update()
{

}
void KTransform::release()
{

}


void KTransform::moving(const KVec2& _Speed)
{
	mPos += _Speed * KTimeManager::instance()->deltatime();
}