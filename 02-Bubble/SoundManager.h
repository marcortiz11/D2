#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class SoundManager
{
public:
	static SoundManager& instance() {
		static SoundManager sm;
		return sm;
	}

private:
	SoundManager() = default;;
	~SoundManager() = default;
public:
	void add(std::string id, std::string filename);
	bool contains(std::string id);
	sf::SoundBuffer& get(std::string id);

private:
	std::unordered_map<std::string, sf::SoundBuffer> map;

};

