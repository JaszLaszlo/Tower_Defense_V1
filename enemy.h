/**
 * @file Enemy.h
 * @brief Ellenségek és kezelésük a tower defense játékban.
 *
 * Tartalmazza az Enemy alaposztályt, annak leszármazottait,
 * valamint az EnemyManager osztályt, amely az ellenségek kezeléséért felel.
 */
#ifndef ENEMY_H
#define ENEMY_H
#include "map.h"
#include "MyArray.h"
#include "vec2.h"
#include "graphics.h"
#include "types.h"
#include <iostream> 

/**
* @class Enemy
* @brief Az ellenségek alapvető viselkedését és tulajdonságait meghatározó alaposztály.
* 
* Az Enemy osztály kezeli a mozgást az útvonal mentén,
* az életerőt, a sebességet és az alap viselkedést
*/
class Enemy
{
protected:
	Vec2<float> position; //Aktuális pozíció világkoordinátákban
	float offset; //Oldalirányú eltolás a mozgás során, hogy ne egy vonalban haladjanak
	float hp; //Aktuális életerő
	float maxHp; //Maximális életerő
	float speed; //Mozgási sebesség
	float size; //Méret
	int currentPathIndex; //Jelenlegi célpont index a path-ban
	/**
	* @brief Normalizált irányvektor számítása két pont között
	*
	* @param from Kiindulási pont (rács koordináta)
	* @param to Célpont (rács koordináta)
	* @return Irányvektor a from → to irányba
	*/
	Vec2<float> calculateNormalizedDir(const Vec2<int>& from, const Vec2<int>& to) const;
	/**
	* @brief Egy vektor merőlegesének meghatározása
	*
	* @param dir Bemeneti irányvektor
	* @return A dir vektorra merőleges vektor (90 fokkal elforgatva)
	*/
	Vec2<float> getPerpendicular(const Vec2<float>& dir) const;
	/**
	* @brief Kanyarodási célpont számítása
	*
	*
	* @param map A pálya objektum
	* @param pathIndex Az aktuális útvonal pont indexe
	* @param tileSize Egy tile mérete (pixelben)
	* @return A kanyarodáshoz használt célpont világ koordinátában
	*/
	Vec2<float> calculateCornerPoint(const Map& map, int pathIndex, float tileSize) const;
	/**
	* @brief Egyenes szakasz célpont számítása
	*
	* Meghatározza a következő célpontot egyenes haladás esetén.
	*
	* @param map A pálya objektum
	* @param pathIndex Az aktuális útvonal pont indexe
	* @param tileSize Egy tile mérete
	* @return A célpont világ koordinátában
	*/
	Vec2<float> calculateStraightTarget(const Map& map, int pathIndex, float tileSize) const;
	/**
	* @brief Spawnbeli offset kezelés
	*
	* Szétoszlatja az egymásra spawnoló enemy-ket úgy,
	* hogy oldalirányú eltolást alkalmaz az útvonal mentén.
	*
	* @param map A pálya, amely tartalmazza az útvonalat
	*/
	void handleOffsetAtSpawn(const Map& map);
	/**
	* @brief Offsetelt célpont lekérése
	*
	* Az alap path pontot módosítja az enemy offset értékével,
	* hogy ne egy vonalon haladjanak.
	*
	* @param map A pálya objektum
	* @param pathIndex Az aktuális útvonal pont indexe
	* @return Az offsetelt célpont világ koordinátában
	*/
	Vec2<float> getOffsetTarget(const Map& map, int pathIndex) const;
	/**
	* @brief Mozgás alkalmazása a célpont felé
	*
	* Frissíti az enemy pozícióját a célpont irányába
	*
	* @param target A cél pozíció
	* @param moveStep Egy frame alatt maximálisan megtehető távolság
	* @param distance A jelenlegi távolság a célponttól
	*/
	void applyMovement(const Vec2<float>& target, float moveStep, float distance);
	
public:
	/**
	 * @brief Konstruktor
	 *
	 * @param p Kezdő pozíció
	 * @param h Életerő
	 * @param sp Sebesség
	 * @param si Méret
	 * @param map A pálya (útvonalhoz)
	 * @param multiplier Nehézségi szorzó
	 */
	Enemy(Vec2<float> p, float h, float sp, float si, const Map& map, float multiplier);
	//virtuális destruktor, öröklés miatt
	virtual ~Enemy();
	/**
	* @brief Lekéri az enemy aktuális pozícióját
	* @return Az enemy pozíciója világ koordinátában
	*/
	Vec2<float> getPosition() const { return position; }
	/**
	* @brief Lekéri az enemy méretét
	* @return Az enemy mérete
	*/
	float getSize() const { return size; }
	/**
	* @brief Mozgatás az útvonal mentén
	*
	* Az enemy a következő célpont felé halad a sebességének megfelelően.
	*
	* @param map A pálya (útvonal információkhoz)
	* @param dt Delta time (eltelt idő másodpercben)
	*/
	void Move(const Map& map, float dt);
	/**
	* @brief Ellenőrzi, hogy az enemy elérte-e a pálya végét
	*
	* @param map A pálya objektum
	* @return true ha elérte a célt, különben false
	*/
	bool hasReachedEnd(const Map& map) const;
	/**
	* @brief Ellenőrzi, hogy az enemy életben van-e
	* @return true ha hp > 0, különben false
	*/
	bool isAlive() const;
	/**
	* @brief Sebzés alkalmazása az enemy-re
	* @param amount A sebzés mértéke
	*/
	void takeDamage(float amount) { hp -= amount; }
	/**
	* @brief Kirajzolja az enemy-t
	* A konkrét megjelenítést a leszármazott osztályok valósítják meg.
	* @param g Grafikai objektum
	*/
	virtual void draw(Graphics& g) const = 0;
	/**
	* @brief Az enemy megöléséért járó jutalom
	* @return A játékos által kapott pénz/érték
	*/
	virtual int getReward() const = 0;
	/**
	* @brief Klónozza az enemy-t
	 * Új példányt hoz létre ugyanazzal az állapottal.
	* @return Új Enemy példány pointere
	*/
	virtual Enemy* clone() const = 0;

};
/**
 * @class FastEnemy
 * @brief Gyors, de gyenge ellenség.
 */
