#pragma once
#include "CircusObject.h"


class ComPlayer;
class KBitMap_Animator;
class BackDeco : public CircusObject
{
public:
	BackDeco();
	~BackDeco();

private:
	bool bActiveDeco;
	KBitMap_Animator* pDecoAnimator;

public:
	bool init() override;
	void update() override;

	inline void set_activedeco()
	{
		bActiveDeco = true;
	}
};

