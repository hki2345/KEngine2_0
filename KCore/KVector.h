#pragma once
#include <math.h>



class KVec2
{
public:

	struct
	{
		float x;
		float y;
	};/*
	union
	{
		float s[2];

		struct
		{
			float x;
			float y;
		};

		struct
		{
			float m1;
			float m2;
		};

		struct
		{
			int ix;
			int iy;
		};

		__int64 m_i64;
	};*/


public:
	KVec2() : x(.0f), y(.0f) {}
	/*KVec2(__int64 _Value) : m_i64(_Value) {}*/
	KVec2(float _Value) : x(_Value), y(_Value) {}
	KVec2(float _x, float _y) : x(_x), y(_y) {}
	/*KVec2(int _x, int _y) : ix(_x), iy(_y) {}*/
	KVec2(const KVec2& _Other) 
	{
		x = _Other.x;
		y = _Other.y;
	}


public:
	const static KVec2 Zero;
	const static KVec2 Left;
	const static KVec2 Right;
	const static KVec2 Up;
	const static KVec2 Down;


	void set_vector2(const float& _X, const float& _Y) { x = _X; y = _Y; }
	float x_part() const { return x * .5f; }
	float y_part() const { return y * .5f; }

	/*KVec2 IntToFloat() const
	{
		return KVec2((float)ix, (float)iy);
	}

	KVec2 FloatToInt() const
	{
		return KVec2(ix, iy);
	}
*/
	KVec2 operator + (const KVec2& _Other)
	{
		return{ x + _Other.x, y + _Other.y };
	}

	KVec2& operator = (const KVec2& _Value)
	{
		x = _Value.x;
		y = _Value.y;
		return *this;
	}


	KVec2 operator + (const KVec2& _Value) const
	{
		return KVec2(x + _Value.x, y + _Value.y);
	}
	KVec2 operator * (const KVec2& _Value) const
	{
		return KVec2(x * _Value.x, y * _Value.y);
	}
	KVec2 operator - (const KVec2& _Value) const
	{
		return KVec2(x - _Value.x, y - _Value.y);
	}
	KVec2 operator / (const KVec2& _Value) const
	{
		return KVec2(x / _Value.x, y / _Value.y);
	}

	KVec2 operator + (const float& _Value) const
	{
		return KVec2(x + _Value, y + _Value);
	}
	KVec2 operator * (const float& _Value)const
	{
		return KVec2(x * _Value, y * _Value);
	}
	KVec2 operator - (const float& _Value)const
	{
		return KVec2(x - _Value, y - _Value);
	}
	KVec2 operator / (const float& _Value)const
	{
		return KVec2(x / _Value, y / _Value);
	}



	KVec2& operator += (const KVec2& _Value)
	{
		x += _Value.x;
		y += _Value.y;

		return *this;
	}
	KVec2& operator -= (const KVec2& _Value)
	{
		x -= _Value.x;
		y -= _Value.y;

		return *this;
	}
	KVec2& operator *= (const KVec2& _Value)
	{
		x *= _Value.x;
		y *= _Value.y;

		return *this;
	}
	KVec2& operator /= (const KVec2& _Value)
	{
		x /= _Value.x;
		y /= _Value.y;

		return *this;
	}

	bool operator == (const KVec2& _Value)
	{
		return (x == _Value.x && y == _Value.y);
	}
	bool operator != (const KVec2& _Value)
	{
		return (x != _Value.x || y != _Value.y);
	}


	bool operator == (const KVec2& _Value) const
	{
		return (x == _Value.x && y == _Value.y);
	}
	bool operator != (const KVec2& _Value) const
	{
		return (x != _Value.x || y != _Value.y);
	}
	bool operator >= (const KVec2& _Value) const
	{
		return (x >= _Value.x && y >= _Value.y);
	}
	bool operator <= (const KVec2& _Value) const
	{
		return (x <= _Value.x && y <= _Value.y);
	}
	bool operator > (const KVec2& _Value) const
	{
		return (x > _Value.x && y > _Value.y);
	}
	bool operator < (const KVec2& _Value) const
	{
		return (x < _Value.x && y < _Value.y);
	}
/*
	operator __int64() const
	{
		return m_i64;
	}
*/

	float length() const
	{
		return sqrtf(x*x + y * y);
	}

	float distance() const
	{
		return sqrtf((x) * (x)+(y) * (y));
	}

	float distance(const KVec2& _Value) const
	{
		return sqrtf((x - _Value.x) * (x - _Value.x) + (y - _Value.y) * (y - _Value.y));
	}

	float dot(const KVec2& _Other) const
	{
		return x * _Other.x + y * _Other.y;
	}

	KVec2& y_reverse()
	{
		y *= -1.0f;
		return *this;
	}

	float x_ratio() const
	{
		if (0 > y)
		{
			return .0f;
		}

		return x / y;
	}
	float y_ratio() const
	{
		if (0 > x)
		{
			return .0f;
		}

		return y / x;
	}


};
typedef KVec2 KPoint;
typedef KVec2 KSize2;
typedef KVec2 KPos2;