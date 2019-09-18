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

// 무조건 터진다.
#define KASSERT assert(false)
#define KNAMING 256