#pragma once
#include <map>
#include <string>
#include "KMacro.h"

//
//vector<T>::iterator i; // bad, vector<T>::iterator might not be a type
//	// depending on what 'T' is.  For example, there might be a specialization
//	// where iterator is defined as a member var instead of a type.
//
//typename vector<T>::iterator i;  // OK


template <class ResT>
class KResourceManager
{
private:
	KResourceManager() {};
	KResourceManager(const KResourceManager& _Other) = delete;
	KResourceManager(const KResourceManager&& _Other) = delete;
	void operator=(const KResourceManager& _Other) = delete;
	~KResourceManager() {};


	static KResourceManager<ResT>* pKResManager;

public:
	static KResourceManager<ResT>* instance()
	{
		if (nullptr == pKResManager)
		{
			pKResManager = new KResourceManager<ResT>();
		}

		return pKResManager;
	}

private:
	std::map<std::wstring, ResT*> MapRes;

public:
	void init() {}
	void release()
	{
		typename std::map<std::wstring, ResT*>::iterator SIter = MapRes.begin();
		typename std::map<std::wstring, ResT*>::iterator EIter = MapRes.end();

		for (; SIter != EIter; ++SIter)
		{
			RELEASE_PTR(SIter->second);
		}

		MapRes.clear();

		RELEASE_PTR(pKResManager);
	}



	ResT* find(const wchar_t* _Name)
	{
		typename std::map<std::wstring, ResT*>::iterator FIter = MapRes.find(_Name);

		if (MapRes.end() != FIter)
		{
			return FIter->second;
		}

		return nullptr;
	}

	ResT* create(const wchar_t* _Folder, const wchar_t* _Name)
	{
		ResT* NewRes = new ResT();
		NewRes->create(_Folder, _Name);

		MapRes.insert(std::make_pair(_Name, NewRes));
		return NewRes;
	}

	bool erase(const wchar_t* _Name)
	{
		typename std::map<std::wstring, ResT*>::iterator FIter = MapRes.find(_Name);

		if (MapRes.end() != FIter)
		{
			delete FIter->second;
			MapRes.erase(FIter);
			return true;
		}

		return false;
	}

	bool load(const wchar_t* _Name)
	{
		typename std::map<std::wstring, ResT*>::iterator FIter = MapRes.find(_Name);

		if (MapRes.end() != FIter)
		{
			return FIter->load();
		}

		return true;
	}
	
	bool save(const wchar_t* _Name)
	{
		typename std::map<std::wstring, ResT*>::iterator FIter = MapRes.find(_Name);

		if (MapRes.end() != FIter)
		{
			return FIter->save();
		}

		return true;
	}
};

template <class ResT>
KResourceManager<ResT>* KResourceManager<ResT>::pKResManager = nullptr;