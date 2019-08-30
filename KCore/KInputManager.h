#pragma once
#include <string>
#include "KMacro.h"



class KInputManager
{
public:
	friend class KCore;

private:
	// ��ü������ �ؾ��ϴϱ�
	KInputManager() {} /* = delete*/;
	KInputManager(const KInputManager& _Core) = delete;
	KInputManager(const KInputManager&& _Core) = delete;
	void operator=(const KInputManager& _Core) = delete;
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
	void update(const int& _Value);
	bool is_press(const int& _Value);

	void release();
};

