#pragma once
#include <array>
#include <SFML/Audio.hpp>
#include "Resources.h"

class GameSound
{
	static const int n = 3;					// количество звуков
	std::array<sf::Sound,n> gSounds;		// массив звуков
	static GameSound* sInstance;			// во всём приложении следует чтобы был лишь один объект класса музыки
public:
	GameSound();
	static void play(int index);			// включение звука
	static void stop(int index);			// выключение звука
};