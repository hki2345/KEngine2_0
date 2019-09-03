#include "KRenderer.h"
#include "KTransform.h"
#include "KOne.h"



KRenderer::KRenderer()
{

}

KRenderer::~KRenderer()
{

}


bool KRenderer::init()
{
	MyTrans = kone()->get_component<KTransform>();


	return true;
}