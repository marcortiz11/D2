#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"


using namespace std;


TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	
	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program) :shaderProgram(program)
{
	loadLevel(levelFile);
	this->levelFile = levelFile;
	prepareArrays();
}

void TileMap::reload()
{
	loadLevel(levelFile);
}

TileMap::~TileMap()
{
	if(map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream ifs;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;
	
	ifs.open(levelFile.c_str());
	if(!ifs.is_open())
		return false;
	getline(ifs, line);
	if(line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(ifs, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(ifs, line);
	sstream.str(line);
	sstream >> tileSize.x >> tileSize.y >> blockSize.x >> blockSize.y;
	getline(ifs, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(ifs, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);

	int offset;
	getline(ifs, line);
	sstream.str(line);
	sstream >> offset;
	
	map = new int[mapSize.x * mapSize.y];
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			int idTile;
			ifs >> idTile;
			if (idTile != 0) {
				map[j*mapSize.x + i] = idTile - offset;
			}
			else {
				map[j*mapSize.x + i] = 0;
			}
		}
		ifs.get(tile);
#ifndef _WIN32
		ifs.get(tile);
#endif
	}
	ifs.close();
	
	return true;
}

void TileMap::prepareArrays()
{
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if(tile != 0)
			{
				// Non-empty tile
				nTiles++;

				posTile = glm::vec2(i * blockSize.x, j * blockSize.y);

				float cx = (tile-1) / tilesheetSize.x; //+1
				float cy = (tile-1) % tilesheetSize.x; //-1

				texCoordTile[0] = glm::vec2(cy / float(tilesheetSize.x), cx / float(tilesheetSize.y));
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				texCoordTile[1] -= halfTexel;

				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + 32.f); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + 32.f); vertices.push_back(posTile.y + 63.f);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);

				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + 32.f); vertices.push_back(posTile.y + 63.f);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + 63.f);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = shaderProgram.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = shaderProgram.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = pos.x / tileSize.x;
	y0 = pos.y / tileSize.y;
	y1 = (pos.y + size.y - 1) / tileSize.y;
	for(int y=y0; y<=y1; y++)
	{
		if(map[y*mapSize.x + x] == 1)
			return true;
	}
	
	return false;
}


void TileMap::clearPath(glm::ivec2 pos) {
	map[pos.y*mapSize.x + pos.x] = 0;
	prepareArrays(); //Carreguem un altre cop el mapa

}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = (pos.x + size.x - 1) / tileSize.x;
	y0 = pos.y / tileSize.y;
	y1 = (pos.y + size.y - 1) / tileSize.y;
	for(int y=y0; y<=y1; y++)
	{
		if(map[y*mapSize.x+x] == 1)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &box) const
{
	int x0, x1, y;
	
	x0 = pos.x / tileSize.x;
	x1 = (pos.x + box.x - 1) / tileSize.x;
	y = (pos.y + box.y - 1) / tileSize.y;
	for(int x=x0; x<=x1; x++)
	{
		if(map[y*mapSize.x+x] != 0)
		{
			if(pos.y - tileSize.y * y + box.y <= 4)
			{
				return true;
			}
		}
	}
	
	return false;
}


int TileMap::getIdTile(glm::ivec2 pos) {
	return map[pos.y*mapSize.x + pos.x];
}

glm::ivec2 TileMap::getTilePos(const glm::vec2& pixelPos) {
	glm::ivec2 result;

	result.x = pixelPos.x / tileSize.x;
	result.y = pixelPos.y / tileSize.y;

	return result;
}

glm::vec2 TileMap::getPixelPos(const glm::vec2& tilePos) {
	glm::vec2 result;
	
	result.x = tilePos.x * tileSize.x;
	result.y = tilePos.y * tileSize.y;

	return result;
}




























