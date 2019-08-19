#pragma once
#include "KProgress.h"
#include "KName.h"
#include <map>



class KOne;
class KScene : public KProgress, KName
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
	std::map<std::wstring, KOne*> MapKOne;
	std::map<std::wstring, KOne*>::iterator mSOneMap;
	std::map<std::wstring, KOne*>::iterator mEOneMap;
	std::map<std::wstring, KOne*>::iterator mFOneMap;

protected:
	virtual void init() override;
	virtual void update() override;
	virtual void release() override;

	KOne* create_kone(const wchar_t* _Name);
	KOne* find_kone(const wchar_t* _Name);
	bool delete_kone(const wchar_t* _Name);
};

