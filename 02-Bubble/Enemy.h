#pragma once
#include "Sprite.h"
#include "TileMap.h"

class Enemy
{
public:
	enum Type {
		EMagenta, ECyan
	};

	enum PlayerAnims
	{
		STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_RIGHT, JUMP_LEFT, SLOW_RIGHT, SLOW_LEFT, CLINBING_LEFT, CLINBING_RIGHT, BEND_LEFT, BEND_RIGHT
	};

	enum class Estado { FastWalking, SlowWalking, Jumping, Falling, Stopped, Climbing, Bend };

public:
	void init(Type type, const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime, glm::vec2 positionPlayer);
	void render();

	void setPhysicsTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition();

private:
	bool bJumping, bMoving;
	glm::ivec2 tileMapDispl;
	glm::vec2 posEnemy, targetPosEnemy, direction;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *physicsMap;

	glm::ivec2 colisionBox;
	glm::ivec2 drawAdjustment;

	Estado estado;
};

