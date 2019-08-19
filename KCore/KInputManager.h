#pragma once
class KInputManager
{
public:
	friend class KCore;

public:
	// ��ü������ �ؾ��ϴϱ�
	KInputManager() {} /* = delete*/;
	KInputManager(const KInputManager& _Core) = delete;
	KInputManager(const KInputManager&& _Core) = delete;
	void operator=(const KInputManager& _Core) = delete;
	~KInputManager() = delete;


private:
	static void init();
	static void update();
};

