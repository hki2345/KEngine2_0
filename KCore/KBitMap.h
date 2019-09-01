#pragma once
#include <KResource.h>
#include <Windows.h>

#include "KVector.h"


class KBitMap  final : public KResource
{
public:
	KBitMap();
	~KBitMap();

private:
	HDC MyDC;
	HBITMAP MyBitMap, OldBitmap;
	BITMAP	BitMapData;

public:
	// 이 이후 작업 size 요망
	bool create(const wchar_t* _Folder, const wchar_t* _Name) override;
	bool save() override;
	bool load() override;

	HDC& size(const KSize2& _Size = KVec2( 100, 100 ));
	inline HDC& hdc()
	{
		return MyDC;
	}
};

