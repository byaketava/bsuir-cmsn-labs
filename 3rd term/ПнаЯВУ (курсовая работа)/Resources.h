#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cassert>
#include <map>
#include <memory>

class Resources
{
public:
	Resources();
	static sf::Texture& getTexture(std::string const& filename);
	static sf::SoundBuffer& getSound(std::string const& filename);
	static sf::Font& getFont(std::string const& filename);

private:
	static Resources* sInstance;		// во всём приложении следует чтобы был лишь один объект класса ресурсов

	// переменные ключ - значение
	std::map< std::string, sf::Texture> textures;										
	std::map <std::string, sf::Font> fonts;
	std::map <std::string, sf::SoundBuffer> sounds;
};