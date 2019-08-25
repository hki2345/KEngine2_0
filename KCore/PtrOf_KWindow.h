#pragma once





class PtrOf_KWindow
{
public:
	PtrOf_KWindow() {};
	PtrOf_KWindow(const PtrOf_KWindow& _Core) = delete;
	PtrOf_KWindow(const PtrOf_KWindow&& _Core) = delete;
	void operator=(const PtrOf_KWindow& _Core) = delete;
	~PtrOf_KWindow() {};
};

