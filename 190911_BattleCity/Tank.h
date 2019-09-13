#pragma once
#include <KComponent.h>
#include <KVector.h>
#include <vector>


class KSprite_Animator;
class KRect_Collision;
class Bullet;
class Tile;
class Tank : public KComponent
{
public:
	Tank();
	~Tank();

protected:
	std::vector<Bullet*> VectorMyBullet;
	KSprite_Animator* MyAnimator;
	KRect_Collision* MyCollider;

	KPos2 vPrevDir;
	KPos2 vDir;
	KPos2 vPrevChecPos;
	float fSpeed;

	bool bTileCol;

	Tile* PrevColTile;

public:
	virtual bool init() override;
	virtual void create() override;
	virtual void update() override;

protected:
	void update_coltile();
	void update_checkingpos();
	virtual void update_move();



	void stay_tile(KOne* _Tile);
	void exit_tile(KOne* _Tile);
};

