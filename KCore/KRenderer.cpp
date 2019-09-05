#include "KRenderer.h"
#include "KTransform.h"
#include "KOne.h"



KRenderer::KRenderer() : MyPivot (KPos2::Zero)
{

}

KRenderer::~KRenderer()
{

}


bool KRenderer::init()
{
	if (nullptr ==MyTrans)
	{
		MyTrans = kone()->get_component<KTransform>();
	}
	

	return true;
}