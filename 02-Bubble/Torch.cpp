#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Torch.h"
#include "Game.h"
#include "GL/glut.h"



void Torch::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("images/Animacio_Antorxes.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	double widthAnim = 1/10.0;
	double heightAnim = 1;
	//TODO: definir como constantes de la classe el tamanyo de la antorcha
	sprite = Sprite::createSprite(glm::ivec2(11.3, 32), glm::vec2(widthAnim, heightAnim), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	int ANIMATION = 0;
	sprite->setAnimationSpeed(ANIMATION, 12);
	sprite->addKeyframe(ANIMATION, glm::vec2(0 * widthAnim, heightAnim));
	sprite->addKeyframe(ANIMATION, glm::vec2(1 * widthAnim, heightAnim));
	sprite->addKeyframe(ANIMATION, glm::vec2(2 * widthAnim, heightAnim));
	sprite->addKeyframe(ANIMATION, glm::vec2(3 * widthAnim, heightAnim));
	sprite->addKeyframe(ANIMATION, glm::vec2(4 * widthAnim, heightAnim));
	sprite->addKeyframe(ANIMATION, glm::vec2(5 * widthAnim, heightAnim));

	sprite->changeAnimation(0);

	//TODO: falta definir el offset de la antorcha
	sprite->setPosition(glm::vec2(float(tileMapPos.x + 8.0f), float(tileMapPos.y+2)));
}

void Torch::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void Torch::render()
{
	sprite->render();
}




