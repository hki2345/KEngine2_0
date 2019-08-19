#pragma once
#include <map>


class KScene;
class KSceneManager
{
public:
	friend class KCore;


private:
	// ��ü������ �ؾ��ϴϱ�
	KSceneManager() {} /* = delete*/;
	KSceneManager(const KSceneManager& _Core) = delete;
	KSceneManager(const KSceneManager&& _Core) = delete;
	void operator=(const KSceneManager& _Core) = delete;
	~KSceneManager() = delete;


private:
	static std::map<std::wstring, KScene*> MapScene;
	static std::map<std::wstring, KScene*>::iterator mSMapScene;
	static std::map<std::wstring, KScene*>::iterator mEMapScene;
	static std::map<std::wstring, KScene*>::iterator mFMapScene;
	static KScene* curscene;


private:
	static void init() ;
	static void update() ;
	static void release();

public:
	static KScene* create_scene(const wchar_t* _Name);
	static KScene* find_scene(const wchar_t* _Name);
	static bool delete_scene(const wchar_t* _Name);
	static bool change_scene(const wchar_t* _Name);
	inline static KScene* cur_scene()
	{
		return curscene;
	}
};

