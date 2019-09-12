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
		COL2D_RECT = 0,
		COL2D_CIRCLE,
		COL2D_POINT,
	};


protected:
	bool ColCheck;
	COL_FIGURE MyFigure;

	KTransform* MyTrans;
	KPos2 MyPivot;

	std::list<K2DCollider*> ListEnter;
	std::list<K2DCollider*> ListStay;
	std::list<K2DCollider*> ListExit;

public:
	bool init() override;
	void update() override;
	void update_collision(K2DCollider* _Other);

	void update_enter(K2DCollider* _Other, const bool& _Col);
	void update_stay(K2DCollider* _Other, const bool& _Col);
	void update_exit(K2DCollider* _Other, const bool& _Col);

	

	bool is_enter(K2DCollider* _Other);
	bool is_stay(K2DCollider* _Other);
	bool is_exit(K2DCollider* _Other);

	inline bool& is_col()
	{
		return ColCheck;
	}

	inline void pivot(const KPos2& _Pivot)
	{
		MyPivot = _Pivot;
	}
};