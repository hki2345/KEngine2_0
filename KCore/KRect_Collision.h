#pragma once
#include "K2DCollider.h"


class KRect_Collision : public K2DCollider
{
public:
	KRect_Collision();
	~KRect_Collision();

public:
	void set_rect(const int& _Key);
};

