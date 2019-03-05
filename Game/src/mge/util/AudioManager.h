#ifndef AudioManager_HPP
#define AudioManager_HPP

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <vector>

class AudioManager
{
public:

	static AudioManager * instance;
	enum SoundEffects
	{
		ClothInventory, LetherInventory, MetalClash
	};

	void AddSound(std::string pFileLocation);
	void AddMusic(std::string pFileLocation, std::string pAmbientPath);
	void Restart(int pNumber);
	void GameOver();
	void Update(float pDeltaTime);
	void PlaySound(int pNumber);
	void ChangeBackgroundMusic(int pNumber);
	void PlayFootStep();

	AudioManager();
	~AudioManager();

private:
	void AddFootStep(std::string pFileLocation);
	void ControlBackgroundMusic(float pDeltaTime);
	void ChangeClips();
	float _crossFader = 0;
	float _secondsForCrossFader = 4;
	bool _isClipChanged = true;
	bool _isInGameOverScreen;
	void LoadMusic(std::string pFileLocation, std::string pAmbientLocation);
	void StopAll();

	int _currentMusic;
	int _nextMusic;
	std::vector<sf::Sound *> _sounds;
	std::vector<sf::Sound *> _footSteps;
	std::string _soundsPath= "mge/sounds/";
	std::vector<sf::Music*> _musics;
	std::vector<sf::Music*> _ambients;

};

#endif // AudioManager_HPP

