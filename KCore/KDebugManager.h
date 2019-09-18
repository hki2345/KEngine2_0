#pragma once
#include <vector>
#include <string>


class KDebugManager
{
public:
	friend class KCore;
	friend class KScene;

private:
	KDebugManager() {}
	KDebugManager(const KDebugManager& _Other) = delete;
	KDebugManager(const KDebugManager&& _Other) = delete;
	void operator=(const KDebugManager& _Other) = delete;
	~KDebugManager() {};

	static KDebugManager* pKDebugManager;

public:
	static KDebugManager* instance()
	{
		if (nullptr == pKDebugManager)
		{
			pKDebugManager = new KDebugManager();
		}

		return pKDebugManager;
	}

private:
	bool bDebugAll;
	bool bDebugFigure;
	std::vector<std::wstring> VectorLog;


public:
	void insert_log(const wchar_t* const _Str, ...);



private:
	void init();
	void update();
	void render();
	void release();
};