#pragma once
#include "KProgress.h"
#include "PtrOf_KOne.h"
#include "PtrOf_KScene.h"


class KComponent : public KProgress, PtrOf_KOne, PtrOf_KScene
{
public:
	friend class KOne;


public:
	KComponent();
	KComponent(const KComponent& _Core) = delete;
	KComponent(const KComponent&& _Core) = delete;
	void operator=(const KComponent& _Core) = delete;
	virtual ~KComponent() override {}/* = 0*/;


protected:
	virtual bool init() override;
	virtual void update() override;
	virtual void release() override;
};

