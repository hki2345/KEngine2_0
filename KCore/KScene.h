#pragma once
#include "KProgress.h"
#include "KRenderer.h"
#include <map>



class KOne;
class KRenderManager;
class KScene : public KProgress, public KRenderer
{
public:
	friend class KSceneManager;

protected:
	KScene();
	KScene(const KScene& _Core) = delete;
	KScene(const KScene&& _Core) = delete;
	void operator=(const KScene& _Core) = delete;
	~KScene() override;


private:
	KRenderManager* curKRenderMgr;


	std::multimap<std::wstring, KOne*> MapKOne;
	std::multimap<std::wstring, KOne*>::iterator mSOneMap;
	std::multimap<std::wstring, KOne*>::iterator mEOneMap;
	std::multimap<std::wstring, KOne*>::iterator mFOneMap;

protected:
	virtual void init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;

	KOne* create_kone(const wchar_t* _Name);
	KOne* find_kone(const wchar_t* _Name);
	bool delete_kone(const wchar_t* _Name);
};

