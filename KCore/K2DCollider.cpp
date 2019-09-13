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

	ListCollision.clear();
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
				update_enterorstay(_Other);
				_Other->update_enterorstay(this);
			}
			else
			{
				update_exit(_Other);
				_Other->update_exit(this);
			}

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
}


void K2DCollider::update_enterorstay(K2DCollider* _Other)
{
	std::list<K2DCollider*>::iterator Fiter = find_listcol(_Other);

	if (ListCollision.end() == Fiter)
	{
		// Enter
		ListCollision.push_back(_Other);

		update_enterfunc(_Other->kone());
	}
	else
	{
		// Stay
		update_stayfunc(_Other->kone());
	}
}
void K2DCollider::update_exit(K2DCollider* _Other)
{
	std::list<K2DCollider*>::iterator Fiter = find_listcol(_Other);

	if (ListCollision.end() != Fiter)
	{
		// Exit
		ListCollision.erase(Fiter);

		update_exitfunc(_Other->kone());
	}
}



std::list<K2DCollider*>::iterator K2DCollider::find_listcol(K2DCollider* _Other)
{
	std::list<K2DCollider*>::iterator FIter = ListCollision.begin();
	std::list<K2DCollider*>::iterator EIter = ListCollision.end();

	for (; FIter != EIter; ++FIter)
	{
		if ((*FIter) == _Other)
		{
			break;
		}
	}

	return FIter;
}




void K2DCollider::update_enterfunc(KOne* _Other)
{
	std::list<std::function<void(KOne*)>>::iterator SIter = ListEnterFunc.begin();
	std::list<std::function<void(KOne*)>>::iterator EIter = ListEnterFunc.end();

	for (; SIter != EIter; SIter++)
	{
		(*SIter)(_Other);
	}
}
void K2DCollider::update_stayfunc(KOne* _Other)
{
	std::list<std::function<void(KOne*)>>::iterator SIter = ListStayFunc.begin();
	std::list<std::function<void(KOne*)>>::iterator EIter = ListStayFunc.end();

	for (; SIter != EIter; SIter++)
	{
		(*SIter)(_Other);
	}
}
void K2DCollider::update_exitfunc(KOne* _Other)
{
	std::list<std::function<void(KOne*)>>::iterator SIter = ListExitFunc.begin();
	std::list<std::function<void(KOne*)>>::iterator EIter = ListExitFunc.end();

	for (; SIter != EIter; SIter++)
	{
		(*SIter)(_Other);
	}
}