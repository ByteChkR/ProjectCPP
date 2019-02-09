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

	void PlaySound(SoundEffects pSoundEffect);
	AudioManager();
	~AudioManager();

private:
	sf::Music * music;
	void LoadMusic(std::string pFileLocation);
	void AddSound(std::string pFileLocation);
	std::vector<sf::Sound *> _sounds;
	std::string _soundsPath= "mge/sounds/";

};

#endif // AudioManager_HPP

