#ifndef _Guillotina_INCLUDE
#define _Guillotina_INCLUDE


#include "Sprite.h"
#include "ActivationButton.h"
#include "TileMap.h"
#include "Player.h"
#include <SFML/Audio.hpp>


class Guillotina
{

public:
	void init(const glm::vec2 &tileMapPos, TileMap *map, ShaderProgram &shaderProgram);
	void update(int deltaTime, Player *p);
	void render();

private:
	glm::ivec2 tileMapDispl;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

	glm::vec2 tileMapPos;
};


#endif // _Guillotina_INCLUDE


