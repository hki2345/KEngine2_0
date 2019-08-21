#pragma once
#include "KProgress.h"



class KComponent : public KProgress
{
public:
	friend class KOne;


public:
	KComponent();
	KComponent(const KComponent& _Core) = delete;
	KComponent(const KComponent&& _Core) = delete;
	void operator=(const KComponent& _Core) = delete;
	~KComponent() override;


protected:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void release() = 0;
};

