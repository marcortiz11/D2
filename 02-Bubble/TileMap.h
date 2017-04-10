#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);
	~TileMap();

	void render() const;
	void free();
	
	float getTileSizeX() const { return tileSize.x; }
	float getTileSizeY() const { return tileSize.y; }

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &box) const;
	
	glm::ivec2 getTilePos(const glm::vec2& pixelPos);
	glm::vec2 getPixelPos(const glm::vec2& tilePos);

	int getIdTile(glm::ivec2 pos);
	void clearPath(glm::ivec2 pos);
	int* getTileMap() { return map; };

	int getMapSizeX() { return mapSize.x; };
	int getMapSizeY() { return mapSize.y; };

	void reload();

private:
	bool loadLevel(const string &levelFile);
	void prepareArrays();

private:
	string levelFile;
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	glm::fvec2 blockSize, tileSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	ShaderProgram &shaderProgram;
	int *map;

};


#endif // _TILE_MAP_INCLUDE


