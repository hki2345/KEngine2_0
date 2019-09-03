#pragma once
#include <vector>
#include <string>

class KPathManager
{
public:
	friend class KCore;
	friend class KUnityParse;

private:
	// 본체에서는 해야하니까
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
	std::vector<std::wstring> vec_loadline(const wchar_t* _Path);
	std::vector<std::wstring> split_line(wchar_t* _Path, const std::wstring& _Split = L" ,\t\n");
	std::vector<std::wstring> split_line(
		const std::vector<std::wstring>& _Vec, 
		const std::wstring& _Split = L" ,\t\n",
		const int& idx = 0);
};

