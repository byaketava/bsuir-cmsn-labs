#include "GameSound.h"

GameSound* GameSound::sInstance = nullptr;

GameSound::GameSound()
{
	assert(sInstance == nullptr);
	sInstance = this;
	std::array<std::string, n> namefilebuf{ "res/background.ogg", "res/button.ogg", "res/cleared.ogg"};	// массив названий файлов
	for (int i = 0; i < n; i++)																			// присвоение объекту звука
		gSounds[i].setBuffer(Resources::getSound(namefilebuf[i]));	 
	gSounds[0].setLoop(true);																			// самый первый звук - фон, он воспроизводится циклично
};
void GameSound::play(int index)
{
	if (sInstance->gSounds[index].getStatus() == sf::SoundSource::Status::Stopped) 
		sInstance->gSounds[index].play();
}
void GameSound::stop(int index)
{
	if (sInstance->gSounds[index].getStatus() == sf::SoundSource::Status::Playing)
		sInstance->gSounds[index].stop();
}