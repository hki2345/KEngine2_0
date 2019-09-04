#pragma once
#include <KResource.h>
#include <Windows.h>

#include "KVector.h"


class KBitMap  final : public KResource
{
public:
	friend class KBitMap_Render;

public:
	KBitMap();
	~KBitMap() override;

private:
	HDC MyDC;
	HBITMAP MyBitMap, OldBitmap;
	BITMAP	BitMapData;


public:
	// �� ���� �۾� kwindow_size ���
	bool create(const wchar_t* _Folder, const wchar_t* _Name) override;
	bool save() override;
	bool load() override;

	HDC& kwindow_size(const KSize2& _Size = KVec2( 100, 100 ));
	KPos2 size();
};

