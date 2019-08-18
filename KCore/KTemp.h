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


// 무조건 터진다.
void kassert()
{
	assert(false);
}
