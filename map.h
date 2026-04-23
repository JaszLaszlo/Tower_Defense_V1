#pragma once
#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include "vec2.h"
#include "graphics.h"
#include "types.h"


class Tile {
	TileType type;
public:
	Tile(TileType t = TileType::NOTBUILDABLE): type(t) {}
	TileType getType() const { return type; }
	void setType(TileType t) { type = t; }
};
class Map {
protected:
	int width, height, tileSize, pathSize;
	Tile** Tiles;
	std::vector<Vec2<int>> PathPoints;
	void cleanUp();
	void allocateGrid();
	void loadDimensions(std::istream& is);
	void loadGrid(std::istream& is);
	void loadPathPoints(std::istream& is);
	TileType charToTileType(const char c) const;
	char tileTypeToChar(TileType type) const;
	
public:
	Map();
	Map(int width, int height, int tileSize);
	~Map();
	void load(std::istream& is);
	Tile& getTile(int y, int x) const;
	int getTileSize() const { return tileSize; }
	int getPathSize() const { return PathPoints.size(); }
	int getHeight() const { return height; }
	int getWidth() const { return width; }
	Vec2<int> getSpawnPoint() const { return PathPoints[0]; }
	Vec2<int> getPathPoint(int index) const { return PathPoints[index]; }
	bool canBuild(int y, int x) const;
	Vec2<float> gridToWorld(Vec2<int> gridPos) const;
	virtual void draw(Graphics& g) const;
	virtual void setTile(int y, int x, TileType type);
};

struct PathChange {
	int x, y;
	TileType oldType;
};

class EditorMap : public Map
{
	bool PathPlaced=false;
	void saveDimensions(std::ostream& os) const;
	void savePathPoints(std::ostream& os) const;
	void saveGrid(std::ostream& os) const;
	bool canSave() const;
public:
	EditorMap(int width, int height, int tileSize);
	bool CanPlacePath(int y, int x) const;
	void setTile(int y, int x, TileType type) override;
	void undoLastPath();
	void save(const std::string& filename) const;
	void draw(Graphics& g) const override;
};