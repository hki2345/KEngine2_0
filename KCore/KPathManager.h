#pragma once
#define KNAMING 256


class KPathManager
{
public:
	friend class KCore;

public:
	// 본체에서는 해야하니까
	KPathManager() {} /* = delete*/;
	KPathManager(const KPathManager& _Core) = delete;
	KPathManager(const KPathManager&& _Core) = delete;
	void operator=(const KPathManager& _Core) = delete;
	~KPathManager() = delete;




private:
	static wchar_t mAllpath[KNAMING];
	static wchar_t mDrive[KNAMING];
	static wchar_t mDirectory[KNAMING];
	static wchar_t mFileName[KNAMING];
	static wchar_t mExe[KNAMING];

private:
	static void init();

public:
	inline wchar_t* all_path()
	{
		return mAllpath;
	}
	inline wchar_t* drive()
	{
		return mDrive;
	}
	inline wchar_t* directory()
	{
		return mDirectory;
	}
	inline wchar_t* file_name()
	{
		return mFileName;
	}
	inline wchar_t* exe()
	{
		return mExe;
	}
};

