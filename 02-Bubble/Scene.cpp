#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 0
#define INIT_PLAYER_Y_TILES 0


Scene::Scene()
{
	map = NULL;
	player = NULL;
	frontMap = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if (frontMap != NULL)
		delete frontMap;
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level05.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	physicsMap = TileMap::createTileMap("levels/level05.phy", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	frontMap = TileMap::createTileMap("levels/front05.txt",glm::vec2(SCREEN_X,SCREEN_Y), texProgram);

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	float mapTileSizeX = map->getTileSizeX();
	float mapTileSizeY = map->getTileSizeY();
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * mapTileSizeX, INIT_PLAYER_Y_TILES * mapTileSizeY));
	player->setPhysicsTileMap(physicsMap);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
} 

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
}

void Scene::render()
{
	glm::mat4 modelview;

	float cx = int(player->getPosition().x / CAMERA_WIDTH) * CAMERA_WIDTH;
	float cy = int(player->getPosition().y / CAMERA_HEIGHT) * CAMERA_HEIGHT;
	projection = glm::ortho(cx, float(CAMERA_WIDTH - 1+cx), float(CAMERA_HEIGHT - 1+cy), cy);

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::mat4(1.0f);
	
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map ->render();
	player->render();
	
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	frontMap -> render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



