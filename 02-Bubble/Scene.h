#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Torch.h"
#include "Player.h"
#include "Text.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void initTorches(TileMap* torcheMap);
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	TileMap *map;
	TileMap *physicsMap;
	TileMap *frontMap;
	TileMap *torchMap;
	TileMap *doors;
	TileMap *fallingFloor; 
	Player *player;
	vector<Torch*> torches;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

	Text text;
};


#endif // _SCENE_INCLUDE

