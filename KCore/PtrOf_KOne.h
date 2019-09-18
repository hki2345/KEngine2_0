#pragma once


class KOne;
class PtrOf_KOne
{
protected:
	PtrOf_KOne() : pKOne(nullptr) {};
	PtrOf_KOne(const PtrOf_KOne& _Core) = delete;
	PtrOf_KOne(const PtrOf_KOne&& _Core) = delete;
	void operator=(const PtrOf_KOne& _Core) = delete;
	~PtrOf_KOne() {};

public:
	KOne* pKOne;

public:
	inline KOne* kone()
	{
		return pKOne;
	}

	inline void kone(KOne* _One)
	{
		pKOne = _One;
	}
};

