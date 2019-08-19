#pragma once
#include "KProgress.h"
#include "KName.h"
#include <map>


class KComponent;
class KOne : public KProgress, KName
{
public:
	friend class KScene;

protected:
	KOne();
	KOne(const KOne& _Core) = delete;
	KOne(const KOne&& _Core) = delete;
	void operator=(const KOne& _Core) = delete;
	~KOne() override;


private:
	std::map<std::wstring, KComponent*> MapComponent;
	std::map<std::wstring, KComponent*>::iterator mSMapComponent;
	std::map<std::wstring, KComponent*>::iterator mEMapComponent;
	std::map<std::wstring, KComponent*>::iterator mFMapComponent;


protected:
	virtual void init() override;
	virtual void update() override;
	virtual void release() override;
};

