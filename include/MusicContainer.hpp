#pragma once

#include <raylib.h>

#include <iostream>
#include <vector>
#include <map>

class MusicContainer {
public:
    MusicContainer(AudioCallback callback);

    void Update();
    void Play();
    void Stop();
    void Seek(float position);

    // Setting volume, pan and pitch for music
    void AddVolume();
    void SubVolume();
    void AddPitch();
    void SubPitch();
    void AddPan();
    void SubPan();

    void ToggleMusic();
    void NextMusic();
    void PrevMusic();

    // Getters
    bool IsPlaying();
    float SecsPlaying();
    int MusicCount();
    std::map<std::string, float> MusicInfo();

    const char * GetFileName();
private:
    std::vector<std::pair<std::string, Music>> container;

    Music GetMusic(int id);
    int id;
    float volume;
    float pitch;
    float pan;
};