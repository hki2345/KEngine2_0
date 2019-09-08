#pragma once
#include <vector>
#include <string>

class KDebugManager
{
public:
	friend class KCore;

private:
	KDebugManager() {}
	KDebugManager(const KDebugManager& _Other) = delete;
	KDebugManager(const KDebugManager&& _Other) = delete;
	void operator=(const KDebugManager& _Other) = delete;
	~KDebugManager() {};


private:
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

	wchar_t* operator<<(const wchar_t* _Parse, const float& _Log)
	{
		VectorLog.push_back(std::to_wstring(_Log));
	}

public:
	void init();

	void render();
	void release();
};