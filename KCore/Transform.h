#pragma once
#include "KComponent.h"
#include "KVector.h"



class Transform : public KComponent
{
public:
	Transform();
	~Transform();

public:
	bool init() override;
	void update() override;
	void release() override;


private:
	KVec2	mPos;

public:
	inline void pos(const KVec2& _Other)
	{
		mPos = _Other;
	}

	inline KVec2& pos()
	{
		return mPos;
	}

};

