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

	alturaBigJump = {0.0f, 0.25f, 0.35f, 0.40f, 0.50f, 0.48f, 0.40f, 0.35f, 0.25f, 0.0f};

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

	sprite->setAnimationSpeed(TURN_LEFT, 8);
	sprite->addKeyframe(TURN_LEFT, glm::vec2(0 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(TURN_LEFT, glm::vec2(1 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(TURN_LEFT, glm::vec2(2 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(TURN_LEFT, glm::vec2(3 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(TURN_LEFT, glm::vec2(4 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(TURN_LEFT, glm::vec2(5 * widthAnim, 18 * heightAnim));

	sprite->setAnimationSpeed(TURN_RIGHT, 8);
	sprite->addKeyframe(TURN_RIGHT, glm::vec2(0 * widthAnim, 19 * heightAnim));
	sprite->addKeyframe(TURN_RIGHT, glm::vec2(1 * widthAnim, 19 * heightAnim));
	sprite->addKeyframe(TURN_RIGHT, glm::vec2(2 * widthAnim, 19 * heightAnim));
	sprite->addKeyframe(TURN_RIGHT, glm::vec2(3 * widthAnim, 19 * heightAnim));
	sprite->addKeyframe(TURN_RIGHT, glm::vec2(4 * widthAnim, 19 * heightAnim));
	sprite->addKeyframe(TURN_RIGHT, glm::vec2(5 * widthAnim, 19 * heightAnim));


	sprite->setAnimationSpeed(JUMP_SMALL_LEFT, 8);
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(0 * widthAnim, 21 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(1 * widthAnim, 21 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(2 * widthAnim, 21 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(3 * widthAnim, 21 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(4 * widthAnim, 21 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(5 * widthAnim, 21 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(6 * widthAnim, 21 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(7 * widthAnim, 21 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(8 * widthAnim, 21 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(9 * widthAnim, 21 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(10 * widthAnim, 21 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(11 * widthAnim, 21 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(12 * widthAnim, 21 * heightAnim));
	sprite->addKeyframe(JUMP_SMALL_LEFT, glm::vec2(13 * widthAnim, 21 * heightAnim));
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


	sprite->changeAnimation(0);
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

void Player::estado_Stopped(int deltaTime, vector<Enemy*>& enemies) 
{
	bool enemyInSight = false;
	glm::ivec2 tilePosPlayer = frontMap->getTilePos(posPlayer);

	if (direction.x >= 0) {
		sprite->changeAnimation(STAND_RIGHT);
	}
	else {
		sprite->changeAnimation(STAND_LEFT);
	}

	target = nullptr;
	for (auto& e : enemies) {
		if (e->getLife() > 0 && posPlayer.y == e->getPosition().y) {
			enemyInSight = true;
			target = e;
		}
	}

	if (enemyInSight) {
		estado = Estado::Fighting;
		snd_desenfundar.play();
		if (direction.x >= 0) {
			sprite->changeAnimation(ATACK_PAUSE_RIGHT);
		}
		else {
			sprite->changeAnimation(ATACK_PAUSE_LEFT);
		}
	}
	else if ((Game::instance().getKey('a') || Game::instance().getKey('A')) &&
		frontMap->getIdTile(tilePosPlayer) == 5) {
		sprite->changeAnimation(DRINK_RIGHT);
		estado = Estado::Drinking;
		snd_beberVida.play();
		frontMap->clearPath(tilePosPlayer);
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) &&
		Game::instance().getSpecialKey(GLUT_KEY_UP)) 
	{
		for (int i = 0; i <= 160; i += 32) {
			glm::vec2 test = posPlayer - glm::vec2(i, 0);
			if (!physicsMap->collisionMoveLeft(test, colisionBox)) {
				targetPosPlayer = test;
			}
		}

		jumpDistance = glm::distance(posPlayer, targetPosPlayer);
		prevPosPlayer = posPlayer;
		
		if(direction.x >= 0) {
			sprite->changeAnimation(JUMP_BIG_RIGHT);
		} else {
			sprite->changeAnimation(JUMP_BIG_LEFT);
		}

		estado = Estado::JumpBig;
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) &&
		Game::instance().getSpecialKey(GLUT_KEY_UP)) 
	{
		for (int i = 0; i <= 160; i += 32) {
			glm::vec2 test = posPlayer + glm::vec2(i, 0);
			if (!physicsMap->collisionMoveLeft(test, colisionBox)) {
				targetPosPlayer = test;
			}
		}

		jumpDistance = glm::distance(posPlayer, targetPosPlayer);
		prevPosPlayer = posPlayer;

		if (direction.x >= 0) {
			sprite->changeAnimation(JUMP_BIG_RIGHT);
		}
		else {
			sprite->changeAnimation(JUMP_BIG_LEFT);
		}

		estado = Estado::JumpBig;
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {

		int animation = sprite->animation();

		glm::vec2 farPosition = posPlayer + glm::vec2(-64.0f, 0.0f);
		glm::vec2 closePosition = posPlayer + glm::vec2(-32.0f, 0.0f);

		if (!physicsMap->collisionMoveLeft(closePosition, colisionBox)) {
			targetPosPlayer = closePosition;
			if (!(Game::instance().getKey('A') || Game::instance().getKey('a'))) {
				if (!physicsMap->collisionMoveLeft(farPosition, colisionBox)) {
					targetPosPlayer = farPosition;
					estado = Estado::FastWalking;
					sprite->changeAnimation(MOVE_LEFT);
				}
			}
			else {
				estado = Estado::SlowWalking;
				sprite->changeAnimation(SLOW_LEFT);
			}

		}
		else {
			estado = Estado::Stopped;
			sprite->changeAnimation(animation);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
		int animation = sprite->animation();

		glm::vec2 farPosition = posPlayer + glm::vec2(64.0f, 0.0f);
		glm::vec2 closePosition = posPlayer + glm::vec2(32.0f, 0.0f);

		if (!physicsMap->collisionMoveLeft(closePosition, colisionBox)) {
			targetPosPlayer = closePosition;
			if (!(Game::instance().getKey('A') || Game::instance().getKey('a'))) {
				if (!physicsMap->collisionMoveLeft(farPosition, colisionBox)) {
					targetPosPlayer = farPosition;
					estado = Estado::FastWalking;
					sprite->changeAnimation(MOVE_RIGHT);
					sprite->setFlipY(false);
				}
			}
			else {
				estado = Estado::SlowWalking;
				sprite->changeAnimation(SLOW_RIGHT);
			}

		}
		else {
			estado = Estado::Stopped;
			sprite->changeAnimation(animation);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		// Si encima mio hay un cuadradito azul, marcar posicino como arriba, derecha. interporlar la escalada con una funcion suavita.
		glm::ivec2 tilePos = physicsMap->getTilePos(posPlayer + glm::vec2(0.0f, -32.0f));
		int idTile = physicsMap->getIdTile(tilePos);

		if (idTile == 4 || idTile == 5) {
			if (idTile == 4) {
				tilePos.x += 1;
				sprite->changeAnimation(CLINBING_RIGHT);
			}
			if (idTile == 5) {
				tilePos.x -= 1;
				sprite->changeAnimation(CLINBING_LEFT);
			}
			targetPosPlayer = physicsMap->getPixelPos(tilePos);
			estado = Estado::Climbing;
		}
		else {
			estado = Estado::Jumping;
			if (direction.x >= 0) {
				sprite->changeAnimation(JUMP_RIGHT);
			}
			else {
				sprite->changeAnimation(JUMP_LEFT);
			}
			jumpAngle = 0;
			startY = posPlayer.y;
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		if (direction.x >= 0) {
			sprite->changeAnimation(BEND_RIGHT);
		}
		else {
			sprite->changeAnimation(BEND_LEFT);
		}
		estado = Estado::Bend;
	}
}

void Player::estado_AtackWalk(int deltaTime) 
{
	direction = glm::normalize(targetPosPlayer - posPlayer);

	posPlayer += direction*0.8f;

	if (glm::distance(targetPosPlayer, posPlayer) <= 1.5f) {
		posPlayer = targetPosPlayer;
		estado = Estado::Falling;
		if (direction.x > 0) {
			sprite->changeAnimation(ATACK_PAUSE_RIGHT);
		}
		else {
			sprite->changeAnimation(ATACK_PAUSE_LEFT);
		}
	}
}

void Player::estado_Atacking(int deltaTime)
{
	waitAtack -= deltaTime;
	if (waitAtack <= 0 && !bAtacking) {
		bAtacking = true;
		bBeaten = false;
		timeToBeReady = 1000;
		if (direction.x > 0) {
			sprite->changeAnimation(ATACK_RIGHT);
		}
		else if (direction.x < 0) {
			sprite->changeAnimation(ATACK_LEFT);
		}
	}

	if ((sprite->animation() == ATACK_LEFT || sprite->animation() == ATACK_RIGHT)
		&& sprite->getCurrentKeyframe() == 2 && !bBeaten) {
		snd_golpeAire.play();
	}

	if ((sprite->animation() == ATACK_LEFT || sprite->animation() == ATACK_RIGHT)
		&& sprite->getCurrentKeyframe() == 5 && !bBeaten) {
		int distancia = target->getPosition().x - posPlayer.x;
		if (direction.x > 0) { // Esta mirando hacia la derecha
			if (distancia >= 0 && distancia <= 32) {
				if (target->beaten(damage)) {
					snd_danoEspada.play();
				}
			}
		}
		else {
			if (distancia >= -32 && distancia <= 0) {
				if (target->beaten(damage)) {
					snd_danoEspada.play();
				}
			}
		}


		bBeaten = true;
	}

	timeToBeReady -= deltaTime;
	if (timeToBeReady <= 0) {
		bAtacking = false;
		estado = Estado::Stopped;
	}
}

void Player::estado_Fighting(int deltaTime)
{
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {

		int animation = sprite->animation();

		glm::vec2 closePosition = posPlayer + glm::vec2(-32.0f, 0.0f);

		if (!physicsMap->collisionMoveLeft(closePosition, colisionBox)) {
			targetPosPlayer = closePosition;
			estado = Estado::AtackWalk;
			sprite->changeAnimation(ATACK_WALK_LEFT);
		}
		else {
			estado = Estado::Stopped;
			sprite->changeAnimation(animation);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
		int animation = sprite->animation();

		glm::vec2 closePosition = posPlayer + glm::vec2(32.0f, 0.0f);

		if (!physicsMap->collisionMoveLeft(closePosition, colisionBox)) {
			targetPosPlayer = closePosition;
			estado = Estado::AtackWalk;
			sprite->changeAnimation(ATACK_WALK_RIGHT);
		}
		else {
			estado = Estado::Stopped;
			sprite->changeAnimation(animation);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		// Si encima mio hay un cuadradito azul, marcar posicino como arriba, derecha. interporlar la escalada con una funcion suavita.
		glm::ivec2 tilePos = physicsMap->getTilePos(posPlayer + glm::vec2(0.0f, -32.0f));
		int idTile = physicsMap->getIdTile(tilePos);

		if (idTile == 4 || idTile == 5) {
			if (idTile == 4) {
				tilePos.x += 1;
				sprite->changeAnimation(CLINBING_RIGHT);
			}
			if (idTile == 5) {
				tilePos.x -= 1;
				sprite->changeAnimation(CLINBING_LEFT);
			}
			targetPosPlayer = physicsMap->getPixelPos(tilePos);
			estado = Estado::Climbing;
		}
		else {
			estado = Estado::Jumping;
			if (direction.x >= 0) {
				sprite->changeAnimation(JUMP_RIGHT);
			}
			else {
				sprite->changeAnimation(JUMP_LEFT);
			}
			jumpAngle = 0;
			startY = posPlayer.y;
		}
	}
	else if (Game::instance().getKey('a') || Game::instance().getKey('A')) {
		estado = Estado::Atacking;
	}
}

void Player::update(int deltaTime, vector<Enemy*>& enemies)
{
	sprite->update(deltaTime);

	if (life <= 0) {
		sprite->changeAnimation(DEAD);
		return;
	}

	if (bSuper) {
		superTime -= deltaTime;
		if (superTime <= 0) {
			bSuper = false;
			maxLife = maxLife / 2;
			life = min(life, maxLife);
			damage = damage / 2;
			sprite->setScaleFactor(1.0f);
			drawAdjustment = defaultDrawAdjustment;
		}
	}

	switch (estado) {
	case Estado::JumpBig: {
		float distance = glm::distance(targetPosPlayer, posPlayer);
		direction = glm::normalize(targetPosPlayer - posPlayer);

		posPlayer += direction *2.5f;

		float altura = prevPosPlayer.y - (24*alturaBigJump[sprite->getCurrentKeyframe()]);
		posPlayer.y = altura;

		if (glm::distance(targetPosPlayer, posPlayer) <= 4.0f) {
			posPlayer = targetPosPlayer;
			estado = Estado::Falling;
		}
	}
		
		break;

	case Estado::AtackWalk:
		estado_AtackWalk(deltaTime);
		break;
	case Estado::Atacking:
		estado_Atacking(deltaTime);
		break;
	case Estado::Fighting:
		estado_Fighting(deltaTime);
		break;
	case Estado::Drinking:
		if (sprite->getCurrentKeyframe() == 10) {
			estado = Estado::Stopped;
			superTime = 30000;
			maxLife = maxLife * 2;
			life = maxLife;
			bSuper = true;
			damage = damage * 2;
		}
		sprite->setScaleFactor(1.0f + (0.4f / 10 * sprite->getCurrentKeyframe()));
		drawAdjustment = defaultDrawAdjustment * (1.0f + (0.5f / 10 * sprite->getCurrentKeyframe()));
		break;
	case Estado::Stopped:
		estado_Stopped(deltaTime, enemies);
		break;

	case Estado::Bend:
		if (sprite->getCurrentKeyframe() == 11) {
			estado = Estado::Stopped;
			if (direction.x >= 0) {
				sprite->changeAnimation(STAND_RIGHT);
			}
			else {
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		
		break;
	case Estado::Climbing:
		direction = glm::normalize(targetPosPlayer - posPlayer);

		posPlayer += direction*0.4f;

		if (glm::distance(targetPosPlayer, posPlayer) <= 1.5f) {
			posPlayer = targetPosPlayer;
			estado = Estado::Falling;
			if (direction.x > 0) {
				sprite->changeAnimation(FALLING_RIGHT);
			}
			else {
				sprite->changeAnimation(FALLING_LEFT);
			}
		}
			break;
	case Estado::Jumping:
		if (sprite->getCurrentKeyframe() > 5) {
			jumpAngle += JUMP_ANGLE_STEP;
		}
		if (jumpAngle == 180)
		{
			estado = Estado::Falling;
			posPlayer.y = startY;
			if (direction.x >= 0) {
				sprite->changeAnimation(STAND_RIGHT);
			}
			else {
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		else
		{
			if (sprite->getCurrentKeyframe() > 5) {
				posPlayer.y = int(startY - 10 * sin(3.14159f * jumpAngle / 180.f));
				if (jumpAngle > 90)
					bJumping = !physicsMap->collisionMoveDown(posPlayer, colisionBox);
			}
		}
		break;

	case Estado::Falling:
		posPlayer.y += FALL_STEP;
		if (physicsMap->collisionMoveDown(posPlayer, colisionBox))
		{
			posPlayer.y -= FALL_STEP;
			estado = Estado::Stopped;
		}
		break;

	case Estado::FastWalking:
		direction = glm::normalize(targetPosPlayer - posPlayer);

		posPlayer += direction;

		if (glm::distance(targetPosPlayer, posPlayer) <= 1.5f) {
			posPlayer = targetPosPlayer;
			estado = Estado::Falling;
			if (direction.x > 0) {
				sprite->changeAnimation(FALLING_RIGHT);
			}
			else {
				sprite->changeAnimation(FALLING_LEFT);
			}
		}
		break;

	case Estado::SlowWalking:
		direction = glm::normalize(targetPosPlayer - posPlayer);

		posPlayer += direction*0.4f;

		if (glm::distance(targetPosPlayer, posPlayer) <= 1.5f) {
			posPlayer = targetPosPlayer;
			estado = Estado::Falling;
			if (direction.x > 0) {
				sprite->changeAnimation(STAND_RIGHT);
			}
			else {
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		break;
	}

	setPosition(posPlayer);
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




