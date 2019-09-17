#pragma once
#include "K2DCollider.h"
#include "KVector.h"
#include <Windows.h>



class KRect_Collision : public K2DCollider
{
public:
	KRect_Collision();
	~KRect_Collision();

private:
	KRect ColRect;
	DWORD MyColor;

public:
	void create() override;
	void update() override;
	void set_rect(const int& _Key);
	void render_debug() override;


	inline void render_color(const DWORD& _Color)
	{
		MyColor = _Color;
	}
};

