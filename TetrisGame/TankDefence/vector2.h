#pragma once
#include <iosfwd>

class Vector2
{
public:
	float x;
	float y;
	static const Vector2 zeroPoint;
	static const Vector2 oneByOne;

	Vector2(float _x = 0, float _y = 0) :x(_x),y(_y){} // default para�� �⺻������ ���

	const Vector2 Normalize(float _x = 0, float _y = 0) const;	// normal vector ���ϴ� �Լ�(para : ���������� �Ϲ�ȭ)
	float Magnitude() const;	// ���� ũ�� ���ϴ� �Լ�(���� ��Į��)

	 // �� ���� �Ÿ� & ���� (��ü �ܺο��� ����ϱ� ���� static)
	static float DistTwoDot(const Vector2 &vec1, const Vector2 &vec2);
	static float DotProduct(const Vector2 &vec1, const Vector2 &vec2);

	// ������ �����ε�
	const Vector2 operator*(float scalar) const; // ex. vector2 * 2
	const Vector2 operator+(const Vector2 &vec); // ex. vec1 + vec2
	const Vector2 operator-(const Vector2 &vec); // ex. vec1 - vec2
	Vector2 & operator*=(float scalar);	// ex. vector2 *= 3
	Vector2 & operator+=(const Vector2 &vec);  // ex. vec1 += vec2
};

const Vector2 operator*(float scalar, const Vector2 & vec);
std::istream & operator>>(std::istream & is, Vector2 & vec);
