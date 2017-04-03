#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Gate.h"
#include "Game.h"
#include "GL/glut.h"

enum STATE {CLOSED,MOVING,OPENED};

void Gate::init(ActivationButton *button, const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/Animacio_Porta.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	double widthAnim = 1;
	double heightAnim = 1 / 5.0;
	//TODO: definir como constantes de la classe el tamanyo de la antorcha
	sprite = Sprite::createSprite(glm::ivec2(32, 63), glm::vec2(widthAnim, heightAnim), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(CLOSED, 1);
	sprite->addKeyframe(CLOSED, glm::vec2(widthAnim, 0*heightAnim));

	sprite->setAnimationSpeed(MOVING, 2); //slow speed "heavy gate"
	sprite->addKeyframe(MOVING, glm::vec2(widthAnim, 0 * heightAnim));
	sprite->addKeyframe(MOVING, glm::vec2(widthAnim, 1 * heightAnim));
	sprite->addKeyframe(MOVING, glm::vec2(widthAnim, 2 * heightAnim));
	sprite->addKeyframe(MOVING, glm::vec2(widthAnim, 3 * heightAnim));
	sprite->addKeyframe(MOVING, glm::vec2(widthAnim, 4 * heightAnim));

	sprite->setAnimationSpeed(OPENED, 1);
	sprite->addKeyframe(OPENED, glm::vec2(widthAnim, 4*heightAnim));

	sprite->changeAnimation(CLOSED);
	state = CLOSED;
	//TODO: falta definir el offset de la antorcha
	sprite->setPosition( glm::vec2(tileMapPos.x, tileMapPos.y) );
	this->tileMapPos = tileMapPos;
	b = button;

}

void Gate::update(int deltaTime, TileMap* pyisics)
{
	//S'ha de tractar en funció a la posició del jugador
	if (state == CLOSED && b->isPushed()) {
		sprite->changeAnimation(MOVING);
		state = MOVING;
	}
	if (state == MOVING && sprite->getCurrentKeyframe() == 4) {
		pyisics->clearPath(pyisics->getTilePos(tileMapPos));
		sprite->changeAnimation(OPENED);
		state = OPENED;
	}
	sprite->update(deltaTime);
	
}

void Gate::render()
{
	sprite->render();
}




