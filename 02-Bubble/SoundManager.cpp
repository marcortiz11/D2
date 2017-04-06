#include "SoundManager.h"

void SoundManager::add(std::string id, std::string filename)
{
	sf::SoundBuffer sndBuff;
	if (!sndBuff.loadFromFile(filename)) {
		throw std::runtime_error("Error al cargar el sonido.");
	}
	map[id] = std::move(sndBuff);
}

bool SoundManager::contains(std::string id)
{
	return map.find(id) != map.end();
}

sf::SoundBuffer& SoundManager::get(std::string id)
{
	// TODO poner una excepcio si el id no existe.
	return map[id];
}
