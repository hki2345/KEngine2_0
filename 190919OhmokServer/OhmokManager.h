#pragma once
#include <KMacro.h>
#include <vector>
#include <KVector.h>


#define PANLINE (19)
#define PANSIZE (PANLINE* PANLINE)
#define BLACKSIZE ((int)(19*19 / 2) + 1)
#define WHITESIZE ((int)(19*19 / 2))

#define DOLESIZE (32)

#define VOIDDOLE 0
#define BLACKDOLE 1
#define WHITEDOLE 2

#define SETOFF 0
#define SETON 1

struct Dole
{
	int x;
	int y;
	int color;
	int set;
};

class KScene;
class KOne;
class OhmokManager
{
private:
	// 본체에서는 해야하니까
	OhmokManager() {} /* = delete*/;
	OhmokManager(const OhmokManager& _Other) = delete;
	OhmokManager(const OhmokManager&& _Other) = delete;
	void operator=(const OhmokManager& _Other) = delete;
	~OhmokManager() {};
	static OhmokManager* pOhmokManager;

public:
	static OhmokManager* instance()
	{
		if (nullptr == pOhmokManager)
		{
			pOhmokManager = new OhmokManager();
		}

		return pOhmokManager;
	}
public:
	void release()
	{
		RELEASE_PTR(pOhmokManager);
	}


private:
	enum OHMOKSTATE
	{
		BLACK,
		WHITE,
		DONE,
	};

private:
	KScene* MyScene;
	std::vector<KOne*> VectorBlack;
	std::vector<KOne*> VectorWhite;
	std::vector<Dole> VectorPan;

	KPos2 LineSize;
	OHMOKSTATE eOState;

public:
	void create();
	void update();

private:
	void update_dole();
	void update_input();

	void update_black(const int& _X, const int& _Y);
	void update_white(const int& _X, const int& _Y);
	KPos2 pan_topos(const int& _X, const int& _Y);
	void put_dole(const KPos2& _Pos);
};