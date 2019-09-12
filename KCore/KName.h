#pragma once
#include <string>


class KName
{
public:
	KName();
	KName(const KName& _Core) = delete;
	KName(const KName&& _Core) = delete;
	void operator=(const KName& _Core) = delete;
	~KName();

public:
	std::wstring sName;
};

