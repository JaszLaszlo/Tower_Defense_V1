/**
 * @file Vec2.h
 * @brief 2D vektor template
 *
 * A Vec2 egy általános 2D vektor implementáció, amely
 * támogatja:
 * - koordináta tárolást
 * - típuskonverziót
 * - távolságszámítást
 * - grid <--> world konverziót
 */
#ifndef VEC2_H
#define VEC2_H

 /**
  * @struct Vec2
  * @brief 2D vektor generikus típussal.
  * @tparam T A koordináták típusa (int, float, stb.)
  */
template<typename T>
struct Vec2
{
	T x; //X koordináta
	T y; //Y koordináta
	/**
	 * @brief Konstruktor
	 * @param x X koordináta (alapértelmezett: 0)
	 * @param y Y koordináta (alapértelmezett: 0)
	 */
	Vec2(T x=0, T y=0): x(x), y(y) {}
	/**
	 * @brief Típuskonverziós operátor
	 * Lehetővé teszi Vec2<T> -> Vec2<U> konverziót.
	 * @tparam U Cél típus
	 * @return Átkonvertált vektor
	 */
	template<typename U>
	operator Vec2<U>() const
	{
		return Vec2<U>(static_cast<U>(x), static_cast<U>(y));
	}
	/**
	 * @brief Két vektor közötti távolság
	 * @param other Másik vektor
	 * @return Távolság float értékben
	 */
	float getDistance(const Vec2<T>& other) const {
		T dx = x - other.x;
		T dy = y - other.y;
		return std::sqrt(static_cast<float>(dx * dx + dy * dy));
	}
	/**
	 * @brief World koordináta -> Grid koordináta
	 * Átalakítja a világpozíciót rács alapú indexelésre.
	 * @param worldPos Világ koordináta
	 * @param tileSize Egy cella mérete
	 * @return Grid koordináta (int)
	 */
	static Vec2<int> worldToGrid(const Vec2<float>& worldPos, int tileSize) {
		return Vec2<int>(
			static_cast<int>(worldPos.x / tileSize),
			static_cast<int>(worldPos.y / tileSize)
		);
	}
	/**
	 * @brief Grid koordináta -> World koordináta
	 * A grid cella középpontját számítja ki világ koordinátában.
	 * @param gridPos Grid pozíció
	 * @param tileSize Cella mérete
	 * @return World koordináta (float)
	 */
	static Vec2<float> gridToWorld(const Vec2<int>& gridPos, int tileSize) {
		return Vec2<float>(
			(static_cast<float>(gridPos.x) * tileSize) + (tileSize / 2.0f),
			(static_cast<float>(gridPos.y) * tileSize) + (tileSize / 2.0f)
		);
	}
	/**
	 * @brief Egyenlőség összehasonlítás
	 * @param other Másik vektor
	 * @return true ha x és y megegyezik
	 */
	bool operator==(const Vec2<T>& other) const {
		return (x == other.x && y == other.y);
	}
};

#endif
