#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <vector>
#include "Enemy.h"
#include <SFML/Audio.hpp>

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.
class Enemy;

class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime,  vector<Enemy*>& enemies);
	void render();
	
	void setPhysicsTileMap(TileMap *tileMap);
	void setFrontMap(TileMap* tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition();

	bool beaten();
	int getLife();

	enum class Estado { FastWalking, SlowWalking, Jumping, Falling, Stopped, Climbing,
		Bend, Fighting, Atacking, AtackWalk, Drinking
	};

	enum PlayerAnims
	{
		FALLING_LEFT, FALLING_RIGHT, DEAD,
		STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_RIGHT, JUMP_LEFT, SLOW_RIGHT,
		SLOW_LEFT, CLINBING_LEFT, CLINBING_RIGHT, BEND_LEFT, BEND_RIGHT,
		ATACK_RIGHT, ATACK_LEFT, ATACK_WALK_RIGHT, ATACK_WALK_LEFT, ATACK_PAUSE_RIGHT,
		ATACK_PAUSE_LEFT, DRINK_RIGHT, DRINK_LEFT,
	};


private:
	bool bJumping, bMoving;
	glm::ivec2 tileMapDispl;
	glm::vec2 posPlayer, targetPosPlayer, direction;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *physicsMap;
	TileMap *frontMap;

	glm::ivec2 colisionBox;
	glm::ivec2 drawAdjustment;

	Estado estado;

	Enemy* target;

	int life;

	int waitAtack;
	int timeToBeReady;

	bool bAtacking;
	bool bBeaten;


	sf::Sound snd_danoEspada;
	sf::Sound snd_danoPropio;
	sf::Sound snd_golpeAire;
	sf::Sound snd_desenfundar;
	sf::Sound snd_beberVida;
};


#endif // _PLAYER_INCLUDE


