#pragma once
#include "KComponent.h"
#include "KVector.h"



class KTransform : public KComponent
{
public:
	KTransform();
	~KTransform();

public:
	bool init() override;
	void update() override;
	void release() override;


private:
	KVec2	mPos;
	KSize2	mSize;

public:
	void moving(const KVec2& _Speed);

	inline void pos(const KVec2& _Other)
	{
		mPos = _Other;
	}

	inline KVec2& pos()
	{
		return mPos;
	}


	inline void size(const KVec2& _Other)
	{
		mSize = _Other;
	}

	inline KVec2& size()
	{
		return mSize;
	}
};

