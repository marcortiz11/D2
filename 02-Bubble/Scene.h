#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <SFML/Audio.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Torch.h"
#include "Player.h"
#include "StatusBar.h"
#include "Menu.h"
#include "Enemy.h"

#include "Gate.h"
#include "ActivationButton.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{
public:
	enum Estado {
		MenuJuego, Juego, Muerto
	};

public:
	Scene();
	~Scene();

	void init();
	void initTorches(TileMap* torcheMap);
	void initTraps(TileMap* trapMap);
	void update(int deltaTime);
	void render();

private:
	void initShaders();
	void reload();
	void updateEntities(int deltaTime);

private:
	TileMap *map;
	TileMap *physicsMap;
	TileMap *frontMap;
	TileMap *torchMap;
	TileMap *doors;
	TileMap *fallingFloor;
	TileMap *trapsMap;
	Player *player;
	
	vector<Torch*> torches;
	vector<Gate*> gates;
	vector<ActivationButton*> buttons;
	vector<Enemy*> enemies;
	
	ShaderProgram texProgram;
	glm::mat4 projection;

	StatusBar statusBar;

	Menu menu;

	bool bDead;
	bool bShowMenu;
	
	Estado estado;
	
	sf::SoundBuffer sndBuff_perder;
	sf::SoundBuffer sndBuff_ganar;

	sf::Sound snd_ganar;
	sf::Sound snd_perder;
};


#endif // _SCENE_INCLUDE

