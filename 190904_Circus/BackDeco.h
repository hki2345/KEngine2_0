#pragma once
#include <KComponent.h>


class ComPlayer;
class BackDeco : public KComponent
{
public:
	BackDeco();
	~BackDeco();

private:
	ComPlayer* pPlayer;
	float fWallSpeed;



public:
	bool init() override;
	void update() override;

	inline void set_player(ComPlayer* _Other)
	{
		pPlayer = _Other;
	}

};

