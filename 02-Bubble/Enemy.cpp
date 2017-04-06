#include "Enemy.h"

#define FALL_STEP 7

void Enemy::init(Type type, const glm::ivec2 &tileMapPos, ShaderProgram & shaderProgram)
{
	if (type == EMagenta) {
		spritesheet.loadFromFile("images/enemy-sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	else if (type == ECyan) {
		spritesheet.loadFromFile("images/enemy-sprite2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	double widthAnim = 1.0 / 16.0;
	double heightAnim = 1.0 / 20.0;
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(widthAnim, heightAnim), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(21);

	sprite->setAnimationSpeed(FALLING_LEFT, 1);
	sprite->addKeyframe(FALLING_LEFT, glm::vec2(1* widthAnim, 1 * heightAnim));

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

	sprite->setAnimationSpeed(ATACK_WALK_RIGHT, 1);
	sprite->addKeyframe(ATACK_WALK_RIGHT, glm::vec2(0 * widthAnim, 16 * heightAnim));
	sprite->addKeyframe(ATACK_WALK_RIGHT, glm::vec2(1 * widthAnim, 16 * heightAnim));
	sprite->addKeyframe(ATACK_WALK_RIGHT, glm::vec2(2 * widthAnim, 16 * heightAnim));
	sprite->addKeyframe(ATACK_WALK_RIGHT, glm::vec2(3 * widthAnim, 16 * heightAnim));

	sprite->setAnimationSpeed(ATACK_WALK_LEFT, 1);
	sprite->addKeyframe(ATACK_WALK_LEFT, glm::vec2(0 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_WALK_LEFT, glm::vec2(1 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_WALK_LEFT, glm::vec2(2 * widthAnim, 17 * heightAnim));
	sprite->addKeyframe(ATACK_WALK_LEFT, glm::vec2(3 * widthAnim, 17 * heightAnim));


	sprite->setAnimationSpeed(ATACK_PAUSE_RIGHT, 1);
	sprite->addKeyframe(ATACK_PAUSE_RIGHT, glm::vec2(0 * widthAnim, 16 * heightAnim));

	sprite->setAnimationSpeed(ATACK_PAUSE_LEFT, 1);
	sprite->addKeyframe(ATACK_PAUSE_LEFT, glm::vec2(0 * widthAnim, 17 * heightAnim));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;

	setPosition(glm::vec2(400, 140));
	colisionBox = glm::ivec2(12, 44);
	drawAdjustment = glm::ivec2(45, 40);
	direction = glm::vec2(1.0f, 0.0f);

	bMoving = false;
	bAtacking = false;
	estado = Estado::Falling;
	life = 3;

	
}

void Enemy::reload(const glm::ivec2 & position)
{
	sprite->changeAnimation(0);

	setPosition(position);
	direction = glm::vec2(1.0f, 0.0f);

	bMoving = false;
	bAtacking = false;
	estado = Estado::Falling;
	life = 3;
}

void Enemy::update(int deltaTime, Player& player)
{
	sprite->update(deltaTime);
	
	if (life <= 0) {
		sprite->changeAnimation(DEAD);
		return;
	}
	
	if (player.getLife() == 0) {
		if (direction.x > 0) {
			sprite->changeAnimation(STAND_RIGHT);
		}
		else {
			sprite->changeAnimation(STAND_LEFT);
		}
		return;
	}
	glm::vec2 positionPlayer = player.getPosition();
	switch(estado) {
	case Estado::Stopped:
		if (positionPlayer.y == posEnemy.y) {
			glm::vec2 direction = positionPlayer - posEnemy;
			if (abs(direction.x) > 32.0f) {
				targetPosEnemy = posEnemy;
				if (direction.x > 0) {
					targetPosEnemy.x = posEnemy.x + 32;
					sprite->changeAnimation(ATACK_WALK_RIGHT);

				}
				else if (direction.x < 0) {
					targetPosEnemy.x = posEnemy.x - 32;
					sprite->changeAnimation(ATACK_WALK_LEFT);
				}
				estado = Estado::SlowWalking;
			}
			else {
				if (direction.x > 0) {
					sprite->changeAnimation(ATACK_PAUSE_RIGHT);

				}
				else if (direction.x < 0) {
					sprite->changeAnimation(ATACK_PAUSE_LEFT);
				}
				estado = Estado::Fighting;
			}
			
		}
		break;
	case Estado::Atacking:
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
			&& sprite->getCurrentKeyframe() == 5 && !bBeaten) {
			int distancia = player.getPosition().x - positionPlayer.x;
			if (direction.x > 0) { // Esta mirando hacia la derecha
				if (distancia >= 0 && distancia <= 32) {
					if (player.beaten()) {
						//snd_danoEspada.play();
					}
				}
			}
			else {
				if (distancia >= -32 && distancia <= 0) {
					if (player.beaten()) {
						//snd_danoEspada.play();
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
		break;

	case Estado::Fighting:
		if (positionPlayer.y == posEnemy.y && abs(positionPlayer.x - posEnemy.x) <= 32.0f) {
			waitAtack = (std::rand() % 300);
			estado = Estado::Atacking;
		}
		else {
			estado = Estado::Stopped;
		}
		break;

	case Estado::Falling:
		posEnemy.y += FALL_STEP;
		if (physicsMap->collisionMoveDown(posEnemy, colisionBox))
		{
			posEnemy.y -= FALL_STEP;
			estado = Estado::Stopped;
			if (direction.x > 0) {
				sprite->changeAnimation(STAND_RIGHT);
			}
			else {
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		break;

	case Estado::SlowWalking:
		direction = glm::normalize(targetPosEnemy - posEnemy);

		posEnemy += direction*0.8f;

		if (glm::distance(targetPosEnemy, posEnemy) <= 1.5f) {
			posEnemy = targetPosEnemy;
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

	setPosition(posEnemy);
}

void Enemy::render()
{
	sprite->render();
}

void Enemy::setPhysicsTileMap(TileMap *tileMap)
{
	physicsMap = tileMap;
}

void Enemy::setPosition(const glm::vec2 &pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x - drawAdjustment.x), float(tileMapDispl.y + posEnemy.y - drawAdjustment.y)));
}

glm::vec2 Enemy::getPosition() const
{
	return posEnemy;
}

bool Enemy::beaten()
{
	life -= 1;
	return true;
}

int Enemy::getLife()
{
	return life;
}
