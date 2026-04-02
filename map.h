#pragma once
#include <iostream> 
#include <fstream>
#include "vec2.h"
#include "graphics.h"


class Tile {
	TileType type;
public:
	Tile(TileType t = TileType::NOTBUILDABLE): type(t) {}
	TileType getType() const { return type; }
	TileType setType(TileType t) { type = t; }
};
class Map {
	int width, height, pathSize, tileSize;
	Tile** Tiles;
	Vec2<int>* PathPoints;
	void cleanUp();
	void allocateGrid();
	void loadDimensions(std::istream& is);
	void loadGrid(std::istream& is);
	void loadPathPoints(std::istream& is);
	TileType charToTileType(const char c) const;
	void copyFrom(const Map& map);
	
public:
	Map();
	~Map();
	Map(const Map& map);
	Map& operator=(const Map& map);
	void load(std::istream& is);
	Tile& getTile(int y, int x);
	int getTileSize() const { return tileSize; }
	int getPathSize() const { return pathSize; }
	int getHeight() const { return height; }
	int getWidth() const { return width; }
	Vec2<int> getSpawnPoint() const { return PathPoints[0]; }
	Vec2<int> getPathPoint(int index) const { return PathPoints[index]; }
	bool canBuild(int y, int x) const;
	void draw(Graphics& g) const;
	
};