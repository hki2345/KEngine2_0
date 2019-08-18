#pragma once
#include <string>


class KName
{
public:
	KName();
	~KName();

private:
	std::wstring sName;

public:
	inline void name(const wchar_t* _Value)
	{
		sName = _Value;
	}

	inline const std::wstring& name()
	{
		return sName;
	}

	inline const wchar_t* name_str() const
	{
		return sName.c_str();
	}
};

