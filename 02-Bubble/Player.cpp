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


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_RIGHT, JUMP_LEFT, SLOW_RIGHT,
	SLOW_LEFT, CLINBING_LEFT, CLINBING_RIGHT, BEND_LEFT, BEND_RIGHT,
	ATACK_RIGHT, ATACK_LEFT, ATACK_WALK_RIGHT, ATACK_WALK_LEFT, ATACK_PAUSE_RIGHT,
	ATACK_PAUSE_LEFT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	estado = Estado::Falling;
	spritesheet.loadFromFile("images/prince-sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	double widthAnim = 1.0 / 16.0;
	double heightAnim = 1.0 / 20.0;
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(widthAnim, heightAnim), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(16);

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
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(0 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(1 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(2 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(3 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(4 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(5 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(6 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(7 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(8 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(9 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(10 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_RIGHT, glm::vec2(11 * widthAnim, 17 * heightAnim));

	sprite->setAnimationSpeed(ATACK_LEFT, 8);
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(0 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(1 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(2 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(3 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(4 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(5 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(6 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(7 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(8 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(9 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(10 * widthAnim, 18 * heightAnim));
	sprite->addKeyframe(ATACK_LEFT, glm::vec2(11 * widthAnim, 18 * heightAnim));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;

	setPosition(glm::vec2(400, 140));
	colisionBox = glm::ivec2(12, 44);
	drawAdjustment = glm::ivec2(45, 40);
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

void Player::beaten()
{
	life -= 1;
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);

	switch (estado) {
	case Estado::Stopped:
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {

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
				sprite->changeAnimation(STAND_RIGHT);
			}
			else {
				sprite->changeAnimation(STAND_LEFT);
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
				sprite->changeAnimation(STAND_RIGHT);
			}
			else {
				sprite->changeAnimation(STAND_LEFT);
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

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x - drawAdjustment.x), float(tileMapDispl.y + posPlayer.y - drawAdjustment.y)));
}




