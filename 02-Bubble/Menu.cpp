#include "Menu.h"
#include "Game.h"
#include "GL/glut.h"

Menu::Menu() :
	WAIT_TIME(100)
{

}

void Menu::init(ShaderProgram & shaderProgram)
{
	spritesheet.loadFromFile("images/menu_completo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	double widthAnim = 1;
	double heightAnim = 1.0/5.0;
	//TODO: definir como constantes de la classe el tamanyo de la antorcha
	sprite = Sprite::createSprite(glm::ivec2(320, 189), glm::vec2(widthAnim, heightAnim), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(5);

	sprite->setAnimationSpeed(Jugar, 12);
	sprite->addKeyframe(Jugar, glm::vec2(0 * widthAnim,0* heightAnim));

	sprite->setAnimationSpeed(Instrucciones, 12);
	sprite->addKeyframe(Instrucciones, glm::vec2(0 * widthAnim,1* heightAnim));

	sprite->setAnimationSpeed(Creditos, 12);
	sprite->addKeyframe(Creditos, glm::vec2(0 * widthAnim,2* heightAnim));

	sprite->setAnimationSpeed(InstruccionesTexto, 12);
	sprite->addKeyframe(InstruccionesTexto, glm::vec2(0 * widthAnim,3* heightAnim));

	sprite->setAnimationSpeed(CreditoTexto, 12);
	sprite->addKeyframe(CreditoTexto, glm::vec2(0 * widthAnim, 4*heightAnim));

	sprite->changeAnimation(0);

	sprite->setPosition(glm::vec2(0, 0));

	screen = Screen::Jugar;
	waitTime = 0;

	sndIntroduccion.setBuffer(SoundManager::instance().get("intro"));
	sndIntroduccion.play();
}

bool Menu::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (waitTime <= 0) {
		
		switch (screen) {
		case Jugar:
			if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				sprite->changeAnimation(Creditos);
				screen = Screen::Creditos;
				waitTime = WAIT_TIME;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
				sprite->changeAnimation(Instrucciones);
				screen = Screen::Instrucciones;
				waitTime = WAIT_TIME;
			}
			else if (Game::instance().getKey(13)) { //Press enter
				sndIntroduccion.pause();
				return false;
			}
			break;
		case Instrucciones:
			if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				sprite->changeAnimation(Jugar);
				screen = Screen::Jugar;
				waitTime = WAIT_TIME;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
				sprite->changeAnimation(Creditos);
				screen = Screen::Creditos;
				waitTime = WAIT_TIME;
			}
			else if (Game::instance().getKey(13)) { //Press enter
				sprite->changeAnimation(InstruccionesTexto);
				screen = Screen::InstruccionesTexto;
				waitTime = WAIT_TIME;
			}
			break;
		case Creditos:
			if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				sprite->changeAnimation(Instrucciones);
				screen = Screen::Instrucciones;
				waitTime = WAIT_TIME;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
				sprite->changeAnimation(Jugar);
				screen = Screen::Jugar;
				waitTime = WAIT_TIME;
			}
			else if (Game::instance().getKey(13)) { //Press enter
				sprite->changeAnimation(CreditoTexto);
				screen = Screen::CreditoTexto;
				waitTime = WAIT_TIME;
			}
			break;
		case InstruccionesTexto:
		case CreditoTexto:
			if (Game::instance().getKey(13)) { //Press enter
				sprite->changeAnimation(Jugar);
				screen = Screen::Jugar;
				waitTime = WAIT_TIME;
			}
			break;
		}
	}

	waitTime -= deltaTime;
	return true;
}

void Menu::render()
{
	sprite->render();
}
