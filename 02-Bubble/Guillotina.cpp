#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Guillotina.h"
#include "Game.h"
#include "GL/glut.h"

void Guillotina::init(const glm::vec2 &tileMapPos, TileMap *map, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/guillotineAnimation2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	double widthAnim = 1/5.0;
	double heightAnim = 1;

	sprite = Sprite::createSprite(glm::ivec2(32, 63), glm::vec2(widthAnim, heightAnim), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0 * widthAnim, heightAnim));
	sprite->addKeyframe(0, glm::vec2(0 * widthAnim, heightAnim));
	sprite->addKeyframe(0, glm::vec2(0 * widthAnim, heightAnim));
	sprite->addKeyframe(0, glm::vec2(0 * widthAnim, heightAnim));
	sprite->addKeyframe(0, glm::vec2(0 * widthAnim, heightAnim));
	sprite->addKeyframe(0, glm::vec2(0 * widthAnim, heightAnim));
	sprite->addKeyframe(0, glm::vec2(0 * widthAnim, heightAnim));
	sprite->addKeyframe(0, glm::vec2(1 * widthAnim, heightAnim));
	sprite->addKeyframe(0, glm::vec2(2 * widthAnim, heightAnim));
	sprite->addKeyframe(0, glm::vec2(3 * widthAnim, heightAnim));
	sprite->addKeyframe(0, glm::vec2(4 * widthAnim, heightAnim));

	sprite->changeAnimation(0);

	sprite->setPosition(tileMapPos);
	this->tileMapPos = tileMapPos;
	this->map = map;
}

void Guillotina::update(int deltaTime, Player *p)
{
	//S'ha de tractar en funció a la posició del jugador
	bool sameY = map->getTilePos(p->getPosition()).y == map->getTilePos(tileMapPos).y;
	bool sameXRange = p->getPosition().x+ 16 < tileMapPos.x + 20 && p->getPosition().x + 16 > tileMapPos.x;
	if (sameY && sameXRange && sprite->getCurrentKeyframe() > 7 && sprite->getCurrentKeyframe() <= 10) {
		p->beaten(); p->beaten(); p->beaten(); // Guillotina = -3 vida
	}
	sprite->update(deltaTime);

}

void Guillotina::render()
{
	sprite->render();
}




