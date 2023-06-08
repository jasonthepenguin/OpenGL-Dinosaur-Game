#pragma once


#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <deque>

/**
 * @class SoundManager
 * @brief A class that manages sound effects for a game.
 */
class SoundManager
{
public:
    /**
     * @brief Adds a sound track from a given file path.
     * @param filepath The path of the sound file to be added.
     */
    void addTrack(const std::string& filepath);

    /**
     * @brief Plays a sound with the specified songName.
     * @param songName The name of the song to be played.
     */
    void playSound(const std::string& songName);

    /**
     * @brief Sets the volume of all sounds.
     * @param newVolume The new volume level. Should be a value between 0 (silent)
     *        and 100 (full volume).
     */
    void setVolume(float newVolume);

private:
    /**
     * @brief Extracts the file name from a given file path.
     * @param filepath The file path from which the name should be extracted.
     * @return The extracted file name without extension.
     */
    std::string getFileName(const std::string& filepath);

    /**
     * @brief Gets an available sound object from the sound pool.
     * @return A reference to an available sound object.
     */
    sf::Sound& getAvailableSound();

    /**
     * @brief A map that holds sound buffers for each song name.
     */
    std::map<std::string, sf::SoundBuffer> buffers;

    /**
     * @brief A deque that holds all sound objects.
     */
    std::deque<sf::Sound> sounds;

    /**
     * @brief A variable that holds the volume level.
     */
    float volume = 100.0f;
};
