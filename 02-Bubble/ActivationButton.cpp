#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "ActivationButton.h"
#include "Game.h"
#include "GL/glut.h"

enum STATE { UNTOUCHED, PUSHED };

void ActivationButton::init(TileMap* t, string textureName, const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile(textureName, TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	double widthAnim = 1/2.0;
	double heightAnim = 1;

	sprite = Sprite::createSprite(glm::ivec2(64, 63), glm::vec2(widthAnim, heightAnim), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(UNTOUCHED, 1);
	sprite->addKeyframe(UNTOUCHED, glm::vec2(0 * widthAnim, heightAnim));

	sprite->setAnimationSpeed(PUSHED, 1);
	sprite->addKeyframe(PUSHED, glm::vec2(1 * widthAnim, heightAnim));

	sprite->changeAnimation(UNTOUCHED);
	state = UNTOUCHED;
	TILEX = tileMapPos.x / t->getTileSizeX();
	TILEY = tileMapPos.y / t->getTileSizeY();
	map = t;
	sprite->setPosition(glm::vec2(tileMapPos.x, tileMapPos.y));
	
	snd_boton.setBuffer(SoundManager::instance().get("boton"));
}

void ActivationButton::update(int deltaTime, const glm::ivec2 &posPlayer)
{
	glm::ivec2 playerTiles = map->getTilePos(posPlayer);
	if (playerTiles.x == TILEX && playerTiles.y == TILEY) {
		if (state == UNTOUCHED) snd_boton.play();
		state = PUSHED;
		sprite->changeAnimation(PUSHED);
	}else{
		state = UNTOUCHED;
		sprite->changeAnimation(UNTOUCHED);
	}
}

void ActivationButton::render()
{
	sprite->render();
}




