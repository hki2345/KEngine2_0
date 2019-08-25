#pragma once


class KScene;
class PtrOf_KScene
{
public:
	PtrOf_KScene() : pKScene(nullptr) {};
	PtrOf_KScene(const PtrOf_KScene& _Core) = delete;
	PtrOf_KScene(const PtrOf_KScene&& _Core) = delete;
	void operator=(const PtrOf_KScene& _Core) = delete;
	~PtrOf_KScene() {};



private:
	KScene* pKScene;

public:
	inline KScene* kscene()
	{
		return pKScene;
	}

	inline void kscene(KScene* _One)
	{
		pKScene = _One;
	}

};

