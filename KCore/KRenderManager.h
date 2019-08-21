#pragma once



class KRenderer;
class KRenderManager
{
public:
	friend class KCore;

public:
	KRenderManager() {};
	KRenderManager(const KRenderManager& _Core) = delete;
	KRenderManager(const KRenderManager&& _Core) = delete;
	void operator=(const KRenderManager& _Core) = delete;
	~KRenderManager() {};

	static KRenderManager* pKRenderManager;

public:
	static KRenderManager* instance()
	{
		if (nullptr == pKRenderManager)
		{
			pKRenderManager = new KRenderManager();
		}

		return pKRenderManager;
	}


private:
	void init();
	void render();
	void release();
};

