/**
 * @file Tower.h
 * @brief Tornyok és kezelésük a tower defense játékban.
 *
 * Tartalmazza a Tower alaposztályt, különböző torony típusokat,
 * valamint a TowerManager osztályt.
 */
#ifndef TOWER_H
#define TOWER_H
#include "enemy.h"
#include "MyArray.h"
#include "vec2.h"
#include "graphics.h"
/**
* @class Tower
 * @brief Alaposztály minden torony típushoz.
 * A Tower osztály felelős a célzásért, támadásért
 */
class Tower
{
protected:
	Vec2<float> position; //Torony pozíciója világ koordinátákban
	float range; //Támadási hatótáv
	float damage; //Támadási sebzés
	float fireRate; //Támadási sebesség (másodpercenkénti támadás)
	float fireTimer; //Időzítő a következő támadásig
	float size; //Torony mérete
	int level; //Torony szintje
	const int maxLevel; //Maximális szint
	Enemy* currentTarget; //Aktuális célpont
	/**
	 * @brief Két pont közti távolság számítása
	 *
	 * @param v1 Első pont
	 * @param v2 Második pont
	 * @return A két pont közötti távolság
	 */
	float getDistance(const Vec2<float>& v1, const Vec2<float>& v2) const;
	/**
	 * @brief Célpont keresése az enemy listában
	 *
	 * A torony kiválaszt egy ellenséget a hatótávján belül.
	 *
	 * @param enemies Az aktív enemy-k listája
	 * @return A kiválasztott enemy pointere, vagy nullptr ha nincs cél
	 */
	Enemy* findtarget(MyArray<Enemy>& enemies) const;

public:
	/**
	 * @brief Konstruktor
	 *
	 * @param p Pozíció
	 * @param r Hatótáv
	 * @param d Sebzés
	 * @param fr Támadási sebesség
	 * @param ft Kezdő fire timer
	 * @param si Méret
	 */
	Tower(Vec2<float> p, float r, float d, float fr, float ft, float si);
	//Virtuális destruktor, öröklés miatt
	virtual ~Tower() {};
	//@return Az aktuális célpont pointere, vagy nullptr ha nincs cél
	Enemy* getCurrentTarget() const { return currentTarget; }
	//@return A torony hatótávja
	float getRange() const { return range; }
	//@return A torony mérete
	float getSize() const { return size; }
	//@return A torony sebzése
	float getDamage() const { return damage; }
	//@return A torony támadási sebessége
	float getFireRate() const { return fireRate; }
	//@return A torony szintje
	int getLevel() const { return level; }
	//@return A torony pozíciója világ koordinátákban
	Vec2<float> getPosition() const { return position; }
	
	 //@return A fejlesztés költsége a következő szintre
	int getUpgradeCost() const;	
	/**
	 * @brief Ellenőrzi, hogy fejleszthető-e
	 * @return true ha még nem érte el a max szintet
	 */
	bool canUpgrade() const { return level < maxLevel; }
	/**
	 * @brief Célpont törlése
	 */
	void resetTarget() { currentTarget = nullptr; }
	/**
	 * @brief Támadás végrehajtása
	 * Alap implementáció: közvetlen sebzés.
	 * @param enemy A célpont
	 */
	virtual void attack(Enemy* enemy) const { enemy->takeDamage(damage); }
	/**
	 * @brief Torony frissítése
	 * Kezeli a célkeresést, időzítést és támadást.
	 * @param dt Delta time
	 * @param enemies Aktív enemy-k
	 */
	void Update(float dt, MyArray<Enemy>& enemies);
	/**
	 * @brief Kirajzolás
	 * @param g Grafikai objektum
	 */
	virtual void draw(Graphics& g) const = 0;
	/**
	 * @brief Torony ára
	 * @return Vásárlási költség
	 */
	virtual int getCost() const = 0;
	/**
	 * @brief Eladási érték
	 * @return A torony eladásakor kapott pénz
	 */
	virtual int getSellValue() const;
	/**
	 * @brief Torony fejlesztése
	 */
	virtual void upgrade() = 0;
	/**
	 * @brief Klónozás
	 * @return Új Tower példány pointere
	 */
	virtual Tower* clone() const = 0;
	
};
/**
 * @class NormalTower
 * @brief Kiegyensúlyozott torony.
 */
class NormalTower : public Tower
{
public:
	NormalTower(Vec2<float> p): Tower(p, 400.0, 10.0, 1.0,0.0,150.0) {}
	void draw(Graphics& g) const;
	int getCost() const override { return 50; }
	void upgrade() override;
	NormalTower* clone() const override { return new NormalTower(*this); }
};
/**
 * @class FastTower
 * @brief Gyors, de alacsony sebzésű torony.
 */
class FastTower : public Tower
{
public:
	FastTower(Vec2<float> p): Tower(p, 300.0, 5.0, 0.5, 0.0, 150.0) {}
	void draw(Graphics& g) const;
	int getCost() const override { return 70; }
	void upgrade() override;
	FastTower* clone() const override { return new FastTower(*this); }
};
/**
 * @class SniperTower
 * @brief Nagy hatótávú, erős torony, de lassú.
 */
class SniperTower : public Tower
{
public:
	SniperTower(Vec2<float> p): Tower(p, 900.0, 20.0, 3.0, 0.0, 150.0) {}
	void draw(Graphics& g) const;
	int getCost() const override { return 90; }
	void upgrade() override;
	SniperTower* clone() const override { return new SniperTower(*this); }
};
/**
 * @class TowerManager
 * @brief Tornyok kezeléséért felelős osztály.
 * Kezeli a tornyok létrehozását, frissítését,
 * kirajzolását és eltávolítását.
 */
class TowerManager
{
	MyArray<Tower> towers; //Heterogén tömb a tornyok tárolására
	/**
	 * @brief Torony létrehozása típus alapján
	 * @param type Torony típusa
	 * @param pos Pozíció
	 * @return Új Tower pointer
	 */
	Tower* towerFactory(TowerType type, Vec2<float> pos) const;
public:
	TowerManager(): towers() {}
	/**
	 * @brief Értesítés enemy törléséről
	 * Ha egy torony célpontja törlődik, nullázni kell.
	 * @param enemy A törölt enemy
	 */
	void notifyEnemyRemoved(Enemy* enemy);
	/**
	 * @brief Torony hozzáadása
	 * @param type Torony típusa
	 * @param pos Pozíció
	 */
	void AddTower(TowerType type, Vec2<float> pos);
	/**
	 * @brief Tornyok frissítése
	 * @param dt Delta time
	 * @param enemies Enemy lista
	 */
	void Update(float dt, MyArray<Enemy>& enemies);
	/**
	 * @brief Tornyok kirajzolása
	 * @param g Grafikai objektum
	 */
	void Draw(Graphics& g) const;
	/**
	 * @brief Ár lekérése típus alapján
	 * @param type Torony típusa
	 * @return Ár
	 */
	int GetCostForType(TowerType type) const;
	/**
	 * @brief Torony lekérése pozíció alapján
	 * @param pos Keresett pozíció
	 * @param ts Tile méret (hitbox számításhoz)
	 * @return A torony pointere vagy nullptr
	 */
	Tower* GetTowerAt(const Vec2<float>& pos, int ts);
	/**
	 * @brief Torony eladása
	 * @param t A torony pointere
	 * @param pos Pozíció (eltávolításhoz)
	 * @return A visszakapott pénz
	 */
	int sellTower(Tower *t, Vec2<float>& pos);
};

#endif