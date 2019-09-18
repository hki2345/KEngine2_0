#pragma once
#include "KName.h"


class KScene;
class KActor
{
public:
	friend KScene;

protected:
	KActor();
	KActor(const KActor& _Core) = delete;
	KActor(const KActor&& _Core) = delete;
	void operator=(const KActor& _Core) = delete;
	virtual ~KActor() = 0;

private:
	bool bActing;
	bool bDeath;
	bool bNextActing;

public:	
	inline bool active()
	{
		return bActing & bNextActing;
	}
	inline void active(const bool& _Value)
	{
		bNextActing = _Value;
	}

	inline bool& death()
	{
		return bDeath;
	}
	inline void death(const bool& _Value)
	{
		bDeath = _Value;
	}
};

