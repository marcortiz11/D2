#include "StatusBar.h"
#include <glm/gtc/matrix_transform.hpp>


StatusBar::StatusBar()
{
}


StatusBar::~StatusBar()
{
	delete sprite;
}

void StatusBar::reload() 
{
	sprite->changeAnimation(0);
	elapsedTime = 600'000;
	bDead = false;
}

void StatusBar::init(const glm::ivec2 & pos, ShaderProgram & shaderProgram)
{
	// Select which font you want to use
	if (!text.init("fonts/alterebro-pixel-font.ttf"))
		//if(!text.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		throw std::runtime_error("Could not load font!!!");

	spritesheet.loadFromFile("images/backgroundVida.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	double widthAnim = 1;
	double heightAnim = 1.0/1.0;

	sprite = Sprite::createSprite(glm::ivec2(320, 8), glm::vec2(widthAnim, heightAnim), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(THREE_LIVES, 1);
	sprite->addKeyframe(THREE_LIVES, glm::vec2(0 * widthAnim, 0*heightAnim));
	sprite->setPosition(glm::vec2(0,189-8));

	liveSpritesheet.loadFromFile("images/corazon.png", TEXTURE_PIXEL_FORMAT_RGBA);
	liveSpritesheet.setMinFilter(GL_NEAREST);
	liveSpritesheet.setMagFilter(GL_NEAREST);

	widthAnim = 1.0 / 2.0;
	heightAnim = 1.0 / 1.0f;

	spriteVida = Sprite::createSprite(glm::ivec2(6, 5), glm::vec2(widthAnim, heightAnim), &liveSpritesheet, &shaderProgram);
	spriteVida->setNumberAnimations(2);
	
	spriteVida->setAnimationSpeed(LIVE_FILLED, 1);
	spriteVida->addKeyframe(LIVE_FILLED, glm::vec2(0 * widthAnim, 0 * heightAnim));

	spriteVida->setAnimationSpeed(LIVE_EMPTY, 1);
	spriteVida->addKeyframe(LIVE_EMPTY, glm::vec2(1 * widthAnim, 0 * heightAnim));

	spriteVida->setPosition(glm::vec2(40, 60));


	liveEnemigoSpritesheet.loadFromFile("images/corazonEnemigo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	liveEnemigoSpritesheet.setMinFilter(GL_NEAREST);
	liveEnemigoSpritesheet.setMagFilter(GL_NEAREST);

	widthAnim = 1.0 / 2.0;
	heightAnim = 1.0 / 1.0f;

	spriteVidaEnemigo = Sprite::createSprite(glm::ivec2(6, 5), glm::vec2(widthAnim, heightAnim), &liveEnemigoSpritesheet, &shaderProgram);
	spriteVidaEnemigo->setNumberAnimations(2);

	spriteVidaEnemigo->setAnimationSpeed(LIVE_FILLED, 1);
	spriteVidaEnemigo->addKeyframe(LIVE_FILLED, glm::vec2(0 * widthAnim, 0 * heightAnim));

	spriteVidaEnemigo->setAnimationSpeed(LIVE_EMPTY, 1);
	spriteVidaEnemigo->addKeyframe(LIVE_EMPTY, glm::vec2(1 * widthAnim, 0 * heightAnim));

	spriteVidaEnemigo->setPosition(glm::vec2(200, 60));

	reload();
}

void StatusBar::update(int deltaTime)
{
	sprite->update(deltaTime);
	elapsedTime -= deltaTime;
	spriteVida->update(deltaTime);

}

void StatusBar::render() 
{
	sprite->render();
	
	glm::vec2 pos = position;
	
	if (player != nullptr) {
		pos.y += 1;
		pos.x += 1;

		spriteVida->setPosition(pos);
		spriteVida->changeAnimation(LIVE_FILLED);

		for (int i = 0; i < player->getLife(); ++i) {
			spriteVida->render();
			pos.x += 8;
			spriteVida->setPosition(pos);
		}

		spriteVida->changeAnimation(LIVE_EMPTY);
		for (int i = 0; i < player->getMaxLife() - player->getLife(); ++i) {
			spriteVida->render();
			pos.x += 8;
			spriteVida->setPosition(pos);
		}
	}

	pos = position;
	Enemy* enemy = player->getTarget();
	if (enemy != nullptr) {
		pos.x += 320 - enemy->getMaxLife() * 8;
		pos.y += 1;

		spriteVidaEnemigo->setPosition(pos);
		spriteVidaEnemigo->changeAnimation(LIVE_FILLED);

		for (int i = 0; i < enemy->getLife(); ++i) {
			spriteVidaEnemigo->render();
			pos.x += 8;
			spriteVidaEnemigo->setPosition(pos);
		}

		spriteVidaEnemigo->changeAnimation(LIVE_EMPTY);
		for (int i = 0; i < enemy->getMaxLife() - enemy->getLife(); ++i) {
			spriteVidaEnemigo->render();
			pos.x += 8;
			spriteVidaEnemigo->setPosition(pos);
		}
	}
	

	if (bDead) {
		char str[16];
		sprintf(str, "YOU ARE DEAD");
		text.render(str, glm::vec2(400, 609), 25, glm::vec4(1, 1, 1, 1));
	}
	else if (elapsedTime <= 0) {
		char str[16];
		sprintf(str, "- TIME OUT -");
		text.render(str, glm::vec2(400, 609), 25, glm::vec4(1, 1, 1, 1));
	}
	 else {
		if (elapsedTime % 60000 >= 57000) {
			int minutes = elapsedTime / 1000 / 60;
			char str[16];
			sprintf(str, "%d MINUTES LEFT", minutes + 1);
			text.render(str, glm::vec2(400, 609), 25, glm::vec4(1, 1, 1, 1));
		}
	}
}

void StatusBar::setPosition(glm::vec2 pos)
{
	this->position = glm::vec2(pos.x, pos.y + 181);
	sprite->setPosition(position);
}

void StatusBar::setPlayer(Player * player)
{
	this->player = player;
}


void StatusBar::setDead(bool b)
{
	bDead = b;
}

bool StatusBar::timeout()
{
	return elapsedTime <= 0;
}
