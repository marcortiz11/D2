#ifndef _Gate_INCLUDE
#define _Gate_INCLUDE


#include "Sprite.h"
#include "ActivationButton.h"
#include "TileMap.h"
#include <SFML/Audio.hpp>


class Gate
{

public:
	void init(ActivationButton *b, string textureName, const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime, TileMap* physics);
	void render();

private:
	glm::ivec2 tileMapDispl;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *physicsMap;
	ActivationButton *b;
	int TILEX, TILEY;
	int state = 2;

	glm::ivec2 tileMapPos;

	sf::Sound snd_puerta;
};


#endif // _Gate_INCLUDE


