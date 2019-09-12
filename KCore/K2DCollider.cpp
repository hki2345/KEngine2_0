#include "K2DCollider.h"
#include "KTransform.h"
#include "KOne.h"
#include "KDebugManager.h"
#include "KWindow.h"

#include <Windows.h>

#include <math.h>


K2DCollider::K2DCollider()
{
}


K2DCollider::~K2DCollider()
{
}

bool K2DCollider::init()
{
	if (nullptr == MyTrans)
	{
		MyTrans = kone()->get_component<KTransform>();
	}
	return true;
}

void K2DCollider::update()
{
	KComponent::update();
}

void K2DCollider::update_collision(K2DCollider* _Other)
{

	KPos2 ColPos = MyTrans->Pos + MyPivot;

	switch (MyFigure)
	{
	case K2DCollider::COL2D_RECT:
		switch (_Other->MyFigure)
		{
		case K2DCollider::COL2D_RECT:
		{
			RECT R1 = {
				ColPos.x,
				ColPos.y,
				ColPos.x + MyTrans->Size.x ,
				ColPos.y + MyTrans->Size.y };
			RECT R2 = {
				_Other->MyTrans->Pos.x,
				_Other->MyTrans->Pos.y,
				_Other->MyTrans->Pos.x + _Other->MyTrans->Size.x ,
				_Other->MyTrans->Pos.y + _Other->MyTrans->Size.y };;
			RECT Tmp;

			if (TRUE == IntersectRect(&Tmp, &R1, &R2))
			{
				ColCheck = true;
				_Other->ColCheck = true;
				KDebugManager::instance()->insert_log(L"Col to R2: %d %d %d %d", R2.left, R2.right, R2.top, R2.bottom );
			}
			else
			{
				ColCheck = false;
				_Other->ColCheck = false;
			}

			//if ((MyTrans->Pos.x + MyTrans->Size.x >= _Other->MyTrans->Pos.x &&
			//	MyTrans->Pos.y + MyTrans->Size.y >= _Other->MyTrans->Pos.y  ) &&
			//	(
			//	_Other->MyTrans->Pos.x + _Other->MyTrans->Size.x >= MyTrans->Pos.x &&
			//	_Other->MyTrans->Pos.y + _Other->MyTrans->Size.y >= MyTrans->Pos.y))
			//{
			//	KDebugManager::instance()->insert_log(L"Col to: %d %d %d %d", 
			//		_Other->MyTrans->Pos.x,
			//		_Other->MyTrans->Pos.y,
			//		_Other->MyTrans->Size.x,
			//		_Other->MyTrans->Size.y);
			//	Check = true;
			//}
		break;
		}
		case K2DCollider::COL2D_CIRCLE:
			break;
		case K2DCollider::COL2D_POINT:
			break;
		default:
			break;
		}
		break;
	case K2DCollider::COL2D_CIRCLE:	
		switch (_Other->MyFigure)
		{
		case K2DCollider::COL2D_RECT:
			break;
		case K2DCollider::COL2D_CIRCLE:
			break;
		case K2DCollider::COL2D_POINT:
			break;
		default:
			break;
		}
		break;
	case K2DCollider::COL2D_POINT:
		switch (_Other->MyFigure)
		{
		case K2DCollider::COL2D_RECT:
			break;
		case K2DCollider::COL2D_CIRCLE:
			break;
		case K2DCollider::COL2D_POINT:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
/*
	update_enter(_Other, Check);
	update_stay(_Other, Check);
	update_exit(_Other, Check);*/
}



void K2DCollider::update_enter(K2DCollider* _Other, const bool& _Col)
{
	std::list<K2DCollider*>::iterator SIter = ListEnter.begin();
	std::list<K2DCollider*>::iterator EIter = ListEnter.end();

	for (; SIter != EIter; ++SIter)
	{
		if ((*SIter) == _Other && true == _Col)
		{
			ListEnter.erase(SIter);
			return;
		}
	}

	if (ListEnter.end() == SIter && true == _Col && false == is_stay(_Other))
	{
		ListEnter.push_back(_Other);
	}
}
void K2DCollider::update_stay(K2DCollider* _Other, const bool& _Col)
{
	std::list<K2DCollider*>::iterator SIter = ListStay.begin();
	std::list<K2DCollider*>::iterator EIter = ListStay.end();

	for (; SIter != EIter; ++SIter)
	{
		if ((*SIter) == _Other && false == _Col)
		{
			ListStay.erase(SIter);
			ListExit.push_back(_Other);
			break;
		}
	}
}
void K2DCollider::update_exit(K2DCollider* _Other, const bool& _Col)
{
	std::list<K2DCollider*>::iterator SIter = ListExit.begin();
	std::list<K2DCollider*>::iterator EIter = ListExit.end();

	for (; SIter != EIter; ++SIter)
	{
		if ((*SIter) == _Other && false == _Col)
		{
			ListExit.erase(SIter);
		}
	}
}



bool K2DCollider::is_enter(K2DCollider* _Other)
{
	std::list<K2DCollider*>::iterator SIter = ListEnter.begin();
	std::list<K2DCollider*>::iterator EIter = ListEnter.end();

	for (; SIter != EIter; ++SIter)
	{
		if ((*SIter) == _Other)
		{
			return true;
		}
	}
	return false;
}
bool K2DCollider::is_stay(K2DCollider* _Other)
{
	std::list<K2DCollider*>::iterator SIter = ListStay.begin();
	std::list<K2DCollider*>::iterator EIter = ListStay.end();

	for (; SIter != EIter; ++SIter)
	{
		if ((*SIter) == _Other)
		{
			return true;
		}
	}
	return false;
}
bool K2DCollider::is_exit(K2DCollider* _Other)
{
	std::list<K2DCollider*>::iterator SIter = ListExit.begin();
	std::list<K2DCollider*>::iterator EIter = ListExit.end();

	for (; SIter != EIter; ++SIter)
	{
		if ((*SIter) == _Other)
		{
			return true;
		}
	}
	return false;
}