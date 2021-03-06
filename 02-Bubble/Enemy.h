#pragma once
#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include "SFML/Audio.hpp"

class Player;

class Enemy
{
public:
	enum Type {
		EMagenta, ECyan
	};

	enum PlayerAnims
	{
		FALLING_LEFT, FALLING_RIGHT, DEAD,
		STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_RIGHT, JUMP_LEFT, 
		SLOW_RIGHT, SLOW_LEFT, CLINBING_LEFT, CLINBING_RIGHT, BEND_LEFT, BEND_RIGHT,
		ATACK_RIGHT, ATACK_LEFT, ATACK_WALK_RIGHT, ATACK_WALK_LEFT, ATACK_PAUSE_RIGHT,
		ATACK_PAUSE_LEFT
	};

	enum class Estado { FastWalking, SlowWalking, Jumping, Falling, Stopped, Climbing,
		Bend, Fighting, Atacking };

public:
	void init(Type type, const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void reload(const glm::ivec2& tileMapPos);
	void update(int deltaTime, Player& player);
	void render();

	void setPhysicsTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition() const;

	bool beaten(int damage);
	int getLife();
	int getMaxLife();

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

	int life;
	int maxLife;

	int waitAtack;
	int timeToBeReady;
	bool bAtacking;
	bool bBeaten;
};

