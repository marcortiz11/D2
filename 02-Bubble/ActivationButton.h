#pragma once
#ifndef _ActivationButton_INCLUDE
#define _ActivationButton_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include <SFML/Audio.hpp>

class ActivationButton
{

public:
	void init(TileMap* map,string textureName, const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
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

	sf::Sound snd_boton;
};


#endif // _ActivationButton_INCLUDE