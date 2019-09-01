#pragma once
#include <map>
#include <string>

//
//vector<T>::iterator i; // bad, vector<T>::iterator might not be a type
//	// depending on what 'T' is.  For example, there might be a specialization
//	// where iterator is defined as a member var instead of a type.
//
//typename vector<T>::iterator i;  // OK


template <typename ResT>
class KResourceManager
{
private:
	KResourceManager() {}
	KResourceManager(const KResourceManager& _Other) = delete;
	KResourceManager(const KResourceManager&& _Other) = delete;
	void operator=(const KResourceManager& _Other) = delete;
	virtual ~KResourceManager() = 0 {}



private:
	static std::map<std::wstring, ResT*> MapRes;

public:
	static ResT* find(const wchar_t* _Name)
	{
		typename std::map<std::wstring, ResT*>::iterator FIter = MapRes.find(_Name);

		if (MapRes.end() != FIter)
		{
			return FIter->second;
		}

		return nullptr;
	}

	static ResT* create(const wchar_t* _Folder, const wchar_t* _Name)
	{
		ResT* NewRes = new ResT();
		NewRes->create(_Folder, _Name);

		MapRes.insert(std::make_pair(_Name, NewRes));
		return NewRes;
	}

	static bool erase(const wchar_t* _Name)
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

	static bool load(const wchar_t* _Name)
	{
		typename std::map<std::wstring, ResT*>::iterator FIter = MapRes.find(_Name);

		if (MapRes.end() != FIter)
		{
			return FIter->load();
		}

		return true;
	}
	
	static bool save(const wchar_t* _Name)
	{
		typename std::map<std::wstring, ResT*>::iterator FIter = MapRes.find(_Name);

		if (MapRes.end() != FIter)
		{
			return FIter->save();
		}

		return true;
	}
};


template <typename ResT>
std::map<std::wstring, ResT*> KResourceManager<ResT>::MapRes;
