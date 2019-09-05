#pragma once
#include "KRenderer.h"
#include <string>
#include <Windows.h>


class KText_Render : public KRenderer
{
public:
	KText_Render();
	~KText_Render();


private:
	int iMySize;
	std::wstring sMyParse;
	std::wstring sMyFont;
	DWORD MyColor;
	HFONT myFont;
	HFONT oldFont;

public:
	void set_text(
		const wchar_t* _Text,
		const wchar_t* _Font = L"�ü�",
		const int& _Size = 20,
		const int& _Key = 0, 
		const DWORD& _Color = RGB(255, 255, 255));

	void render() override;
};

