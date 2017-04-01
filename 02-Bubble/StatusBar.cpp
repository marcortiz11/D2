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
	sprite->setNumberAnimations(1);

	int ANIMATION = 0;
	sprite->setAnimationSpeed(ANIMATION, 1);
	sprite->addKeyframe(ANIMATION, glm::vec2(0 * widthAnim, heightAnim));
	sprite->addKeyframe(ANIMATION, glm::vec2(0 * widthAnim, 1*heightAnim));
	sprite->addKeyframe(ANIMATION, glm::vec2(0 * widthAnim, 2*heightAnim));
	sprite->addKeyframe(ANIMATION, glm::vec2(0 * widthAnim, 3 * heightAnim));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(0,189-8));
}

void StatusBar::update(int deltaTime)
{
	sprite->update(deltaTime);
}


void StatusBar::render() 
{
	sprite->render();
	glm::vec2 pos = sprite->getPosition();
	text.render("60 MINUTES LEFT", glm::vec2(400,609), 25, glm::vec4(1, 1, 1, 1));

	
}

void StatusBar::setPosition(glm::vec2 pos)
{
	sprite->setPosition(glm::vec2(pos.x, pos.y+181));
}
