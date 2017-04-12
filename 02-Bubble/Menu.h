#pragma once

#include "Sprite.h"
#include <SFML/Audio.hpp>

class Menu
{
public:
	Menu();
	enum Screen {
		Jugar, Instrucciones, Creditos, InstruccionesTexto, CreditoTexto, Win
	};
	void init(ShaderProgram &shaderProgram);
	bool update(int deltaTime);
	void render();

	void setWin();

private:
	glm::ivec2 tileMapDispl;
	//glm::vec2 posTorch, targetPosTorch, direction;
	Texture spritesheet;
	Sprite *sprite;

	Screen screen;

	int waitTime;
	const int WAIT_TIME = 1000;

	sf::Sound sndIntroduccion;
};




