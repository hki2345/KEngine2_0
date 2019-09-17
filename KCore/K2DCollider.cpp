#include "K2DCollider.h"
#include "KTransform.h"
#include "KOne.h"
#include "KDebugManager.h"
#include "KWindow.h"
#include "KScene.h"
#include "KMath.h"

#include <Windows.h>

#include <math.h>


K2DCollider::K2DCollider()
{
}


K2DCollider::~K2DCollider()
{
}

void K2DCollider::create()
{
	if (nullptr == MyTrans)
	{
		MyTrans = kone()->get_component<KTransform>();
	}

	ListCollision.clear();
}

void K2DCollider::update()
{
	KComponent::update();
}

void K2DCollider::release()
{
	kscene()->delete_k2dcollider(this);
}



void K2DCollider::checking_deltabox()
{
	PrevPos += MyPivot;

	if (MyTrans->Pos.x == PrevPos.x)
	{
		DeltaBox.Start.x = PrevPos.x;
		DeltaBox.End.x = MyTrans->Pos.x + MyTrans->Size.x  * .5f;
	}
	else if (MyTrans->Pos.x > PrevPos.x)
	{
		DeltaBox.Start.x = PrevPos.x;
		DeltaBox.End.x = MyTrans->Pos.x + MyTrans->Size.x  * .5f;
	}
	else if (MyTrans->Pos.x < PrevPos.x)
	{
		DeltaBox.Start.x = MyTrans->Pos.x;
		DeltaBox.End.x = PrevPos.x + MyTrans->Size.x * .5f;
	}

	if (MyTrans->Pos.y == PrevPos.y)
	{
		DeltaBox.Start.y = PrevPos.y;
		DeltaBox.End.y = MyTrans->Pos.y + MyTrans->Size.y  * .5f;
	}
	else if (MyTrans->Pos.y > PrevPos.y)
	{
		DeltaBox.Start.y = PrevPos.y;
		DeltaBox.End.y = MyTrans->Pos.y + MyTrans->Size.y  * .5f;
	}
	else if (MyTrans->Pos.y < PrevPos.y)
	{
		DeltaBox.Start.y = MyTrans->Pos.y;
		DeltaBox.End.y = PrevPos.y + MyTrans->Size.y * .5f;
	}

	DeltaDistance = 9999999999999.0f;
}

void K2DCollider::update_collision(K2DCollider* _Other)
{
	KPos2 ColPos = MyTrans->Pos + MyPivot;
	KPos2 OtherColPos = _Other->MyTrans->Pos + _Other->MyPivot;
	float OtherDistance = (ColPos - OtherColPos).distance();
	PrevPos = MyTrans->Pos;


	switch (MyFigure)
	{
	case K2DCollider::COL2D_RECT:
		switch (_Other->MyFigure)
		{
		case K2DCollider::COL2D_RECT:
		{
			KRect R1 = {
				ColPos,
				ColPos + MyTrans->Size };
			KRect R2 = {
				OtherColPos,
				OtherColPos + _Other->MyTrans->Size };
			bool result = false;

			AABB(R1, R2, result);
			// AABB(DeltaBox, R2, result);

			if (true == result)
			{
				MyColliderRect.Start = R2.Start;
				MyColliderRect.End = DeltaBox.End;
				_Other->MyColliderRect.Start = R2.Start;
				_Other->MyColliderRect.End = DeltaBox.End;
				
				update_enterorstay(_Other);
				_Other->update_enterorstay(this);

				////////////////// 
				// if (DeltaDistance > OtherDistance)
				// {
				// 	DeltaDistance = OtherDistance;
				// 
				// 	MyColliderRect.Start = R2.Start;
				// 	MyColliderRect.End = DeltaBox.End;
				// 	_Other->MyColliderRect.Start = R2.Start;
				// 	_Other->MyColliderRect.End = DeltaBox.End;
				// 
				// 	update_enterorstay(_Other);
				// 	_Other->update_enterorstay(this);
				// }
				// else
				// {
				// 	update_exit(_Other);
				// 	_Other->update_exit(this);
				// }
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
		// stay
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
	udpate_list(ListEnterFunc, _Other);
}
void K2DCollider::update_stayfunc(KOne* _Other)
{
	udpate_list(ListStayFunc, _Other);
}
void K2DCollider::update_exitfunc(KOne* _Other)
{
	udpate_list(ListExitFunc, _Other);
}

void K2DCollider::udpate_list(std::list<std::function<void(KOne*)>>& _List, KOne* _Other)
{
	std::list<std::function<void(KOne*)>>::iterator SIter = _List.begin();
	std::list<std::function<void(KOne*)>>::iterator EIter = _List.end();

	for (; SIter != EIter; SIter++)
	{
		(*SIter)(_Other);
	}
}