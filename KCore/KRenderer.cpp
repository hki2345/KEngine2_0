#include "KRenderer.h"
#include "KScene.h"

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
	bHold = false;
	bRender = false;
	if (nullptr ==MyTrans)
	{
		MyTrans = kone()->get_component<KTransform>();
	}

	return true;
}


void KRenderer::update_trans(const KPos2& _CameraPos)
{
	if (_CameraPos.x > MyTrans->Pos.x + MyTrans->Size.x)
	{
		bRender = false;
	}
	else if (_CameraPos.x  < (MyTrans->Pos.x) - 800 )
	{
		bRender = false;
	}
	else
	{
		bRender = true;
	}

	RenderPos = MyTrans->Pos - _CameraPos + MyPivot;
}