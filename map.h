/**
* @file map.h
* @brief Pálya kezelését megvalósító osztályok deklarációja.
* Tartalmazza a Tile, Map és EditorMap osztályokat,
* amelyek a pálya kezeléséért, betöltéséért és szerkesztéséért felelõsek.
*/

#ifndef MAP_H
#define MAP_H
#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include "vec2.h"
#include "graphics.h"
#include "types.h"

/**
* @class Tile
* @brief A térkép egyetlen csempéjét reprezentáló osztály.
*/
class Tile {
	TileType type; //A csempe típusa (Path, buildable, not buildable)
public:
	/**
	* @brief Konstruktor, amely beállítja a csempe típusát.
	* @param t A csempe típusa. (Alapértelmezett::not buildable)
	*/
	Tile(TileType t = TileType::NOTBUILDABLE): type(t) {}
	/**
	* @brief Visszaadja a csempe típusát.
	* @return A csempe típusa.
	*/
	TileType getType() const { return type; }
	/**
	* @brief Beállítja a csempe típusát.
	* @param t A csempe típusa.
	*/
	void setType(TileType t) { type = t; }
};
/**
* @class Map
* @brief A játék pályáját reprezentáló osztály.
* Kezeli a négyzetrács alapú pályát, az útvonal pontokat,
* valamint a pálya betöltését és megjelenítését.
*/
class Map {
protected:
	int width, height; //Pálya méretei
	int tileSize, pathSize; //Csempe és útvonal méretei
	Tile** Tiles; //Dinamikus 2D tömb a csempék tárolására
	std::vector<Vec2<int>> PathPoints; //Az útvonal pontjainak listája
	//Memória felszabadítása
	void cleanUp();
	//Rács lefoglalása
	void allocateGrid();
	//Méretek betöltése streambõl
	void loadDimensions(std::istream& is);
	//Rács betöltése streambõl
	void loadGrid(std::istream& is);
	//Útvonal pontok betöltése streambõl
	void loadPathPoints(std::istream& is);
	/**
	 * @brief Karakter -> TileType konverzió
	 * @param c A karakter
	 * @return A megfelelõ TileType
	 */
	TileType charToTileType(const char c) const;
	/**
	 * @brief TileType -> karakter konverzió
	 * @param type A TileType
	 * @return A megfelelõ karakter
	 */
	char tileTypeToChar(TileType type) const;
	
public:
	//Alapértelmezett konstruktor
	Map();
	/**
	 * @brief Konstruktor méretekkel
	 * @param width Szélesség
	 * @param height Magasság
	 * @param tileSize Tile méret pixelben
	 */
	Map(int width, int height, int tileSize);
	//Destruktor
	~Map();
	/**
	 * @brief Pálya betöltése streambõl
	 * @param is Input stream
	 */
	void load(std::istream& is);
	/**
	 * @brief Tile lekérése
	 * @param y Sor index
	 * @param x Oszlop index
	 * @return Referencia a tile-ra
	 */
	Tile& getTile(int y, int x) const;
	// @return Tile méret
	int getTileSize() const { return tileSize; }
	// @return Útvonal hossza
	int getPathSize() const { return PathPoints.size(); }
	// @return Pálya magasság
	int getHeight() const { return height; }
	// @return Pálya szélesség
	int getWidth() const { return width; }
	// @return Az útvonal kezdõpontja
	Vec2<int> getSpawnPoint() const { return PathPoints[0]; }
	/**
	 * @brief Útvonal pont lekérése
	 * @param index Index
	 * @return A pont koordinátája
	 */
	Vec2<int> getPathPoint(int index) const { return PathPoints[index]; }
	/**
	 * @brief Megmondja, hogy lehet-e építeni adott helyre
	 * @param y Sor
	 * @param x Oszlop
	 * @return true ha építhetõ
	 */
	bool canBuild(int y, int x) const;
	/**
	 * @brief Rács koordináták -> világ koordináták konverzió
	 * @param gridPos Rács koordináták
	 * @return Világ koordináták
	 */
	Vec2<float> gridToWorld(Vec2<int> gridPos) const;
	/**
	 * @brief Pálya kirajzolása
	 * @param g Grafikai objektum
	 */
	virtual void draw(Graphics& g) const;
	/**
	 * @brief Tile módosítása
	 * @param y Sor
	 * @param x Oszlop
	 * @param type Új típus
	 */
	virtual void setTile(int y, int x, TileType type);
};
/**
 * @class EditorMap
 * @brief Pályaszerkesztõhöz használt Map.
 *
 * Lehetõvé teszi az útvonal szerkesztését,
 * visszavonást és pálya mentést.
 */
class EditorMap : public Map
{
	bool PathPlaced=false; //Jelzi, hogy már van-e útvonal
	void saveDimensions(std::ostream& os) const;
	void savePathPoints(std::ostream& os) const;
	void saveGrid(std::ostream& os) const;
	//Ellenõrzi, hogy menthetõ-e a pálya
	bool canSave() const;
	/**
	 * @brief Visszaadja a menthetõ pálya indexét
	 * @return A menthetõ pálya indexe
	 */
	int getSavableMapIndex() const;
	//Mentés levels.txt fájlba
	void saveToLevelsTxt() const;
public:
	/**
	 * @brief Konstruktor méretekkel
	 * @param width Szélesség
	 * @param height Magasság
	 * @param tileSize Tile méret pixelben
	 */
	EditorMap(int width, int height, int tileSize);
	/**
	 * @brief Ellenõrzi, hogy lerakható-e útvonal
	 * @param y Sor
	 * @param x Oszlop
	 * @return true ha lerakható
	 */
	bool CanPlacePath(int y, int x) const;
	/**
	 * @brief Tile módosítása
	 * @param y Sor
	 * @param x Oszlop
	 * @param type Új típus
	 */
	void setTile(int y, int x, TileType type) override;
	//Visszavonja az utolsó útvonal pontot
	void undoLastPath();
	//Menti a pályát a megfelelõ formátumban egy .txt fájlba
	void save() const;
	/**
	 * @brief Pálya kirajzolása
	 * @param g Grafikai objektum
	 */
	void draw(Graphics& g) const override;
};
#endif