#include <iostream>

using namespace std;

class AAA;
class KFloat
{
private:
	float X;

public:
	friend AAA;

public:
	void operator=( const float& _Value)
	{
		X = _Value; 
	}

	operator int()
	{
		return (int)X;
	}
};


class AAA
{
public:
	union 
	{
		KFloat s[2];

		struct
		{
			KFloat f1;
			KFloat f2;
		};
	};

public:
	AAA();
	~AAA();

private:

};

AAA::AAA()
{
}

AAA::~AAA()
{
}




int main()
{
	AAA as = AAA();
	as.f1 = 9.0f;
	as.f2 = 7.0f;

	int AA = as.f1;

	cout << as.s[0] << endl;
	cout << as.s[1] << endl;
	cout << as.f1 << endl;
	cout << as.f2 << endl;

	cout << endl;

	cout << sizeof(as.s[0]) << endl;
	cout << sizeof(as.f1) << endl;
	cout << sizeof(as) << endl;

	return 0;
}