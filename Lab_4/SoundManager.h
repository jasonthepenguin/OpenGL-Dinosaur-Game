#pragma once


#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>

class SoundManager
{

public:

	
	void addTrack(const std::string& filepath); // get the name of the song, map this with the full file path of the sound file

	void playSound(const std::string& songName); // check if the song name exists in a map pair
	
	void setVolume(float newVolume); // adjust the volume 
	
	
private:


	std::string getFileName(const std::string& filepath);

	std::map<std::string, std::string> soundMap;

	sf::SoundBuffer buffer;
	sf::Sound sound;

};

