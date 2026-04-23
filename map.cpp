#include "map.h"
#include <iostream> 
#include <fstream>
#include "memtrace.h"

Map::Map() : height(0), width(0), tileSize(0), pathSize(0), Tiles(nullptr) {}

Map::Map(int width, int height, int tileSize) : width(width), height(height),
tileSize(tileSize), pathSize(0), Tiles(nullptr)
{
	allocateGrid();
}


void Map::cleanUp()
{
	if (Tiles != nullptr)
	{
		for (int i = 0; i < height; i++)
		{
			delete[] Tiles[i];
		}
		delete[] Tiles;
	}
	Tiles = nullptr;
}

void Map::loadDimensions(std::istream& is)
{
	is >> tileSize >> pathSize >> width >> height;
}
void Map::loadPathPoints(std::istream& is)
{
	PathPoints.clear();
	for (int i = 0; i < pathSize; i++)
	{
		int x, y;
		char comma;
		is >> x >> comma >> y;
		PathPoints.push_back({ x,y });
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
char Map::tileTypeToChar(TileType type) const
{
	switch (type)
	{
	case TileType::PATH: return 'P';
	case TileType::BUILDABLE: return 'B';
	case TileType::NOTBUILDABLE: return 'N';
	default: return 'N';
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
Vec2<float> Map::gridToWorld(Vec2<int> gridPos) const {
	float ts = static_cast<float>(this->tileSize);
	return { gridPos.x * ts + ts / 2.0f, gridPos.y * ts + ts / 2.0f };
}
void Map::load(std::istream& is)
{
	cleanUp();
	loadDimensions(is);
	loadPathPoints(is);
	allocateGrid();
	loadGrid(is);
}
Tile& Map::getTile(int y, int x) const
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
void Map::setTile(int y, int x, TileType type) {
	if (y < 0 || y >= height || x < 0 || x >= width) return;
	Tiles[y][x].setType(type);
}
EditorMap::EditorMap(int width, int height, int tileSize) : Map(width, height, tileSize) {}

void EditorMap::setTile(int y, int x, TileType type)
{
	if (y < 0 || y >= height || x < 0 || x >= width) return;
	if (getTile(y, x).getType() == TileType::PATH) return;
	if (type == TileType::PATH) {
		if (!CanPlacePath(y, x)) return; 

		PathPoints.push_back({ x, y });
		PathPlaced = true;
	}
	Map::setTile(y, x, type);
}

void EditorMap::undoLastPath()
{
	if(PathPoints.empty()) return;
	Vec2<int> last = PathPoints.back();
	PathPoints.pop_back();
	Map::setTile(last.y, last.x, TileType::NOTBUILDABLE);
	if (PathPoints.empty()) {
		PathPlaced = false;
	}
}

void EditorMap::save(const std::string& filename) const
{
	if(!canSave())
	{
		std::cerr << "Nem lehet elmenteni a pályát: túl kevés útpont van.\n";
		return;
	}
	std::ofstream file(filename);
	if (file.is_open())
	{
		saveDimensions(file);
		savePathPoints(file);
		saveGrid(file);
		file.close();
	}
}
void EditorMap::saveDimensions(std::ostream& os) const
{
	os << tileSize << "\n" << PathPoints.size() << "\n" << width << "\n" << height << "\n";
}
void EditorMap::savePathPoints(std::ostream& os) const
{
	for(size_t i=0;i<PathPoints.size(); i++)
	{
		os << PathPoints[i].x << "," << PathPoints[i].y<<" ";
	}
	os << "\n";
}
void EditorMap::saveGrid(std::ostream& os) const
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			os << tileTypeToChar(Tiles[y][x].getType());
		}
		os << "\n";
	}
}
bool EditorMap::CanPlacePath(int y, int x) const
{
	if (!PathPlaced) return true;
	int dy[] = { 0,0,1,-1 };
	int dx[] = { 1,-1,0,0 };
	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny >= 0 && ny < height && nx >= 0 && nx < width)
		{
			if(getTile(ny, nx).getType() == TileType::PATH)
			{
				return true;
			}
		}
	}
	return false;
}
bool EditorMap::canSave() const
{
	if (PathPoints.size() < 3) return false;
	return true;
}
void EditorMap::draw(Graphics& g) const
{
	Map::draw(g);
	g.drawGrid(width, height, static_cast<float>(tileSize));
	g.drawPathNumbers(PathPoints, static_cast<float>(tileSize));
}
