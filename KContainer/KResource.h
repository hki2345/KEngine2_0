#pragma once
#include <string>


class KResource
{
protected:
	KResource();
	KResource(const KResource& _Other) = delete;
	KResource(const KResource&& _Other) = delete;
	void operator=(const KResource& _Other) = delete;
	virtual ~KResource() = 0;

protected:
	std::wstring sName;
	std::wstring sPath;

protected:
	virtual bool create(const wchar_t* _Folder, const wchar_t* _Name) = 0;
	virtual bool load() = 0;
	virtual bool save() = 0;

public:
	bool check(const wchar_t* _Name);
	bool check(KResource* _Other);
};

