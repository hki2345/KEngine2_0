#pragma once
#include "KComponent.h"
#include "KVector.h"

#include <list>


class KTransform;
class K2DCollider : public KComponent
{
public:
	K2DCollider();
	~K2DCollider();

protected:
	enum COL_FIGURE
	{
		RECT = 0,
		CIRCLE,
		POINT,
	};


protected:
	COL_FIGURE MyFigure;

	KTransform* MyTrans;
	KPos2 MyPivot;

	std::list<K2DCollider*> ListEnter;
	std::list<K2DCollider*> ListStay;
	std::list<K2DCollider*> ListExit;

public:
	bool init() override;
	void update_collision(K2DCollider* _Other);

	void update_enter(K2DCollider* _Other, const bool& _Col);
	void update_stay(K2DCollider* _Other, const bool& _Col);
	void update_exit(K2DCollider* _Other, const bool& _Col);


	bool is_enter(K2DCollider* _Other);
	bool is_stay(K2DCollider* _Other);
	bool is_exit(K2DCollider* _Other);
};