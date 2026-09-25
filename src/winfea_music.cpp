/*
WinFea(Window Feather)
A lightweight framework to build light apps :).
Made by: Juan Yaguaro(aka silverhacker)
License: GPL-2.0
*/

#include "winfea_music.hpp"

bool WinFeaMusic::LoadMusic(const std::string& path){

    if (music) {
        MIX_DestroyAudio(music);
        music = nullptr;
    }

    music = MIX_LoadAudio(mixer, path.c_str(), false);

    if (!music) {
            std::cerr << "Error to load " << path << ": " << SDL_GetError() << std::endl;
            return false;
        }

    if (!track && mixer) {
        track = MIX_CreateTrack(mixer);
        if (!track) {
            std::cerr << "Error to create track: " << SDL_GetError() << std::endl;
            return false;
        }
    }

    MIX_SetTrackAudio(track, music);

    return true;
}

bool WinFeaMusic::PlayMusic(float volume, int loops){
    if (!track) {
        std::cerr << "Error: No track available to play music! " << SDL_GetError() << std::endl;
        return false;
    }

    MIX_SetTrackGain(track, volume);

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, loops);

    bool success = MIX_PlayTrack(track, props);

    SDL_DestroyProperties(props);

    return success;
}