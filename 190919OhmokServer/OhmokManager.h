#pragma once
#include <KMacro.h>
#include <vector>

#define PANLINE 19
#define BLACKSIZE ((int)(19*19 / 2) + 1)
#define WHITESIZE ((int)(19*19 / 2))

#define DOLESIZE (30)

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
	KScene* MyScene;
	std::vector<KOne*> VectorBlack;
	std::vector<KOne*> VectorWhite;

	float OneX;

public:
	void create();
	void update();
};