#pragma once
#include "KProgress.h"
#include "KName.h"






class KComponent : public KProgress, KName
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
	virtual void init() override;
	virtual void update() override;
	virtual void release() override;
};

