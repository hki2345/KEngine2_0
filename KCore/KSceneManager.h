#pragma once
#include <map>


class KScene;
class KSceneManager
{
public:
	friend class KCore;


private:
	// 본체에서는 해야하니까
	KSceneManager() : curscene(nullptr){} /* = delete*/;
	KSceneManager(const KSceneManager& _Core) = delete;
	KSceneManager(const KSceneManager&& _Core) = delete;
	void operator=(const KSceneManager& _Core) = delete;
	~KSceneManager() {};

	static KSceneManager* pKSceneManager;

	public:
		static KSceneManager* instance()
		{
			if (nullptr == pKSceneManager)
			{
				pKSceneManager = new KSceneManager();
			}

			return pKSceneManager;
		}

private:
	std::multimap<std::wstring, KScene*> MapScene;
	std::multimap<std::wstring, KScene*>::iterator mSMapScene;
	std::multimap<std::wstring, KScene*>::iterator mEMapScene;
	std::multimap<std::wstring, KScene*>::iterator mFMapScene;
	KScene* curscene;


private:
	void init() ;
	void update() ;
	void render();
	void release();

public:
	KScene* create_scene(KScene* _Other, const wchar_t* _Name = L"KScene");
	KScene* create_scene(const wchar_t* _Name = L"KScene");
	KScene* find_scene(const wchar_t* _Name);
	bool delete_scene(const wchar_t* _Name);
	bool change_scene(const wchar_t* _Name);
	inline KScene* cur_scene()
	{
		return curscene;
	}
};

