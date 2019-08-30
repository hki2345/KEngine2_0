#pragma once
#include <string>
#include "KMacro.h"



class KInputManager
{
public:
	friend class KCore;

private:
	// 본체에서는 해야하니까
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

