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
	if (physicsMap != nullptr)
		delete physicsMap;
	if (frontMap != NULL)
		delete frontMap;
	if (torchMap != NULL)
		delete torchMap;
	if (doors != nullptr)
		delete doors;
	if (fallingFloor != nullptr)
		delete fallingFloor;
	if (trapsMap != nullptr)
		delete trapsMap;
	if(player != NULL)
		delete player;

	for (int i = 0; i < torches.size(); ++i) {
		delete torches[i];
	}
	for (int i = 0; i < gates.size(); ++i) {
		delete gates[i];
	}
	for (int i = 0; i < buttons.size(); i++) {
		delete buttons[i];
	}
	for (int i = 0; i < enemies.size(); ++i) {
		delete enemies[i];
	}
}

void Scene::reload() 
{
	float mapTileSizeX = map->getTileSizeX();
	float mapTileSizeY = map->getTileSizeY();

	player->reload(glm::vec2(INIT_PLAYER_X_TILES * mapTileSizeX, INIT_PLAYER_Y_TILES * mapTileSizeY));
	
	glm::vec2 enemyPos((INIT_PLAYER_X_TILES + 2) * mapTileSizeX, (INIT_PLAYER_Y_TILES + 2) * mapTileSizeY);
	enemies[0]->reload(enemyPos);

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);

	statusBar.init(glm::ivec2(0, 0), texProgram);
	menu.init(texProgram);

	bDead = false;

	for (auto gate : gates) {
		delete gate;
	}

	for (auto button : buttons) {
		delete button;
	}

	gates = vector<Gate*>();
	buttons = vector<ActivationButton*>();

	initTraps(trapsMap);
	physicsMap->reload();
	frontMap->reload();
}

void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level05.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	physicsMap = TileMap::createTileMap("levels/level05.phy", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	frontMap = TileMap::createTileMap("levels/front05.txt",glm::vec2(SCREEN_X,SCREEN_Y), texProgram);
	torchMap = TileMap::createTileMap("levels/torches05.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	trapsMap = TileMap::createTileMap("levels/trap05.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram); //Mapa para diferentes tipos de trampas

	initTorches(torchMap);
	initTraps(trapsMap);
	float mapTileSizeX = map->getTileSizeX();
	float mapTileSizeY = map->getTileSizeY();

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * mapTileSizeX, INIT_PLAYER_Y_TILES * mapTileSizeY));
	player->setPhysicsTileMap(physicsMap);
	player->setFrontMap(frontMap);


	Enemy* enemy = new Enemy();
	enemy->init(Enemy::Type::EMagenta, glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	glm::vec2 enemyPos((INIT_PLAYER_X_TILES + 2) * mapTileSizeX, (INIT_PLAYER_Y_TILES+2) * mapTileSizeY);
	enemy->setPosition(enemyPos);
	enemy->setPhysicsTileMap(physicsMap);

	enemies.push_back(enemy);

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);

	statusBar.init(glm::ivec2(0,0), texProgram);
	menu.init(texProgram);
	bDead = false;
	bShowMenu = true;

	estado = Estado::MenuJuego;

	
	SoundManager& sm = SoundManager::instance();
	
	snd_ganar.setBuffer(sm.get("ganar"));
	snd_perder.setBuffer(sm.get("perder"));
} 

void Scene::update(int deltaTime)
{
	switch (estado) {
	case Estado::MenuJuego:
		if (!menu.update(deltaTime)) {
			estado = Estado::Juego;
		}
		break;
	case Estado::Juego:
		if (player->getLife() <= 0) {
			estado = Estado::Muerto;
			statusBar.setDead(true);
			snd_perder.play();
		}
		updateEntities(deltaTime);
		break;
	case Estado::Muerto:
		updateEntities(deltaTime);

		if (Game::instance().getKey(13)) {
			reload();
			estado = Estado::Juego;
			
		}

		break;
	}	
}

void Scene::updateEntities(int deltaTime) {
	player->update(deltaTime, enemies);
	for (Enemy* e : enemies) {
		e->update(deltaTime, *player);
	}
	for (int i = 0; i < torches.size(); ++i) torches[i]->update(deltaTime);
	for (int i = 0; i < buttons.size(); ++i) buttons[i]->update(deltaTime, player->getPosition());
	for (int i = 0; i < gates.size(); ++i) gates[i]->update(deltaTime, physicsMap);
	statusBar.setLife(player->getLife());
	statusBar.update(deltaTime);
}

void Scene::render()
{
	glm::mat4 modelview;

	float cx = int(player->getPosition().x / CAMERA_WIDTH) * CAMERA_WIDTH;
	float cy = int(player->getPosition().y / CAMERA_HEIGHT) * CAMERA_HEIGHT;
	projection = glm::ortho(cx, float(CAMERA_WIDTH - 1 + cx), float(CAMERA_HEIGHT - 1 + cy), cy);
	//projection = glm::ortho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);


	texProgram.setUniform1f("invertir", 0.0f);
	map->render();
	texProgram.setUniform1f("invertir", 0.0f);

	for (int i = 0; i < torches.size(); ++i) torches[i]->render();
	for (int i = 0; i < buttons.size(); ++i) buttons[i]->render();
	for (int i = 0; i < gates.size(); ++i) gates[i]->render();

	player->render();
	for (Enemy* e : enemies) {
		e->render();
	}
	

	texProgram.setUniform1f("invertir", 0.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	frontMap->render();

	statusBar.setPosition(glm::vec2(cx, cy));
	statusBar.render();

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	if (estado == Estado::MenuJuego) {
		menu.render();
	}
}

void Scene::initTorches(TileMap* torcheMap) {

	int* map = torcheMap->getTileMap();
	int rows = torcheMap->getMapSizeY();
	int cols = torcheMap->getMapSizeX();

	int tileSizeX = torcheMap->getTileSizeX();
	int tileSizeY = torcheMap->getTileSizeY();

	for (int j = 0; j < rows; ++j) {
		for (int i = 0; i < cols; ++i) {
			if (map[j*cols + i] == 1) {
				const glm::ivec2 Coords = glm::ivec2(i*tileSizeX, j*tileSizeY);
				Torch* torch = new Torch();
				torch->init(Coords, texProgram);
				torches.push_back(torch);
			}
		}
	}
}

void Scene::initTraps(TileMap* trapsMap) {

	int* matrix = trapsMap->getTileMap();
	int rows = trapsMap->getMapSizeY();
	int cols = trapsMap->getMapSizeX();

	int tileSizeX = trapsMap->getTileSizeX();
	int tileSizeY = trapsMap->getTileSizeY();

	int elems = cols * rows;
	int i = 0;
	while (i < elems) {
		//Hemos encontrado un activador
		if (matrix[i] == 1) {
			ActivationButton* b = new ActivationButton();
			b->init(map, glm::ivec2((i%cols)*tileSizeX, (i / cols)*tileSizeY), texProgram);
			buttons.push_back(b);
			++i;
			while (i<elems && matrix[i] != 1) {
				if (matrix[i] == 2) {
					Gate* g = new Gate();
					g->init(b, glm::ivec2((i%cols)*tileSizeX, (i / cols)*tileSizeY), texProgram);
					gates.push_back(g);
				}
				++i;
			}
			--i;
		}
		else if (matrix[i] == 3) {
			//Trampa2
		}
		++i;
	}
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



