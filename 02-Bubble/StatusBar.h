#pragma once
#include "Sprite.h"
#include "TileMap.h"
#include "Text.h"

class StatusBar
{
public:
	StatusBar();
	~StatusBar();

	enum Live
	{
		THREE_LIVES, TWO_LIVES, ONE_LIVE, DEAD
	};


public:
	void init(const glm::ivec2 &pos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setPosition(glm::vec2 pos);

	void setLife(Live live);

private:
	glm::ivec2 tileMapDispl;
	//glm::vec2 posTorch, targetPosTorch, direction;
	Texture spritesheet;
	Sprite *sprite;
	Text text;

	int elapsedTime;
};

