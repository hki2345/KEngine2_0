#pragma once
#include "KComponent.h"
#include "KVector.h"

#include <string>
#include <map>
#include <list>

#include <functional>


class KTransform;
class KOne;
class K2DCollider : public KComponent
{
public:
	friend class K2DColliderManager;

public:
	K2DCollider();
	~K2DCollider();

protected:
	enum COL_FIGURE
	{
		COL2D_RECT = 0,
		COL2D_CIRCLE,
		COL2D_POINT,
	};


protected:
	COL_FIGURE MyFigure;

	KTransform* MyTrans;
	KPos2 MyPivot;


private:
	std::list<K2DCollider*> ListCollision;

	std::multimap<std::wstring, std::function<void(KOne*)>> ListEnterFunc;
	std::multimap<std::wstring, std::function<void(KOne*)>> ListStayFunc;
	std::multimap<std::wstring, std::function<void(KOne*)>> ListExitFunc;


public:
	bool init() override;
	void update() override;

	void update_collision(K2DCollider* _Other);


	// 아오 써글...
	// 일당 ㅍ어셔널 사용법
	// https://en.cppreference.com/w/cpp/utility/functional/function
	template<typename T>
	void insert_enterfunc(const wchar_t* _Name, T* _This, void(T::*_Func)(KOne*))
	{
		// 함수 포인터, 객체 -이게 사실 멤버라 디스 객체를 넣어줌
		// 마지막으로 인자 수
		ListEnterFunc.insert(
			std::make_pair(_Name, std::bind(_Func, _This, std::placeholders::_1)));

		// 호출은 this, &클래스 명::함수이름 식으로 호출
		// 실상은 직접 클래스 호출하는 형태
	}

	template<typename T>
	void insert_stayfunc(const wchar_t* _Name, T* _This, void(T::*_Func)(KOne*))
	{
		ListStayFunc.insert(
			std::make_pair(_Name, std::bind(_Func, _This, std::placeholders::_1)));
	}
	template<typename T>
	void insert_exitfunc(const wchar_t* _Name, T* _This, void(T::*_Func)(KOne*))
	{
		ListExitFunc.insert(
			std::make_pair(_Name, std::bind(_Func, _This, std::placeholders::_1)));
	}


protected:
	void update_enterorstay(K2DCollider* _Other);
	void update_exit(K2DCollider* _Other);

	void update_enterfunc(KOne* _Other);
	void update_stayfunc(KOne* _Other);
	void update_exitfunc(KOne* _Other);

	std::list<K2DCollider*>::iterator find_listcol(K2DCollider* _Other);

public:

	inline void pivot(const KPos2& _Pivot)
	{
		MyPivot = _Pivot;
	}
};