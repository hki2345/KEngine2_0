#pragma once
#include <KResource.h>
#include <Windows.h>

#include "KVector.h"


class KBitMap  final : public KResource
{
public:
	friend class KBitMap_Render;
	friend class KBitMap_Animator;

public:
	KBitMap();
	~KBitMap() override;

private:
	HDC MyDC;
	HBITMAP MyBitMap, OldBitmap;
	BITMAP	BitMapData;


public:
	// �� ���� �۾� kwindow_size ���
	bool load() override;
	bool save() override;

	HDC& kwindow_size(const KSize2& _Size = KVec2( 100, 100 ));
	KPos2 size();
};

