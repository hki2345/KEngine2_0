#include "KFileStream.h"
#include "KMacro.h"




KFileStream* KFileStream::pKFileStream = nullptr;


void KFileStream::release()
{
	RELEASE_PTR(pKFileStream);
}