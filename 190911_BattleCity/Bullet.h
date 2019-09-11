#pragma once
#include <KComponent.h>
#include <KVector.h>



class KSprite_Render;
class Bullet : public KComponent
{
public:
	Bullet();
	~Bullet();

private:
	KSprite_Render* MySprite;
	KPos2 vDir;
	float fSpeed;

public:
	void create() override;
	void set_bullet(const KPos2& _Pos, const KPos2& _Dir);
	void update() override;
};

