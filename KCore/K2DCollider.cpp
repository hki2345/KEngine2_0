#include "K2DCollider.h"
#include "KTransform.h"
#include "KOne.h"

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

void K2DCollider::update_collision(K2DCollider* _Other)
{
	bool Check;

	switch (MyFigure)
	{
	case K2DCollider::RECT:
		switch (_Other->MyFigure)
		{
		case K2DCollider::RECT:
			if (fabsf(MyTrans->Pos.x - _Other->MyTrans->Pos.x) <= MyTrans->Size.x + _Other->MyTrans->Size.x &&
				fabsf(MyTrans->Pos.y - _Other->MyTrans->Pos.y) <= MyTrans->Size.y + _Other->MyTrans->Size.y)
			{
				Check =  true;
			}
			break;
		case K2DCollider::CIRCLE:
			break;
		case K2DCollider::POINT:
			break;
		default:
			break;
		}
		break;
	case K2DCollider::CIRCLE:	
		switch (_Other->MyFigure)
		{
		case K2DCollider::RECT:
			break;
		case K2DCollider::CIRCLE:
			break;
		case K2DCollider::POINT:
			break;
		default:
			break;
		}
		break;
	case K2DCollider::POINT:
		switch (_Other->MyFigure)
		{
		case K2DCollider::RECT:
			break;
		case K2DCollider::CIRCLE:
			break;
		case K2DCollider::POINT:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	update_enter(_Other, Check);
	update_stay(_Other, Check);
	update_exit(_Other, Check);

	return Check;
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