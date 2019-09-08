#include "KText_Render.h"
#include "KScene.h"
#include "KWindow.h"
#include "KOne.h"


KText_Render::KText_Render()
{
}


KText_Render::~KText_Render()
{
}



void KText_Render::set_text(
	const wchar_t* _Text,
	const int& _Size,
	const int& _Key/* = 0*/,
	const wchar_t* _Font/* = L"±Ã¼­"*/,
	const DWORD& _Color /*= RGB(255, 255, 255)*/)
{
	iMySize = _Size;
	MyColor = _Color;
	sMyParse = _Text;
	sMyFont = _Font;
	kscene()->insert_krender(this, _Key);
}

void KText_Render::set_text(const wchar_t* _Text)
{
	sMyParse = _Text;
}

void KText_Render::render()
{
	if (false == bRender)
	{
		return;
	}

	myFont = CreateFont(iMySize, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, sMyFont.c_str());
	oldFont = (HFONT)SelectObject(kwindow()->bhdc(), myFont);
	SetTextColor(kwindow()->bhdc(), MyColor);
	SetBkMode(kwindow()->bhdc(), TRANSPARENT);
	SetTextAlign(kwindow()->bhdc(), TA_CENTER);

	TextOutW(kwindow()->bhdc(), RenderPos.x, RenderPos.y, sMyParse.c_str(), sMyParse.size());

	SelectObject(kwindow()->bhdc(), oldFont);
	DeleteObject(myFont);
}