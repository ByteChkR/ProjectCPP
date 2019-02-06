#include "AudioManager.h"
#include <iostream>

AudioManager * AudioManager:: instance;

AudioManager::AudioManager()
{
	if (instance == NULL)
	{
		instance = this;
	}
	LoadMusic("Dark _Atmosphere13_Looped_24bit.wav");


	AddSound("cloth-inventory.wav");//0
	AddSound("leather_inventory.wav");//1
	AddSound("metal-clash.wav");//2




}


AudioManager::~AudioManager()
{
}

void AudioManager::LoadMusic(std::string pFileLocation)
{
	sf::Music * music = new sf::Music();
	if (!music->openFromFile(_soundsPath + pFileLocation))
	{
		std::cout << "/////////////////   Sound path not found. /////////////////// \n" << pFileLocation << "\n";
		return;
	}
	
	music->play();

	music->setLoop(true);
}


void AudioManager::PlaySound(SoundEffects pSoundEffect)
{
	if ((int)pSoundEffect > _sounds.size() -1)
	{
		std::cout << "Number higher then number of sounds. The number is " << pSoundEffect <<
			" and the size is: " << _sounds.size();
		return;
	}
	_sounds[(int)pSoundEffect]->play();

}

void AudioManager::AddSound(std::string pFileLocation)
{
	
	sf::SoundBuffer * buffer = new sf::SoundBuffer();
	if (!buffer->loadFromFile(_soundsPath+pFileLocation))
	{
		std::cout << "/////////////////   Sound path not found. /////////////////// \n" << pFileLocation<<"\n";
	}

	sf::Sound * sound = new sf::Sound(*buffer);

	_sounds.push_back(sound);

}
