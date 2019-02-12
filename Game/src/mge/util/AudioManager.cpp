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

	LoadMusic("Dark _Atmosphere13_Looped_24bit.wav");
	AddMusic("GameOver.wav");
	AddMusic("Background.wav");

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

void AudioManager::LoadMusic(std::string pFileLocation)
{
	AddMusic(pFileLocation);
	_currentMusic = 0;
	_nextMusic = 0;

	
	_musics[_currentMusic]->play();

	_musics[_currentMusic]->setVolume(100);

	_musics[_currentMusic]->setLoop(true);

	
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

void AudioManager::AddMusic(std::string pFileLocation)
{
	_musicPaths.push_back(_soundsPath + pFileLocation);

	sf::Music * music = new sf::Music();

	if (!music->openFromFile(_soundsPath + pFileLocation))
	{
		std::cout << "/////////////////   Sound path not found. /////////////////// \n" << pFileLocation << "\n";
		return;
	}

	music->setLoop(true);

	_musics.push_back(music);

}

void AudioManager::Restart(int pNumber)
{


	if (pNumber > (int)_musicPaths.size() - 1)
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

	_musics[pNumber]->play();


}

void AudioManager::GameOver()
{
	_isInGameOverScreen = true;

	StopAll();

	_musics[1]->play();

	_musics[1]->setVolume(100);
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
		}
		else
			if (_crossFader <= _secondsForCrossFader / 2 && _crossFader > 0)
			{
				ChangeClips();
				_musics[_nextMusic]->setVolume( (1 - (_crossFader / (_secondsForCrossFader / 2))) * 100);
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
	if (pNumber > (int)_musicPaths.size() - 1)
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

		_musics[_nextMusic]->setVolume(0);

		_musics[_nextMusic]->play();

	}
}

void AudioManager::StopAll()
{
	for (int i = 0; i < (int)_musics.size(); ++i)
	{
		_musics[i]->pause();
	}
}