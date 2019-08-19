#pragma once
#include <string>
#include "KMacro.h"



class KInputManager
{
public:
	friend class KCore;

public:
	// 본체에서는 해야하니까
	KInputManager() {} /* = delete*/;
	KInputManager(const KInputManager& _Core) = delete;
	KInputManager(const KInputManager&& _Core) = delete;
	void operator=(const KInputManager& _Core) = delete;
	~KInputManager() = delete;


private:
	static void update(const int& _Value);
	static bool is_press(const int& _Value);
};

