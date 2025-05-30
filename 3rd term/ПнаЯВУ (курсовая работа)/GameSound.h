#pragma once
#include <array>
#include <SFML/Audio.hpp>
#include "Resources.h"

class GameSound
{
	static const int n = 3;					// ���������� ������
	std::array<sf::Sound,n> gSounds;		// ������ ������
	static GameSound* sInstance;			// �� ��� ���������� ������� ����� ��� ���� ���� ������ ������ ������
public:
	GameSound();
	static void play(int index);			// ��������� �����
	static void stop(int index);			// ���������� �����
};