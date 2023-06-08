#include "SoundManager.h"

// Adds a track to the sound manager from a given file path
void SoundManager::addTrack(const std::string& filepath) {
    // Extract the song name from the file path
    std::string songName = getFileName(filepath);

    // Create a sound buffer and attempt to load the sound file into it
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath)) {
        // If the load fails, abort the operation
        return;
    }

    // If the load succeeds, add the buffer to the map
    buffers[songName] = std::move(buffer);
}

// Plays a sound with the specified songName
void SoundManager::playSound(const std::string& songName) {
    // Attempt to find the sound buffer in the map
    auto it = buffers.find(songName);
    if (it == buffers.end()) {
        // If the buffer isn't found, abort the operation
        return;
    }

    // Get an available sound object from the pool
    sf::Sound& sound = getAvailableSound();

    // Set the sound object to use the found sound buffer and play it
    sound.setBuffer(it->second);
    sound.play();
}

// Sets the volume of all sounds
void SoundManager::setVolume(float newVolume) {
    volume = newVolume;

    // Loop over all sounds in the pool and set their volume
    for (auto& sound : sounds) {
        sound.setVolume(newVolume);
    }
}

// Helper function to extract the file name from a given file path
std::string SoundManager::getFileName(const std::string& filepath) {
    // Remove directory (if present)
    const size_t lastSlashIndex = filepath.find_last_of("/\\");
    std::string filename = filepath.substr(lastSlashIndex + 1);

    // Remove extension (if present)
    const size_t periodIndex = filename.rfind('.');
    if (periodIndex != std::string::npos) {
        filename.erase(periodIndex);
    }

    return filename;
}

// Helper function to get an available sound object from the pool
sf::Sound& SoundManager::getAvailableSound() {
    // Loop over all sounds in the pool
    for (auto& sound : sounds) {
        // If a sound is not currently playing, return it
        if (sound.getStatus() != sf::Sound::Playing) {
            return sound;
        }
    }

    // If all sounds are currently playing, add a new one
    sounds.emplace_back();
    sounds.back().setVolume(volume);
    return sounds.back();
}
