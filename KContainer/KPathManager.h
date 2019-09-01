#pragma once
#include <string>

class KPathManager
{
public:
	friend class KCore;
	friend class KUnityParse;

private:
	// ��ü������ �ؾ��ϴϱ�
	KPathManager() {} /* = delete*/;
	KPathManager(const KPathManager& _Core) = delete;
	KPathManager(const KPathManager&& _Core) = delete;
	void operator=(const KPathManager& _Core) = delete;
	~KPathManager() {};


	static KPathManager* pKPathManager;

public:
	static KPathManager* instance()
	{
		if (nullptr == pKPathManager)
		{
			pKPathManager = new KPathManager();
		}

		return pKPathManager;
	}


private:
	std::wstring mAllpath;
	std::wstring mDrive;
	std::wstring mDirectory;
	std::wstring mFileName;
	std::wstring mExe;

private:
	void init();
	void release();

public:
	inline std::wstring& all_path()
	{
		return mAllpath;
	}
	inline std::wstring& drive()
	{
		return mDrive;
	}
	inline std::wstring& directory()
	{
		return mDirectory;
	}
	inline std::wstring& file_name()
	{
		return mFileName;
	}
	inline std::wstring& exe()
	{
		return mExe;
	}

	bool input_wchar(wchar_t* _Target, const int& _Target_sizeof, const wchar_t* _Path);
};

