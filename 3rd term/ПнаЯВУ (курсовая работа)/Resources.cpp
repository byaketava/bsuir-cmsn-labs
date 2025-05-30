#include "Resources.h"

Resources* Resources::sInstance = nullptr;

Resources::Resources()
{
	assert(sInstance == nullptr);
	sInstance = this;
}

sf::Texture& Resources::getTexture(std::string const& filename)		// filename - ключ
{
	auto& Map = sInstance->textures;
	auto value = Map.find(filename);								// value - значение
	if (value != Map.end())
	{
		return value->second;
	}
	else
	{
		auto& texture = Map[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}

sf::Font& Resources::getFont(std::string const& filename)
{
	auto& Map = sInstance->fonts;
	auto value = Map.find(filename);
	if (value != Map.end())
	{
		return value->second;													
	}
	else
	{
		auto& font = Map[filename];
		font.loadFromFile(filename);
		return font;
	}
}
 
sf::SoundBuffer& Resources::getSound(std::string const& filename)
{
	auto& Map = sInstance->sounds;
	auto value = Map.find(filename);

	if (value != Map.end())
	{
		return value->second;
	}
	else
	{
		auto& sound = Map[filename];
		sound.loadFromFile(filename);
		return sound;
	}
}