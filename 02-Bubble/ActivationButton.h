#pragma once
#ifndef _ActivationButton_INCLUDE
#define _ActivationButton_INCLUDE

#include "Sprite.h"
#include "TileMap.h"


class ActivationButton
{

public:
	void init(TileMap* map, const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime, const glm::ivec2 &playerPos);
	void render();
	int isPushed() { return state; };

private:
	glm::ivec2 tileMapDispl;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int TILEX, TILEY;
	int state = 0;
};


#endif // _ActivationButton_INCLUDE