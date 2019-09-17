#pragma once
#include "PtrOf_KWindow.h"
#include "PtrOf_KOne.h"
#include "PtrOf_KScene.h"

#include "KName.h"
#include "KActor.h"


class KComponent : 
	public PtrOf_KWindow,
	public PtrOf_KScene,
	public PtrOf_KOne,
	public KName,
	public KActor
{
public:
	friend class KOne;


public:
	KComponent();
	KComponent(const KComponent& _Core) = delete;
	KComponent(const KComponent&& _Core) = delete;
	void operator=(const KComponent& _Core) = delete;
	virtual ~KComponent() {}/* = 0*/;


protected:
	virtual void create() {}
	virtual bool init(){ return false; } /*= 0*/
	virtual void update(){}/*= 0*/
	virtual void out() {}/*= 0*/
	virtual void render_debug () {}
	virtual void release() {}/*= 0*/
};

