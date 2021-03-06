#ifndef _MYMATH_H_
#define _MYMATH_H_

// 수학적인 요소들이 들어있는 소스
#include<cmath>

// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const float M_PI = 3.141592653f;
// namespace 개념을 공부해서 이 및에 부분들을 namespace로 뺄것
class Vector2f
{
public:
	Vector2f();
	Vector2f(const float& x, const float& y);
	Vector2f(Vector2f& vec);
	Vector2f& operator=(Vector2f& vec);
	~Vector2f();

	const float& GetX();
	const float& GetY();

	void SetX(const float& x);
	void SetY(const float& y);
	void SetVector2f(Vector2f& vec);
	void SetVector2f(const float& x, const float& y);

	friend const float& CrossProduct(const float& a, const float& b, const float& c);
	friend const float& CrossProduct(const Vector2f& a, const Vector2f& b);

private:
	float m_x;
	float m_y;
};

class Vector3f
{
public:
	Vector3f();
	Vector3f(const float& x, const float& y, const float& z);
	Vector3f(Vector3f&);
	~Vector3f();

	void SetVector3f(Vector3f& vec);
	void SetVector3f(const float& x, const float& y, const float& z);

	// 내적
	const float& DotProduct(const Vector3f& a);
	// 외적
	const Vector3f& CrossProduct(const Vector3f& a);
	// 거리
	//const float& GetDistance(const Vector3f& a);
	// 정규화
	const Vector3f& Normalize();
	// 크기
	const float& GetLength();

	// 각 요소끼리 합하는 것
	friend const Vector3f& operator+(const Vector3f& a, const Vector3f& b);
	// 각 요소끼리 곱하는 것
	friend Vector3f& operator*(const Vector3f& a, const Vector3f& b);
	// 상수와 벡터 곱
	friend const Vector3f& operator*(const float& a, const Vector3f& b);
	friend const Vector3f& operator*(const Vector3f& a, const float& b);

	friend const float& GetDistance(const Vector3f& a, const Vector3f& b);

	float m_x;
	float m_y;
	float m_z;
};


// TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 쿼터니언을 공부해서 4차원 벡터와 좌표계를 사용할것
class Vector4f
{

};

#endif