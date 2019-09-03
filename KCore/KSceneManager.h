#pragma once
#include <map>
#include "PtrOf_KWindow.h"



class KScene;
class KSceneManager : public PtrOf_KWindow
{
public:
	friend class KCore;
	friend class KWindow;


private:
	// 본체에서는 해야하니까
	KSceneManager() : curscene(nullptr), bCurInit(false){} /* = delete*/;
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
	bool bCurInit;

	std::multimap<std::wstring, KScene*> MapScene;
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

