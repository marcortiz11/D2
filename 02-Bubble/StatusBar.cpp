#include "StatusBar.h"
#include <glm/gtc/matrix_transform.hpp>


StatusBar::StatusBar()
{
}


StatusBar::~StatusBar()
{
}

void StatusBar::init(const glm::ivec2 & pos, ShaderProgram & shaderProgram)
{
	// Select which font you want to use
	if (!text.init("fonts/alterebro-pixel-font.ttf"))
		//if(!text.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		throw std::runtime_error("Could not load font!!!");

	spritesheet.loadFromFile("images/vida.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	double widthAnim = 1;
	double heightAnim = 1.0/4.0;

	sprite = Sprite::createSprite(glm::ivec2(320, 8), glm::vec2(widthAnim, heightAnim), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);


	sprite->setAnimationSpeed(THREE_LIVES, 1);
	sprite->addKeyframe(THREE_LIVES, glm::vec2(0 * widthAnim, 0*heightAnim));

	sprite->setAnimationSpeed(TWO_LIVES, 1);
	sprite->addKeyframe(TWO_LIVES, glm::vec2(0 * widthAnim, 1*heightAnim));

	sprite->setAnimationSpeed(ONE_LIVE, 1);
	sprite->addKeyframe(ONE_LIVE, glm::vec2(0 * widthAnim, 2*heightAnim));

	sprite->setAnimationSpeed(DEAD, 1);
	sprite->addKeyframe(DEAD, glm::vec2(0 * widthAnim, 3 * heightAnim));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(0,189-8));

	elapsedTime = 3'600'000;
}

void StatusBar::update(int deltaTime)
{
	sprite->update(deltaTime);
	elapsedTime -= deltaTime;


}

void StatusBar::render() 
{
	sprite->render();
	glm::vec2 pos = sprite->getPosition();
	
	if (elapsedTime % 60000 >= 57000) {
		int minutes = elapsedTime / 1000 / 60;
		char str[16];
		sprintf(str, "%d MINUTES LEFT", minutes + 1);
		text.render(str, glm::vec2(400,609), 25, glm::vec4(1, 1, 1, 1));
	}
		
}

void StatusBar::setPosition(glm::vec2 pos)
{
	sprite->setPosition(glm::vec2(pos.x, pos.y+181));
}

void StatusBar::setLifeAnimation(Live live)
{
	switch (live) {
	case THREE_LIVES:
		sprite->changeAnimation(0);
		break;
	case TWO_LIVES:
		sprite->changeAnimation(1);
		break;
	case ONE_LIVE:
		sprite->changeAnimation(2);
		break;
	case DEAD:
		sprite->changeAnimation(3);
		break;
	}
}

void StatusBar::setLife(int live)
{
	switch (live) {
	case 0:
		setLifeAnimation(DEAD);
		break;
	case 1:
		setLifeAnimation(ONE_LIVE);
		break;
	case 2:
		setLifeAnimation(TWO_LIVES);
		break;
	case 3:
		setLifeAnimation(THREE_LIVES);
		break;
	}
}
