#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include "GL/glut.h"

#define JUMP_ANGLE_STEP 6
#define JUMP_HEIGHT 96
#define FALL_STEP 7

void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	estado = Estado::Falling;
	spritesheet.loadFromFile("images/prince-sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	double widthAnim = 1.0 / 16.0;
	double heightAnim = 1.0 / 32.0;
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(widthAnim, heightAnim), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(29);

	sprite->setAnimationSpeed(FALLING_LEFT, 1);
	sprite->addKeyframe(FALLING_LEFT, glm::vec2(1 * widthAnim, 1 * heightAnim));

	sprite->setAnimationSpeed(FALLING_RIGHT, 1);
	sprite->addKeyframe(FALLING_RIGHT, glm::vec2(1 * widthAnim, 0 * heightAnim));

	sprite->setAnimationSpeed(DEAD, 1);
	sprite->addKeyframe(DEAD, glm::vec2(2 * widthAnim, 0 * heightAnim));

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 1 * heightAnim));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0 * heightAnim));


	sprite->setAnimationSpeed(MOVE_LEFT, 10);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0 * widthAnim, 3 * heightAnim));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(1 * widthAnim, 3 * heightAnim));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2 * widthAnim, 3 * heightAnim));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(3 * widthAnim, 3 * heightAnim));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(4 * widthAnim, 3 * heightAnim));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(5 * widthAnim, 3 * heightAnim));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(6 * widthAnim, 3 * heightAnim));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(7 * widthAnim, 3 * heightAnim));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(8 * widthAnim, 3 * heightAnim));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(9 * widthAnim, 3 * heightAnim));

	sprite->setAnimationSpeed(MOVE_RIGHT, 10);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0 * widthAnim, 2 * heightAnim));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1 * widthAnim, 2 * heightAnim));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2 * widthAnim, 2 * heightAnim));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3 * widthAnim, 2 * heightAnim));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4 * widthAnim, 2 * heightAnim));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(5 * widthAnim, 2 * heightAnim));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(6 * widthAnim, 2 * heightAnim));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(7 * widthAnim, 2 * heightAnim));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(8 * widthAnim, 2 * heightAnim));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(9 * widthAnim, 2 * heightAnim));

	sprite->setAnimationSpeed(JUMP_RIGHT, 12);
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(1 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(2 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(3 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(4 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(5 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(6 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(7 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(8 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(9 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(10 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(11 * widthAnim, 4 * heightAnim));

	sprite->setAnimationSpeed(JUMP_LEFT, 12);
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(1 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(2 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(3 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(4 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(5 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(6 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(7 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(8 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(9 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(10 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(11 * widthAnim, 5 * heightAnim));

	sprite->setAnimationSpeed(SLOW_RIGHT, 6);
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(0 * widthAnim, 6 * heightAnim));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(1 * widthAnim, 6 * heightAnim));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(2 * widthAnim, 6 * heightAnim));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(3 * widthAnim, 6 * heightAnim));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(4 * widthAnim, 6 * heightAnim));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(5 * widthAnim, 6 * heightAnim));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(6 * widthAnim, 6 * heightAnim));
	sprite->addKeyframe(SLOW_RIGHT, glm::vec2(7 * widthAnim, 6 * heightAnim));

	sprite->setAnimationSpeed(SLOW_LEFT, 6);
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(0 * widthAnim, 7 * heightAnim));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(1 * widthAnim, 7 * heightAnim));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(2 * widthAnim, 7 * heightAnim));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(3 * widthAnim, 7 * heightAnim));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(4 * widthAnim, 7 * heightAnim));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(5 * widthAnim, 7 * heightAnim));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(6 * widthAnim, 7 * heightAnim));
	sprite->addKeyframe(SLOW_LEFT, glm::vec2(7 * widthAnim, 7 * heightAnim));

	sprite->setAnimationSpeed(CLINBING_RIGHT, 8);
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(0 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(1 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(2 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(3 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(4 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(5 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(6 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(7 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(8 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(9 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(10 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(11 * widthAnim, 4 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(0 * widthAnim, 14 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(1 * widthAnim, 14 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(2 * widthAnim, 14 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(3 * widthAnim, 14 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(4 * widthAnim, 14 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(5 * widthAnim, 14 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(6 * widthAnim, 14 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(7 * widthAnim, 14 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(8 * widthAnim, 14 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(9 * widthAnim, 14 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(10 * widthAnim, 14 * heightAnim));
	sprite->addKeyframe(CLINBING_RIGHT, glm::vec2(11 * widthAnim, 14 * heightAnim));

	sprite->setAnimationSpeed(CLINBING_LEFT, 8);
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(0 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(1 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(2 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(3 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(4 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(5 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(6 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(7 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(8 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(9 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(10 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(11 * widthAnim, 5 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(0 * widthAnim, 15 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(1 * widthAnim, 15 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(2 * widthAnim, 15 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(3 * widthAnim, 15 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(4 * widthAnim, 15 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(5 * widthAnim, 15 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(6 * widthAnim, 15 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(7 * widthAnim, 15 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(8 * widthAnim, 15 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(9 * widthAnim, 15 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(10 * widthAnim, 15 * heightAnim));
	sprite->addKeyframe(CLINBING_LEFT, glm::vec2(11 * widthAnim, 15 * heightAnim));

	sprite->setAnimationSpeed(BEND_RIGHT, 8);
	sprite->addKeyframe(BEND_RIGHT, glm::vec2(0 * widthAnim, 10 * heightAnim));
	sprite->addKeyframe(BEND_RIGHT, glm::vec2(1 * widthAnim, 10 * heightAnim));
	sprite->addKeyframe(BEND_RIGHT, glm::vec2(2 * widthAnim, 10 * heightAnim));
	sprite->addKeyframe(BEND_RIGHT, glm::vec2(3 * widthAnim, 10 * heightAnim));
	sprite->addKeyframe(BEND_RIGHT, glm::vec2(4 * widthAnim, 10 * heightAnim));
	sprite->addKeyframe(BEND_RIGHT, glm::vec2(5 * widthAnim, 10 * heightAnim));
	sprite->addKeyframe(BEND_RIGHT, glm::vec2(6 * widthAnim, 10 * heightAnim));
	sprite->addKeyframe(BEND_RIGHT, glm::vec2(7 * widthAnim, 10 * heightAnim));
	sprite->addKeyframe(BEND_RIGHT, glm::vec2(8 * widthAnim, 10 * heightAnim));
	sprite->addKeyframe(BEND_RIGHT, glm::vec2(9 * widthAnim, 10 * heightAnim));
	sprite->addKeyframe(BEND_RIGHT, glm::vec2(10 * widthAnim, 10 * heightAnim));
	sprite->addKeyframe(BEND_RIGHT, glm::vec2(11 * widthAnim, 10 * heightAnim));
	
	sprite->setAnimationSpeed(BEND_LEFT, 8);
	sprite->addKeyframe(BEND_LEFT, glm::vec2(0 * widthAnim, 11 * heightAnim));
	sprite->addKeyframe(BEND_LEFT, glm::vec2(1 * widthAnim, 11 * heightAnim));
	sprite->addKeyframe(BEND_LEFT, glm::vec2(2 * widthAnim, 11 * heightAnim));
	sprite->addKeyframe(BEND_LEFT, glm::vec2(3 * widthAnim, 11 * heightAnim));
	sprite->addKeyframe(BEND_LEFT, glm::vec2(4 * widthAnim, 11 * heightAnim));
	sprite->addKeyframe(BEND_LEFT, glm::vec2(5 * widthAnim, 11 * heightAnim));
	sprite->addKeyframe(BEND_LEFT, glm::vec2(6 * widthAnim, 11 * heightAnim));
	sprite->addKeyframe(BEND_LEFT, glm::vec2(7 * widthAnim, 11 * heightAnim));
	sprite->addKeyframe(BEND_LEFT, glm::vec2(8 * widthAnim, 11 * heightAnim));
	sprite->addKeyframe(BEND_LEFT, glm::vec2(9 * widthAnim, 11 * heightAnim));
	sprite->addKeyframe(BEND_LEFT, glm::vec2(10 * widthAnim, 11 * heightAnim));
	sprite->addKeyframe(BEND_LEFT, glm::vec2(11 * widthAnim, 11 * heightAnim));


	sprite->setAnimationSpeed(ATACK_RIGHT, 8);
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(0 * widthAnim, 16 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(1 * widthAnim, 16 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(2 * widthAnim, 16 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(3 * widthAnim, 16 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(4 * widthAnim, 16 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(5 * widthAnim, 16 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(6 * widthAnim, 16 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(7 * widthAnim, 16 * heightAnim));

	sprite->setAnimationSpeed(ATACK_LEFT, 8);
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(0 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(1 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(2 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(3 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(4 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(5 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(6 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(7 * widthAnim, 17 * heightAnim));

	sprite->setAnimationSpeed(ATACK_WALK_RIGHT, 3);
	sprite->addKeyframe(ATACK_WALK_RIGHT, glm::vec2(0 * widthAnim, 16 * heightAnim));
	sprite->addKeyframe(ATACK_WALK_RIGHT, glm::vec2(1 * widthAnim, 16 * heightAnim));
	sprite->addKeyframe(ATACK_WALK_RIGHT, glm::vec2(2 * widthAnim, 16 * heightAnim));
	sprite->addKeyframe(ATACK_WALK_RIGHT, glm::vec2(3 * widthAnim, 16 * heightAnim));

	sprite->setAnimationSpeed(ATACK_WALK_LEFT, 3);
	sprite->addKeyframe(ATACK_WALK_LEFT, glm::vec2(0 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_WALK_LEFT, glm::vec2(1 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_WALK_LEFT, glm::vec2(2 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_WALK_LEFT, glm::vec2(3 * widthAnim, 17 * heightAnim));


	sprite->setAnimationSpeed(ATACK_PAUSE_RIGHT, 1);
	sprite->addKeyframe(ATACK_PAUSE_RIGHT, glm::vec2(0 * widthAnim, 16 * heightAnim));

	sprite->setAnimationSpeed(ATACK_PAUSE_LEFT, 1);
	sprite->addKeyframe(ATACK_PAUSE_LEFT, glm::vec2(0 * widthAnim, 17 * heightAnim));

	sprite->setAnimationSpeed(DRINK_RIGHT, 8);
	sprite->addKeyframe(DRINK_RIGHT, glm::vec2(0 * widthAnim, 8 * heightAnim));
	sprite->addKeyframe(DRINK_RIGHT, glm::vec2(1 * widthAnim, 8 * heightAnim));
	sprite->addKeyframe(DRINK_RIGHT, glm::vec2(2 * widthAnim, 8 * heightAnim));
	sprite->addKeyframe(DRINK_RIGHT, glm::vec2(3 * widthAnim, 8 * heightAnim));
	sprite->addKeyframe(DRINK_RIGHT, glm::vec2(4 * widthAnim, 8 * heightAnim));
	sprite->addKeyframe(DRINK_RIGHT, glm::vec2(5 * widthAnim, 8 * heightAnim));
	sprite->addKeyframe(DRINK_RIGHT, glm::vec2(6 * widthAnim, 8 * heightAnim));
	sprite->addKeyframe(DRINK_RIGHT, glm::vec2(7 * widthAnim, 8 * heightAnim));
	sprite->addKeyframe(DRINK_RIGHT, glm::vec2(8 * widthAnim, 8 * heightAnim));
	sprite->addKeyframe(DRINK_RIGHT, glm::vec2(9 * widthAnim, 8 * heightAnim));
	sprite->addKeyframe(DRINK_RIGHT, glm::vec2(10 * widthAnim, 8 * heightAnim));
	sprite->addKeyframe(DRINK_RIGHT, glm::vec2(11 * widthAnim, 8 * heightAnim));

	sprite->setAnimationSpeed(DRINK_LEFT, 1);
	sprite->addKeyframe(DRINK_LEFT, glm::vec2(0 * widthAnim, 9 * heightAnim));
	sprite->addKeyframe(DRINK_LEFT, glm::vec2(1 * widthAnim, 9 * heightAnim));
	sprite->addKeyframe(DRINK_LEFT, glm::vec2(2 * widthAnim, 9 * heightAnim));
	sprite->addKeyframe(DRINK_LEFT, glm::vec2(3 * widthAnim, 9 * heightAnim));
	sprite->addKeyframe(DRINK_LEFT, glm::vec2(4 * widthAnim, 9 * heightAnim));
	sprite->addKeyframe(DRINK_LEFT, glm::vec2(5 * widthAnim, 9 * heightAnim));
	sprite->addKeyframe(DRINK_LEFT, glm::vec2(6 * widthAnim, 9 * heightAnim));
	sprite->addKeyframe(DRINK_LEFT, glm::vec2(7 * widthAnim, 9 * heightAnim));
	sprite->addKeyframe(DRINK_LEFT, glm::vec2(8 * widthAnim, 9 * heightAnim));
	sprite->addKeyframe(DRINK_LEFT, glm::vec2(9 * widthAnim, 9 * heightAnim));
	sprite->addKeyframe(DRINK_LEFT, glm::vec2(10 * widthAnim, 9 * heightAnim));
	sprite->addKeyframe(DRINK_LEFT, glm::vec2(11 * widthAnim, 9 * heightAnim));

	sprite->setAnimationSpeed(TURN_LEFT, 1);
	sprite->addKeyframe(TURN_LEFT, glm::vec2(0 * widthAnim, 19 * heightAnim));
	sprite->addKeyframe(TURN_LEFT, glm::vec2(1 * widthAnim, 19 * heightAnim));
	sprite->addKeyframe(TURN_LEFT, glm::vec2(2 * widthAnim, 19 * heightAnim));
	sprite->addKeyframe(TURN_LEFT, glm::vec2(3 * widthAnim, 19 * heightAnim));
	sprite->addKeyframe(TURN_LEFT, glm::vec2(4 * widthAnim, 19 * heightAnim));
	sprite->addKeyframe(TURN_LEFT, glm::vec2(5 * widthAnim, 19 * heightAnim));

	sprite->setAnimationSpeed(TURN_RIGHT, 1);
	sprite->addKeyframe(TURN_RIGHT, glm::vec2(0 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(TURN_RIGHT, glm::vec2(1 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(TURN_RIGHT, glm::vec2(2 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(TURN_RIGHT, glm::vec2(3 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(TURN_RIGHT, glm::vec2(4 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(TURN_RIGHT, glm::vec2(5 * widthAnim, 18 * heightAnim));


	sprite->setAnimationSpeed(JUMP_SMALL_LEFT, 8);
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(0 * widthAnim, 21 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(1 * widthAnim, 21* heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(2 * widthAnim, 21* heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(3 * widthAnim, 21* heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(4 * widthAnim, 21* heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(5 * widthAnim, 21* heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(6 * widthAnim, 21* heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(7 * widthAnim, 21* heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(8 * widthAnim, 21* heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(9 * widthAnim, 21* heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(10 * widthAnim, 21* heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(11 * widthAnim, 21* heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(12 * widthAnim, 21* heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(13* widthAnim, 21* heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(14 * widthAnim, 21 * heightAnim));
	
	sprite->setAnimationSpeed(JUMP_SMALL_RIGHT, 8);
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(0 * widthAnim, 20 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(1 * widthAnim, 20 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(2 * widthAnim, 20 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(3 * widthAnim, 20 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(4 * widthAnim, 20 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(5 * widthAnim, 20 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(6 * widthAnim, 20 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(7 * widthAnim, 20 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(8 * widthAnim, 20 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(9 * widthAnim, 20 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(10 * widthAnim, 20 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(11 * widthAnim, 20 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(12 * widthAnim, 20 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(13 * widthAnim, 20 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_RIGHT, glm::vec2(14 * widthAnim, 20 * heightAnim));

	sprite->setAnimationSpeed(JUMP_BIG_RIGHT, 8);
	sprite->addKeyframe(JUMP_BIG_RIGHT, glm::vec2(0 * widthAnim, 12 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_RIGHT, glm::vec2(1 * widthAnim, 12 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_RIGHT, glm::vec2(2 * widthAnim, 12 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_RIGHT, glm::vec2(3 * widthAnim, 12 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_RIGHT, glm::vec2(4 * widthAnim, 12 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_RIGHT, glm::vec2(5 * widthAnim, 12 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_RIGHT, glm::vec2(6 * widthAnim, 12 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_RIGHT, glm::vec2(7 * widthAnim, 12 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_RIGHT, glm::vec2(8 * widthAnim, 12 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_RIGHT, glm::vec2(9 * widthAnim, 12 * heightAnim));

	sprite->setAnimationSpeed(JUMP_BIG_LEFT, 8);
	sprite->addKeyframe(JUMP_BIG_LEFT, glm::vec2(0 * widthAnim, 13 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_LEFT, glm::vec2(1 * widthAnim, 13 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_LEFT, glm::vec2(2 * widthAnim, 13 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_LEFT, glm::vec2(3 * widthAnim, 13 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_LEFT, glm::vec2(4 * widthAnim, 13 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_LEFT, glm::vec2(5 * widthAnim, 13 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_LEFT, glm::vec2(6 * widthAnim, 13 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_LEFT, glm::vec2(7 * widthAnim, 13 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_LEFT, glm::vec2(8 * widthAnim, 13 * heightAnim));
	sprite->addKeyframe(JUMP_BIG_LEFT, glm::vec2(9 * widthAnim, 13 * heightAnim));

	sprite->setAnimationSpeed(RUNNING_RIGHT, 8);
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(0 * widthAnim, 22 * heightAnim));
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(1 * widthAnim, 22 * heightAnim));
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(2 * widthAnim, 22 * heightAnim));
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(3 * widthAnim, 22 * heightAnim));
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(4 * widthAnim, 22 * heightAnim));
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(5 * widthAnim, 22 * heightAnim));
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(6 * widthAnim, 22 * heightAnim));
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(7 * widthAnim, 22 * heightAnim));
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(8 * widthAnim, 22 * heightAnim));
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(9 * widthAnim, 22 * heightAnim));
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(10 * widthAnim, 22 * heightAnim));
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(11 * widthAnim, 22 * heightAnim));
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(12 * widthAnim, 22 * heightAnim));
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(13 * widthAnim, 22 * heightAnim));
	sprite->addKeyframe(RUNNING_RIGHT, glm::vec2(14 * widthAnim, 22 * heightAnim));

	sprite->setAnimationSpeed(RUNNING_LEFT, 8);
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(0 * widthAnim, 23* heightAnim));
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(1 * widthAnim, 23 * heightAnim));
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(2 * widthAnim, 23 * heightAnim));
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(3 * widthAnim, 23 * heightAnim));
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(4 * widthAnim, 23 * heightAnim));
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(5 * widthAnim, 23 * heightAnim));
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(6 * widthAnim, 23 * heightAnim));
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(7 * widthAnim, 23 * heightAnim));
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(8 * widthAnim, 23 * heightAnim));
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(9 * widthAnim, 23 * heightAnim));
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(10 * widthAnim, 23 * heightAnim));
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(11 * widthAnim, 23 * heightAnim));
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(12 * widthAnim, 23 * heightAnim));
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(13 * widthAnim, 23 * heightAnim));
	sprite->addKeyframe(RUNNING_LEFT, glm::vec2(14 * widthAnim, 23 * heightAnim));

	estadoAnimacion[Estado::Stopped].left = STAND_LEFT;
	estadoAnimacion[Estado::Stopped].right = STAND_RIGHT;

	estadoAnimacion[Estado::Turn].left = STAND_LEFT;
	estadoAnimacion[Estado::Turn].right = STAND_RIGHT;

	estadoAnimacion[Estado::StartRun].left = STAND_LEFT;
	estadoAnimacion[Estado::StartRun].right = STAND_RIGHT;
	
	estadoAnimacion[Estado::Running].left = STAND_LEFT;
	estadoAnimacion[Estado::Running].right = STAND_RIGHT;
	
	estadoAnimacion[Estado::StopRun].left = STAND_LEFT;
	estadoAnimacion[Estado::StopRun].right = STAND_RIGHT;
	
	estadoAnimacion[Estado::SlowWalking].left = STAND_LEFT;
	estadoAnimacion[Estado::SlowWalking].right = STAND_RIGHT;
	
	estadoAnimacion[Estado::JumpBig].left = STAND_LEFT;
	estadoAnimacion[Estado::JumpBig].right = STAND_RIGHT;
	
	estadoAnimacion[Estado::Stopped].left = STAND_LEFT;
	estadoAnimacion[Estado::Stopped].right = STAND_RIGHT;

	sprite->changeAnimation(STAND_RIGHT);
	tileMapDispl = tileMapPos;

	setPosition(glm::vec2(400, 140));
	colisionBox = glm::ivec2(12, 44);
	defaultDrawAdjustment = glm::vec2(45, 40);
	drawAdjustment = defaultDrawAdjustment;
	direction = glm::vec2(1.0f, 0.0f);

	bMoving = false;
	bSuper = false;
	life = 3;
	maxLife = 3;
	damage = 1;

	SoundManager& sm = SoundManager::instance();

	snd_danoEspada.setBuffer(sm.get("danoEspada"));
	snd_danoPropio.setBuffer(sm.get("danoPropio"));
	snd_golpeAire.setBuffer(sm.get("golpeAire"));
	snd_desenfundar.setBuffer(sm.get("desenfundar"));
	snd_beberVida.setBuffer(sm.get("beberVida"));
}

void Player::reload(const glm::ivec2 & position)
{
	estado = Estado::Falling;
	sprite->changeAnimation(0);
	setPosition(position);
	
	direction = glm::vec2(1.0f, 0.0f);

	bMoving = false;
	life = 3;
}

glm::vec2 Player::getPosition()
{
	return posPlayer;
}

int Player::getLife()
{
	return life;
}

int Player::getMaxLife()
{
	return maxLife;
}

Enemy * Player::getTarget()
{
	return target;
}

bool Player::beaten()
{
	life = max(life-1, 0);
	snd_danoPropio.play();
	return true;
}

void Player::update(int deltaTime, vector<Enemy*>& enemies)
{
	sprite->update(deltaTime);

	//setPosition(posPlayer);
}

void Player::render()
{
	sprite->render();
}

void Player::setPhysicsTileMap(TileMap *tileMap)
{
	physicsMap = tileMap;
}

void Player::setFrontMap(TileMap * tileMap)
{
	frontMap = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	float posX = tileMapDispl.x + posPlayer.x - drawAdjustment.x;
	float posY = tileMapDispl.y + posPlayer.y - drawAdjustment.y;
	
	sprite->setPosition(glm::vec2(posX, posY));
}




