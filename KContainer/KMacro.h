#pragma once
#include <assert.h>



#define RELEASE_PTR(PTR) \
{\
	if (nullptr != PTR)\
	{\
		delete PTR;\
		PTR = nullptr;\
	}\
}

// ������ ������.
#define KASSERT assert(false)
#define KNAMING 256