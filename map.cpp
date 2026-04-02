#include "map.h"
#include <iostream> 
#include <fstream>
#include "memtrace.h"

Map::Map() : height(0), width(0), pathSize(0), tileSize(0), Tiles(nullptr), PathPoints(nullptr){}

void Map::copyFrom(const Map& map)
{
	this->width = map.width;
	this->height = map.height;
	this->pathSize = map.pathSize;
	this->tileSize = map.tileSize;
	if (map.PathPoints != nullptr)
	{
		this->PathPoints = new Vec2<int>[pathSize];
		for (int i = 0; i < pathSize; i++) {
			this->PathPoints[i] = map.PathPoints[i];
		}
	}
	if (map.Tiles != nullptr) {
		this->Tiles = new Tile * [height];
		for (int i = 0; i < height; i++) {
			this->Tiles[i] = new Tile[width];
			for (int j = 0; j < width; j++) {
				this->Tiles[i][j] = map.Tiles[i][j];
			}
		}
	}
}

void Map::cleanUp()
{
	delete[] PathPoints;
	if (Tiles != nullptr)
	{
		for (int i = 0; i < height; i++)
		{
			delete[] Tiles[i];
		}
		delete[] Tiles;
	}
	Tiles = nullptr;
	PathPoints = nullptr;
}

void Map::loadDimensions(std::istream& is)
{
	is >> tileSize >> pathSize >> width >> height;
}
void Map::loadPathPoints(std::istream& is)
{
	PathPoints = new Vec2<int>[pathSize];
	for (int i = 0; i < pathSize; i++)
	{
		char comma;
		is >> PathPoints[i].x >> comma >> PathPoints[i].y;
	}
}
TileType Map::charToTileType(const char c) const
{
	switch (c)
	{
	case 'P': return TileType(TileType::PATH);
	case 'B': return TileType(TileType::BUILDABLE);
	case 'N': return TileType(TileType::NOTBUILDABLE);
	default: return TileType(TileType::NOTBUILDABLE);
	}
}
void Map::allocateGrid()
{
	Tiles = new Tile * [height];
	for (int i = 0; i < height; i++)
	{
		Tiles[i] = new Tile[width];
	}
}
void Map::loadGrid(std::istream& is)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			char c;
			is >> c;
			Tiles[i][j] = charToTileType(c);
		}
	}
}
void Map::load(std::istream& is)
{
	cleanUp();
	loadDimensions(is);
	loadPathPoints(is);
	allocateGrid();
	loadGrid(is);
}
Tile& Map::getTile(int y, int x)
{
	if (y < 0 || y >= height || x < 0 || x >= width) {
		throw std::out_of_range("A koordinata a palyan kivulre esik!");
	}
	return Tiles[y][x];
}
bool Map::canBuild(int y, int x) const
{ 
	return Tiles[y][x].getType() == TileType::BUILDABLE;
}
Map::Map(const Map& map) : Tiles(nullptr), PathPoints(nullptr)
{
	copyFrom(map);
}
Map& Map::operator=(const Map& other)
{
	if (this != &other) 
	{
		cleanUp();           
		copyFrom(other);     
	}
	return *this;            
}
void Map::draw(Graphics&g) const
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Vec2<float> pos(static_cast<float>(x * tileSize), static_cast<float>(y * tileSize));
			TileType type = Tiles[y][x].getType();
			g.drawTile(pos, type, static_cast<float>(tileSize));
		}
	}
}
Map::~Map()
{
	cleanUp();
}