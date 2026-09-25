/*
WinFea(Window Feather)
A lightweight framework to build light apps :).
Made by: Juan Yaguaro(aka silverhacker)
License: GPL-2.0
*/

#ifndef WINFEA_MUSIC_HPP
#define WINFEA_MUSIC_HPP

#include "winfea.hpp"

class WinFeaMusic {
private:
    static inline MIX_Mixer* mixer = nullptr;
    static inline int instancesCount = 0;

    MIX_Audio* music = nullptr;
    MIX_Track* track = nullptr;

public:
    WinFeaMusic() {
        if (mixer == nullptr) {
            mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
            if (!mixer) {
                std::cerr << "Error to create the global mixer: " << SDL_GetError() << std::endl;
                return;
            }
        }

        ++instancesCount;
    }

    ~WinFeaMusic() {
        if (track) {
            MIX_SetTrackAudio(track, nullptr);
            MIX_DestroyTrack(track);
            track = nullptr;
        }

        if (music) {
            MIX_DestroyAudio(music);
            music = nullptr;
        }

        if (instancesCount > 0) {
            --instancesCount;
        }
    }

    static void Shutdown() {
        if (mixer) {
            MIX_DestroyMixer(mixer);
            mixer = nullptr;
        }

        instancesCount = 0;
        MIX_Quit();
    }

    WinFeaMusic(const WinFeaMusic&) = delete;
    WinFeaMusic& operator=(const WinFeaMusic&) = delete;
    WinFeaMusic(WinFeaMusic&&) = delete;
    WinFeaMusic& operator=(WinFeaMusic&&) = delete;

    bool LoadMusic(const std::string& path);
    bool PlayMusic(float volume = 1.0f, int loops = 0);
};

#endif