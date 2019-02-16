#include "AudioManager.h"
#include <iostream>

AudioManager * AudioManager:: instance;

AudioManager::AudioManager()
{
	if (instance == NULL)
	{
		instance = this;
	}

	_musics = std::vector < sf::Music*>();

	LoadMusic("Dark _Atmosphere13_Looped_24bit.wav", "cloth-inventory.wav");
	AddMusic("GameOver.wav", "leather_inventory.wav");
	AddMusic("Background.wav", "metal-clash.wav");

	for (int i = 0; i <5; i++)
	{
		AddMusic("Background.wav", "metal-clash.wav");
	}

	//GameOver();

	AddSound("cloth-inventory.wav");//0
	AddSound("leather_inventory.wav");//1
	AddSound("metal-clash.wav");//2




}


AudioManager::~AudioManager()
{
	for (int i = 0; i < (int)_musics.size(); i++)
	{
		delete _musics[i];
	}

	_musics.clear();

	instance = nullptr;

}

void AudioManager::LoadMusic(std::string pFileLocation, std::string pAmbientLocation)
{
	AddMusic(pFileLocation,pAmbientLocation);
	_currentMusic = 0;
	_nextMusic = 0;


	_musics[_currentMusic]->setVolume(100);
	_ambients[_currentMusic]->setVolume(100);
	_musics[_currentMusic]->play();
	_ambients[_currentMusic]->play();



	
}


void AudioManager::PlaySound(int pNumber)
{
	if (pNumber > (int)_sounds.size() -1)
	{
		std::cout << "Number higher then number of sounds. The number is " << pNumber<<
			" and the size is: " << _sounds.size();
		return;
	}
	_sounds[pNumber]->play();

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

void AudioManager::AddMusic(std::string pFileLocation, std::string pAmbientPath)
{


	sf::Music * musicTrack = new sf::Music();

	if (!musicTrack->openFromFile(_soundsPath + pFileLocation))
	{
		std::cout << "/////////////////   Sound path not found. /////////////////// \n" << pFileLocation << "\n";
		return;
	}

	musicTrack->setLoop(true);

	//musicTrack->play();
	musicTrack->setVolume(0);

	_musics.push_back(musicTrack);


	sf::Music * ambient = new sf::Music();

	if (!ambient->openFromFile(_soundsPath + pAmbientPath))
	{
		std::cout << "/////////////////   Sound path not found. /////////////////// \n" << pFileLocation << "\n";
		return;
	}

	ambient->setLoop(true);

	//ambient->play();
	ambient->setVolume(0);

	_ambients.push_back(ambient);

}

void AudioManager::Restart(int pNumber)
{


	if (pNumber > (int)_musics.size() - 1)
	{
		std::cout << "can't restart index out of range";
		return;
	}

	_currentMusic = pNumber;
	_nextMusic = _currentMusic;
	_isClipChanged = true;
	_crossFader = 0;
	_isInGameOverScreen = false;

	StopAll();

	// Restart the track if needed.
	
	_musics[pNumber]->setVolume(100);
	_ambients[pNumber]->setVolume(100);
	_musics[pNumber]->play();
	_ambients[pNumber]->play();

}

void AudioManager::GameOver()
{
	_isInGameOverScreen = true;

	StopAll();

	_musics[1]->setVolume(100);
	_ambients[1]->setVolume(100);
	_musics[1]->play();
	_ambients[1]->play();
}

void AudioManager::Update(float pDeltaTime)
{
	if (_isInGameOverScreen == true)
	{
		return;
	}
	ControlBackgroundMusic(pDeltaTime);

}

void AudioManager::ControlBackgroundMusic(float pDeltaTime)
{
	if (_currentMusic != _nextMusic)
	{
		if (_crossFader > _secondsForCrossFader / 2)
		{
			_musics[_currentMusic]->setVolume( ((_crossFader - ( _secondsForCrossFader / 2)) / (_secondsForCrossFader / 2)) * 100);
			_ambients[_currentMusic]->setVolume(_musics[_currentMusic]->getVolume());
		}
		else
			if (_crossFader <= _secondsForCrossFader / 2 && _crossFader > 0)
			{
				ChangeClips();
				_musics[_nextMusic]->setVolume( (1 - (_crossFader / (_secondsForCrossFader / 2))) * 100);
				_ambients[_nextMusic]->setVolume(_musics[_nextMusic]->getVolume());
			}
			else
			{
				_currentMusic = _nextMusic;
				return;
			}


	}
	else
	{
		_crossFader = 0;
	}

	if (_crossFader > 0)
	{
		_crossFader -= pDeltaTime;
	}
}

void AudioManager::ChangeBackgroundMusic(int pNumber)
{
	if (pNumber > (int)_musics.size() - 1)
	{
		std::cout << "can't change music index out of range" << pNumber;
		return;
	}

	if (_crossFader > 0)
	{
		return;
	}

	_isClipChanged = false;
	_crossFader = _secondsForCrossFader;
	_nextMusic = pNumber;
		
}

void AudioManager::ChangeClips()
{
	if (_isClipChanged == false)
	{
		_isClipChanged = true;

		StopAll();

		_musics[_nextMusic]->play();
		_ambients[_nextMusic]->play();


	}
}

void AudioManager::StopAll()
{
	for (int i = 0; i < (int)_musics.size(); ++i)
	{
		_musics[i]->pause();
		_ambients[i]->pause();
	}
}