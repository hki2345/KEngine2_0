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
	bool bTankCol;

	Tile* PrevColTile;
	Tank* PrevColTank;

public:
	virtual bool init() override;
	virtual void create() override;
	virtual void update() override;

protected:
	void update_coltile();
	void update_checkingpos();

	void calculate_checkpos();
	virtual void update_move();



	virtual void stay_tile(KOne* _Tile);
	virtual void exit_tile(KOne* _Tile);
};

