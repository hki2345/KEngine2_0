#pragma once
#include "PtrOf_KWindow.h"
#include "KName.h"
#include "KActor.h"
#include "KVector.h"

#include <map>



class KOne;
class KRenderManager;
class KRenderer;
class KScene : 
	public PtrOf_KWindow,
	public KName,
	public KActor
{
public:
	friend class KSceneManager;

protected:
	KScene();
	KScene(const KScene& _Core) = delete;
	KScene(const KScene&& _Core) = delete;
	void operator=(const KScene& _Core) = delete;
	virtual ~KScene() {}/* = 0*/;

public:
	KPos2 SceneCamPos;


protected:
	KRenderManager* curKRenderMgr;

	std::multimap<std::wstring, KOne*> MapKOne;
	
public:
	bool insert_krender(KRenderer* _Render, const int& _Key = 0);
	KPos2 outof_screen(KOne* _Target);

protected:
	virtual void create();
	virtual bool init() ;
	virtual void update() ;
	virtual void out();
	virtual void release();
	virtual void render();

public:
	KOne* create_kone(const wchar_t* _Name = L"KOne");
	KOne* create_kone(KOne* _Other, const wchar_t* _Name = L"KOne");
	KOne* find_kone(const wchar_t* _Name);
	bool delete_kone(const wchar_t* _Name);
};

