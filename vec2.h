#ifndef VEC2_H
#define VEC2_H

template<typename T>
struct Vec2
{
	T x;
	T y;
	Vec2(T x=0, T y=0): x(x), y(y) {}
	template<typename U>
	operator Vec2<U>() const
	{
		return Vec2<U>(static_cast<U>(x), static_cast<U>(y));
	}
	float getDistance(const Vec2<T>& other) const {
		T dx = x - other.x;
		T dy = y - other.y;
		return std::sqrt(static_cast<float>(dx * dx + dy * dy));
	}
};

#endif
