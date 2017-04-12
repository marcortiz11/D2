#pragma once
#include "Sprite.h"
#include "TileMap.h"
#include "Text.h"
#include "Player.h"
#include "Enemy.h"
#include <SFML/Audio.hpp>

class StatusBar
{
public:
	StatusBar();
	~StatusBar();

	enum Live
	{
		THREE_LIVES, TWO_LIVES, ONE_LIVE, DEAD
	};
	enum LiveAnimation
	{
		LIVE_FILLED, LIVE_EMPTY
	};

public:
	void init(const glm::ivec2 &pos, ShaderProgram &shaderProgram);
	void reload();
	void update(int deltaTime);
	void render();

	void setPosition(glm::vec2 pos);
	void setPlayer(Player* player);
	void setDead(bool b);
	bool timeout();

private:
	glm::ivec2 tileMapDispl;
	glm::vec2 position;
	//glm::vec2 posTorch, targetPosTorch, direction;
	Texture spritesheet;
	Texture liveSpritesheet;
	Texture liveEnemigoSpritesheet;
	Sprite *sprite;
	Sprite *spriteVida;
	Sprite *spriteVidaEnemigo;
	Text text;

	Player* player;

	int elapsedTime;
	bool bDead;

};

