#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "ActivationButton.h"
#include "Game.h"
#include "GL/glut.h"

enum STATE { UNTOUCHED, PUSHED };

void ActivationButton::init(TileMap* t, const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/Animacion_Boton.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	double widthAnim = 1/2.0;
	double heightAnim = 1;
	//TODO: definir como constantes de la classe el tamanyo de la antorcha
	sprite = Sprite::createSprite(glm::ivec2(64, 63), glm::vec2(widthAnim, heightAnim), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(UNTOUCHED, 1);
	sprite->addKeyframe(UNTOUCHED, glm::vec2(0 * widthAnim, heightAnim));

	sprite->setAnimationSpeed(PUSHED, 1); //slow speed "heavy ActivationButton"
	sprite->addKeyframe(PUSHED, glm::vec2(1 * widthAnim, heightAnim));

	sprite->changeAnimation(UNTOUCHED);
	state = UNTOUCHED;
	//TODO: falta definir el offset de la antorcha
	TILEX = tileMapPos.x / t->getTileSizeX();
	TILEY = tileMapPos.y / t->getTileSizeY();
	map = t;
	sprite->setPosition(glm::vec2(tileMapPos.x, tileMapPos.y));
}

void ActivationButton::update(int deltaTime, const glm::ivec2 &posPlayer)
{
	//sprite->update(deltaTime);
	glm::ivec2 playerTiles = map->getTilePos(posPlayer);
	if (state == UNTOUCHED && playerTiles.x == TILEX && playerTiles.y == TILEY) {
		state = PUSHED;
		sprite->changeAnimation(PUSHED);
	}

}

void ActivationButton::render()
{
	sprite->render();
}




