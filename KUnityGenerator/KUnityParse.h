#pragma once
#include <string>
#include <set>


class KUnityParse
{
public:
	KUnityParse();
	KUnityParse(const KUnityParse& _Core) = delete;
	KUnityParse(const KUnityParse&& _Core) = delete;
	void operator=(const KUnityParse& _Core) = delete;
	~KUnityParse();

	static KUnityParse* pKParse;
	 

private:
	std::multiset<std::string> MapCpp;
	std::string sTarget;



public:
	static KUnityParse* instance()
	{
		if (nullptr == pKParse)
		{
			pKParse = new KUnityParse();
		}

		return pKParse;
	}


public:
	void init();
	void loop();


private:
	void update();

	void load_cpp();
	void save_cpp();
};

