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
	void reload(const glm::ivec2& tileMapPos);
	void update(int deltaTime,  vector<Enemy*>& enemies);
	void render();
	
	void setPhysicsTileMap(TileMap *tileMap);
	void setFrontMap(TileMap* tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getPosition();


	bool beaten();
	int getLife();
	int getMaxLife();

	Enemy* getTarget();
	
	enum class Estado { 
		//WALKING
		Stopped,
		Turn,
		StartRun,
		Running,
		StopRun, 
		SlowWalking,
		JumpBig,

		// Stoped ACTIONS
		JumpVertical,
		JumpSmall,
		Falling, 
		Climbing,
		Bend, 
		
		//FIGHT
		Fighting, 
		Atacking, 
		AtackWalk, 
		
		//ACTIONS
		Drinking,
		SIZE
	};
	
	enum PlayerAnims
	{
		DEAD,
		FALLING_LEFT, FALLING_RIGHT, 
		STAND_LEFT, STAND_RIGHT,
		MOVE_LEFT, MOVE_RIGHT,
		JUMP_RIGHT, JUMP_LEFT, 
		SLOW_RIGHT, SLOW_LEFT,
		CLINBING_LEFT, CLINBING_RIGHT,
		BEND_LEFT, BEND_RIGHT,
		ATACK_RIGHT, ATACK_LEFT, 
		ATACK_WALK_RIGHT, ATACK_WALK_LEFT,
		ATACK_PAUSE_RIGHT, ATACK_PAUSE_LEFT,
		DRINK_RIGHT, DRINK_LEFT,
		JUMP_SMALL_LEFT, JUMP_SMALL_RIGHT, 
		JUMP_BIG_LEFT, JUMP_BIG_RIGHT,
		TURN_LEFT, TURN_RIGHT,
		RUNNING_LEFT, RUNNING_RIGHT
	};

	struct EstadoAnimacion {
		PlayerAnims left;
		PlayerAnims right;
	};

	EstadoAnimacion estadoAnimacion[Estado::SIZE];

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
	glm::vec2 defaultDrawAdjustment;
	glm::vec2 drawAdjustment;

	Estado estado;

	Enemy* target;

	int life;
	int maxLife;
	int damage;

	// Times
	int waitAtack;
	int timeToBeReady;
	int superTime;

	bool bAtacking;
	bool bBeaten;
	bool bSuper;


	sf::Sound snd_danoEspada;
	sf::Sound snd_danoPropio;
	sf::Sound snd_golpeAire;
	sf::Sound snd_desenfundar;
	sf::Sound snd_beberVida;

};


#endif // _PLAYER_INCLUDE


