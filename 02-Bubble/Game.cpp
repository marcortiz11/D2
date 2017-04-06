#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	SoundManager& sm = SoundManager::instance();
	sm.add("danoEspada", "sounds/danoEspada.wav");
	sm.add("danoPropio", "sounds/danoPropio.wav");
	sm.add("golpeAire", "sounds/espadaAlAire.wav");
	sm.add("desenfundar", "sounds/desenfundarEspada.wav");
	sm.add("beberVida", "sounds/restaurarVida.wav");
	sm.add("boton", "sounds/boton.wav");
	sm.add("intro", "sounds/intro.wav");
	sm.add("puerta", "sounds/puerta2.wav");
	sm.add("ganar", "sounds/final.wav");
	sm.add("perder", "sounds/perder.wav");

	scene.init();
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





