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
	void operator<<(const wchar_t* _Log)
	{
		VectorLog.push_back(_Log);
	}
	void operator<<(const int& _Log)
	{
		VectorLog.push_back(std::to_wstring(_Log));
	}
	void operator<<(const float& _Log)
	{
		VectorLog.push_back(std::to_wstring(_Log));
	}

	void insert_log(const wchar_t* const _Str, ...);



private:
	void init();
	void update();
	void render();
	void release();
};