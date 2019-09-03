#pragma once





class KWindow;
class PtrOf_KWindow
{
public:
	PtrOf_KWindow() {};
	PtrOf_KWindow(const PtrOf_KWindow& _Other) = delete;
	PtrOf_KWindow(const PtrOf_KWindow&& _Other) = delete;
	void operator=(const PtrOf_KWindow& _Other) = delete;
	~PtrOf_KWindow() {};



private:
	KWindow* pKWindow;

public:
	inline KWindow* kwindow()
	{
		return pKWindow;
	}

	inline void kwindow(KWindow* _Other)
	{
		pKWindow = _Other;
	}

};

