#pragma once
#include <assert.h>


template <typename Ptr>
void release_ptr(Ptr& _Value)
{
	if (nullptr != _Value)
	{
		delete _Value;
		_Value = nullptr;
	}
}


// ������ ������.
void kassert()
{
	assert(false);
}
