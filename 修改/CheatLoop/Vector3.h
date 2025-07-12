#pragma once
#pragma once

#define M_PI 3.14159265358979323846264338327950288419716939937510f
#include <cmath>
struct MyFQuat;
class Vector3;

//弧度转角度
inline float ToDegree(float radian) {
	return radian * 180.f / M_PI;
}

//角度转弧度
inline float ToRadian(float degree) {
	return degree * M_PI / 180.0f;
}

class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f) { }

	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }

	float x;
	float y;
	float z;

	inline float Dot(Vector3 v) {
		return x * v.x + y * v.y + z * v.z;
	}

	//将欧拉角转换为四元数 x = pitch, y = yaw, z = roll

	Vector3 operator+(Vector3 v) {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3 v) {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(float number) const {
		return Vector3(x * number, y * number, z * number);
	}
};

struct MyFQuat
{
	float x;
	float y;
	float z;
	float w;

	//将四元数转换为欧拉角
	Vector3 ToEulerAngles();
};

inline Vector3 MyFQuat::ToEulerAngles()
{
	Vector3 e;

	e.x = asin(2 * (z * x - y * w));							//pitch
	e.y = atan2(2 * (x * y + z * w), 1 - 2 * (y * y + z * z));	//yaw
	e.z = atan2(2 * (z * y + x * w), 1 - 2 * (y * y + x * x));	//roll

	e.x = ToDegree(e.x);
	e.y = ToDegree(e.y);
	e.z = ToDegree(e.z);
	return e;
}

inline float CalcDistance(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrt(dx * dx + dy * dy);
}

inline float CalcDistance(Vector3 v1, Vector3 v2)
{
	float dx = v1.x - v2.x;
	float dy = v1.y - v2.y;
	float dz = v1.z - v2.z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

//两个角度相加
inline float AnglesAdd(float a1, float a2) {
	float angle = a1 + a2;

	//确保角度在 -180 到 180 之间
	while (angle <= -180.0) {
		angle += 360.0;
	}
	while (angle > 180.0) {
		angle -= 360.0;
	}
	return angle;
}
