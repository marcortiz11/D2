#pragma once

#include "Sprite.h"

class Menu
{
public:
	enum Screen {
		Jugar, Instrucciones, Creditos, InstruccionesTexto, CreditoTexto
	};
	void init(ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

private:
	glm::ivec2 tileMapDispl;
	//glm::vec2 posTorch, targetPosTorch, direction;
	Texture spritesheet;
	Sprite *sprite;

	Screen screen;

	bool bRender;

	int waitTime;
	const int WAIT_TIME = 1;
};




