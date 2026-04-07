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
	static Vec2<int> worldToGrid(const Vec2<float>& worldPos, int tileSize) {
		return Vec2<int>(
			static_cast<int>(worldPos.x / tileSize),
			static_cast<int>(worldPos.y / tileSize)
		);
	}
	static Vec2<float> gridToWorld(const Vec2<int>& gridPos, int tileSize) {
		return Vec2<float>(
			(static_cast<float>(gridPos.x) * tileSize) + (tileSize / 2),
			(static_cast<float>(gridPos.y) * tileSize) + (tileSize / 2)
		);
	}
	bool operator==(const Vec2<T>& other) const {
		return (x == other.x && y == other.y);
	}
};

#endif
