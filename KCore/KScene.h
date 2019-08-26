#pragma once
#include "KProgress.h"
#include <map>



class KOne;
class KRenderManager;
class KScene : public KProgress
{
public:
	friend class KSceneManager;

protected:
	KScene();
	KScene(const KScene& _Core) = delete;
	KScene(const KScene&& _Core) = delete;
	void operator=(const KScene& _Core) = delete;
	virtual ~KScene() override {}/* = 0*/;


private:
	KRenderManager* curKRenderMgr;


	std::multimap<std::wstring, KOne*> MapKOne;
	
protected:
	virtual bool init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render();

	KOne* create_kone(const wchar_t* _Name = L"KOne");
	KOne* create_kone(KOne* _Other, const wchar_t* _Name = L"KOne");
	KOne* find_kone(const wchar_t* _Name);
	bool delete_kone(const wchar_t* _Name);
};