class FastEnemy : public Enemy
{
public:
	FastEnemy(Vec2<float> p, const Map& map, float mult) 
		: Enemy(p, 15.0f,130.0f,55.0f, map, mult) {}
	void draw(Graphics& g) const;
	int getReward() const override { return 6; }
	FastEnemy* clone() const override { return new FastEnemy(*this); }
};
/**
 * @class NormalEnemy
 * @brief Kiegyensúlyozott ellenség.
 */
class NormalEnemy : public Enemy
{
public:
	NormalEnemy(Vec2<float> p, const Map& map, float mult) : 
		Enemy(p, 30.0f, 60.0f, 30.0f, map, mult) {}
	void draw(Graphics& g) const;
	int getReward() const override { return 3; }
	NormalEnemy* clone() const override { return new NormalEnemy(*this); }
};
/**
 * @class TankEnemy
 * @brief Lassú, de nagyon erős ellenség.
 */
class TankEnemy : public Enemy
{
public:
	TankEnemy(Vec2<float> p, const Map& map, float mult)
		: Enemy(p, 120.0f, 35.0f, 30.0f, map, mult) {}
	void draw(Graphics& g) const;
	int getReward() const override { return 9; }
	TankEnemy* clone() const override { return new TankEnemy(*this); }
};
/**
 * @class EnemyManager
 * @brief Az összes ellenség kezeléséért felel.
 * Spawnolás, frissítés, törlés és kirajzolás.
 */
class EnemyManager
{
	MyArray<Enemy> Enemies; //Heterogén tömb az ellenségek tárolására
	/**
	* @brief Enemy példány létrehozása típus alapján
	* @param type Az enemy típusa
	* @param pos Spawn pozíció
	* @param map A pálya
	* @param mult Nehézségi szorzó
	* @return Új Enemy példány pointere
	*/
	Enemy* enemyFactory(EnemyType type, Vec2<float> pos, const Map& map, float mult) const;
public:
	EnemyManager() : Enemies() {}
	/**
	* @brief Az összes enemy frissítése
	* Mozgatja az enemyket.
	* @param map A pálya
	* @param dt Delta time
	*/
	void Update(const Map& map,float dt);
	/**
	* @brief Új enemy spawnolása
	* @param type Az enemy típusa
	* @param map A pálya
	* @param wave Aktuális hullám száma (nehézség skálázás)
	*/
	void spawnEnemy(EnemyType type, const Map& map, int wave);
	/**
	* @brief Enemy lista lekérése
	* @return Az enemy-ket tartalmazó tömb referenciája
	*/
	MyArray<Enemy>& getEnemies() { return Enemies; }
	/**
	* @brief Összes enemy kirajzolása
	* @param g Grafikai objektum
	*/
	void Draw(Graphics& g) const;
	/**
	* @brief Ellenőrzi, hogy van-e aktív enemy
	* @return true ha nincs enemy, különben false
	*/
	bool isEmpty() const { return Enemies.size() == 0; }
};

#endif