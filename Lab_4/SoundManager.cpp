#include "SoundManager.h"


// get the name of the song from the filepath, map this with the full file path of the sound file
void SoundManager::addTrack(const std::string& filepath) {
    std::string songName = getFileName(filepath);
    soundMap[songName] = filepath;

    std::cout << songName << " , " << filepath << std::endl;
}


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


// adjust the volume 
void SoundManager::setVolume(float newVolume) {
    sound.setVolume(newVolume);
}


// check if the song name exists in a map pair
void SoundManager::playSound(const std::string& songName) {
    auto it = soundMap.find(songName);
    if (it == soundMap.end()) {
        // The song was not found
        std::cout << "SONG NOT FOUND" << std::endl;
        return;
    }

    if (!buffer.loadFromFile(it->second)) {
        // Failed to load the sound
        std::cout << "SONG NOT FOUND" << std::endl;
        return;
    }

    sound.setBuffer(buffer);
    sound.play();
}

