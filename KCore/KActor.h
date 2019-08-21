#pragma once
#include "KName.h"


class KActor
{
public:
	KActor();
	KActor(const KActor& _Core) = delete;
	KActor(const KActor&& _Core) = delete;
	void operator=(const KActor& _Core) = delete;
	virtual ~KActor() = 0;

private:
	bool bActing;
	bool bDeath;

public:
	bool& active()
	{
		return bActing;
	}

	bool& death()
	{
		return bDeath;
	}

	void active(const bool& _Value)
	{
		bActing = _Value;
	}

	void death(const bool& _Value)
	{
		bDeath = _Value;
	}
};

