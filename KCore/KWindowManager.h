#pragma once
class KWindowManager
{
public:
	KWindowManager() {} /* = delete*/;;
	KWindowManager(const KWindowManager& _Window) = delete;
	KWindowManager(const KWindowManager&& _Window) = delete;
	void operator=(const KWindowManager& _Window) = delete;
	~KWindowManager() {} ;


	static KWindowManager* pKWindow;
};

