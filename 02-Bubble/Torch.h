#ifndef _Torch_INCLUDE
#define _Torch_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class Torch
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

private:
	glm::ivec2 tileMapDispl;
	//glm::vec2 posTorch, targetPosTorch, direction;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *physicsMap;

};


#endif // _Torch_INCLUDE


