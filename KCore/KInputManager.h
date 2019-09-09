#pragma once
#include <string>
#include <map>
#include "KMacro.h"



class KInputManager
{
public:
	friend class KCore;

private:
	// ��ü������ �ؾ��ϴϱ�
	KInputManager() {} /* = delete*/;
	KInputManager(const KInputManager& _Other) = delete;
	KInputManager(const KInputManager&& _Other) = delete;
	void operator=(const KInputManager& _Other) = delete;
	~KInputManager() {};
	static KInputManager* pKInputManager;

public:
	static KInputManager* instance()
	{
		if (nullptr == pKInputManager)
		{
			pKInputManager = new KInputManager();
		}

		return pKInputManager;
	}


public:
	bool is_down(const int& _Value);
	bool is_press(const int& _Value);
	bool is_up(const int& _Value);
	bool is_unpress(const int& _Value);

	void release();
};

