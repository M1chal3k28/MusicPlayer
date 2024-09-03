#include <MusicContainer.hpp>
#include <filesystem>
#include <string>
#include <split.hpp>
#include <math.h>

#include <Config.hpp>

// Constructor for MusicContainer class
MusicContainer::MusicContainer(AudioCallback callback) 
    : id(0), volume(MUSIC_VOLUME), pitch(MUSIC_PITCH), pan(MUSIC_PAN)
{
    // Get the current working directory and append the "music" path
    std::filesystem::path path = std::filesystem::current_path().append("music");

    // Iterate over all files in the "music" directory
    for (auto &entry : std::filesystem::directory_iterator(path)) {
        // Check extension of the file 
        #ifdef _WIN32 
            std::string fileName = split(entry.path().string(), "\\").back();
            std::string extension = split(fileName, ".").back();
        #else 
            std::string fileName = split(entry.path().string(), "/").back();
            std::string extension = split(fileName, ".").back();
        #endif
        
        // Read only mp3, wav and m4a files
        if(
            extension == "mp3" ||
            extension == "wav" ||
            extension == "m4a"
        ) {
            // Load the music file and add it to the container
            Music music = LoadMusicStream(entry.path().string().c_str());
            
            // If cannot open a music stream
            if (!IsMusicReady(music)) {
                UnloadMusicStream(music);
                continue;
            }
            container.push_back({fileName, music});

            // Attach an audio stream processor to the music stream
            AttachAudioStreamProcessor(container.back().second.stream, callback);
        }
    }
}

// Get the music object at the specified index
Music MusicContainer::GetMusic(int id) {
    return container[id].second;
}

// Play the current music
void MusicContainer::Play() {
    // Set the music pitch, volume, and pan
    SetMusicPitch(GetMusic(id), this->pitch);
    SetMusicVolume(GetMusic(id), this->volume);
    SetMusicPan(GetMusic(id), this->pan);

    // Play the music stream
    PlayMusicStream(GetMusic(id));
}

// Stop the current music
void MusicContainer::Stop() {
    // Stop the music stream
    StopMusicStream(GetMusic(id));
}

// Seek to a position in the current music
void MusicContainer::Seek(float position) {
    // Calculate the new position
    float newPosition = GetMusicTimePlayed(GetMusic(id)) + position;
    if (newPosition < 0.0f) newPosition = GetMusicTimeLength(GetMusic(id)) + position;

    // Seek to the new position
    SeekMusicStream(GetMusic(id), newPosition);
}

// Increase the volume
void MusicContainer::AddVolume() {
    // Increase the volume by 0.05, capping at 1.0
    this->volume = std::min(1.0f, this->volume + 0.05f);

    // Set the new volume
    SetMusicVolume(GetMusic(id), this->volume);
}

// Decrease the volume
void MusicContainer::SubVolume() {
    // Decrease the volume by 0.05, capping at 0.0
    this->volume = std::max(0.0f, this->volume - 0.05f);

    // Set the new volume
    SetMusicVolume(GetMusic(id), this->volume);
}

// Increase the pitch
void MusicContainer::AddPitch() {
    // Increase the pitch by 0.05, capping at 2.0
    this->pitch = std::min(2.0f, this->pitch + 0.05f);

    // Set the new pitch
    SetMusicPitch(GetMusic(id), this->pitch);
}

// Decrease the pitch
void MusicContainer::SubPitch() {
    // Decrease the pitch by 0.05, capping at 0.05
    this->pitch = std::max(0.05f, this->pitch - 0.05f);

    // Set the new pitch
    SetMusicPitch(GetMusic(id), this->pitch);
}

// Increase the pan
void MusicContainer::AddPan() {
    // Increase the pan by 0.05, capping at 1.0
    this->pan = std::min(1.0f, this->pan + 0.05f);

    // Set the new pan
    SetMusicPan(GetMusic(id), this->pan);
}

// Decrease the pan
void MusicContainer::SubPan() {
    // Decrease the pan by 0.05, capping at 0.0
    this->pan = std::max(0.0f, this->pan - 0.05f);

    // Set the new pan
    SetMusicPan(GetMusic(id), this->pan);
}

// Get the filename of the current music
const char * MusicContainer::GetFileName() {
    return container[id].first.c_str();
}

// Update the music stream
void MusicContainer::Update() {
    UpdateMusicStream(GetMusic(id));
}

// Toggle the music playback
void MusicContainer::ToggleMusic() {
    // Check if the music is playing
    if(IsMusicStreamPlaying(GetMusic(id))) {
        // Pause the music stream
        PauseMusicStream(GetMusic(id));
    } else {
        // Resume the music stream
        ResumeMusicStream(GetMusic(id));
    }
}

// Check if the music is playing
bool MusicContainer::IsPlaying() {
    return IsMusicStreamPlaying(GetMusic(id));
}

// Get the number of seconds played
float MusicContainer::SecsPlaying() {
    return GetMusicTimePlayed(GetMusic(id));
}

// Get the number of music files
int MusicContainer::MusicCount() {
    return container.size();
}

// Play the next music file
void MusicContainer::NextMusic() {
    // Seek to the beginning of the current music
    SeekMusicStream(GetMusic(this->id), 0.01f);

    // Stop the current music
    Stop();

    // Increment the music index, wrapping around if necessary
    if (this->id == container.size() - 1) this->id = 0;
    else this->id++;

    // Play the next music
    Play();
}

// Play the previous music file
void MusicContainer::PrevMusic() {
    // Seek to the beginning of the current music
    SeekMusicStream(GetMusic(this->id), 0.01f);

    // Stop the current music
    Stop();

    // Decrement the music index, wrapping around if necessary
    if (this->id == 0) this->id = container.size() - 1;
    else this->id--;

    // Play the previous music
    Play();
}

// Get the music info (volume, pitch, pan)
std::map<std::string, float> MusicContainer::MusicInfo() {
    return {{"volume", volume}, {"pitch", pitch}, {"pan", pan}};
}