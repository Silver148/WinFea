#ifndef WINFEA_EVENTS_HPP
#define WINFEA_EVENTS_HPP

#include "winfea.hpp"
#include <functional>

#define WINFEA_KEY_UNKNOWN SDL_SCANCODE_UNKNOWN
#define WINFEA_KEY_A SDL_SCANCODE_A
#define WINFEA_KEY_B SDL_SCANCODE_B
#define WINFEA_KEY_C SDL_SCANCODE_C
#define WINFEA_KEY_D SDL_SCANCODE_D
#define WINFEA_KEY_E SDL_SCANCODE_E
#define WINFEA_KEY_F SDL_SCANCODE_F
#define WINFEA_KEY_G SDL_SCANCODE_G
#define WINFEA_KEY_H SDL_SCANCODE_H
#define WINFEA_KEY_I SDL_SCANCODE_I
#define WINFEA_KEY_J SDL_SCANCODE_J
#define WINFEA_KEY_K SDL_SCANCODE_K
#define WINFEA_KEY_L SDL_SCANCODE_L
#define WINFEA_KEY_M SDL_SCANCODE_M
#define WINFEA_KEY_N SDL_SCANCODE_N
#define WINFEA_KEY_O SDL_SCANCODE_O
#define WINFEA_KEY_P SDL_SCANCODE_P
#define WINFEA_KEY_Q SDL_SCANCODE_Q
#define WINFEA_KEY_R SDL_SCANCODE_R
#define WINFEA_KEY_S SDL_SCANCODE_S
#define WINFEA_KEY_T SDL_SCANCODE_T
#define WINFEA_KEY_U SDL_SCANCODE_U
#define WINFEA_KEY_V SDL_SCANCODE_V
#define WINFEA_KEY_W SDL_SCANCODE_W
#define WINFEA_KEY_X SDL_SCANCODE_X
#define WINFEA_KEY_Y SDL_SCANCODE_Y
#define WINFEA_KEY_Z SDL_SCANCODE_Z

#define WINFEA_KEY_0 SDL_SCANCODE_0
#define WINFEA_KEY_1 SDL_SCANCODE_1
#define WINFEA_KEY_2 SDL_SCANCODE_2
#define WINFEA_KEY_3 SDL_SCANCODE_3
#define WINFEA_KEY_4 SDL_SCANCODE_4
#define WINFEA_KEY_5 SDL_SCANCODE_5
#define WINFEA_KEY_6 SDL_SCANCODE_6
#define WINFEA_KEY_7 SDL_SCANCODE_7
#define WINFEA_KEY_8 SDL_SCANCODE_8
#define WINFEA_KEY_9 SDL_SCANCODE_9

#define WINFEA_KEY_RETURN SDL_SCANCODE_RETURN
#define WINFEA_KEY_ESCAPE SDL_SCANCODE_ESCAPE
#define WINFEA_KEY_BACKSPACE SDL_SCANCODE_BACKSPACE
#define WINFEA_KEY_TAB SDL_SCANCODE_TAB
#define WINFEA_KEY_SPACE SDL_SCANCODE_SPACE
#define WINFEA_KEY_MINUS SDL_SCANCODE_MINUS
#define WINFEA_KEY_EQUALS SDL_SCANCODE_EQUALS
#define WINFEA_KEY_LEFTBRACKET SDL_SCANCODE_LEFTBRACKET
#define WINFEA_KEY_RIGHTBRACKET SDL_SCANCODE_RIGHTBRACKET
#define WINFEA_KEY_BACKSLASH SDL_SCANCODE_BACKSLASH
#define WINFEA_KEY_SEMICOLON SDL_SCANCODE_SEMICOLON
#define WINFEA_KEY_APOSTROPHE SDL_SCANCODE_APOSTROPHE
#define WINFEA_KEY_GRAVE SDL_SCANCODE_GRAVE
#define WINFEA_KEY_COMMA SDL_SCANCODE_COMMA
#define WINFEA_KEY_PERIOD SDL_SCANCODE_PERIOD
#define WINFEA_KEY_SLASH SDL_SCANCODE_SLASH
#define WINFEA_KEY_CAPSLOCK SDL_SCANCODE_CAPSLOCK
#define WINFEA_KEY_F1 SDL_SCANCODE_F1
#define WINFEA_KEY_F2 SDL_SCANCODE_F2
#define WINFEA_KEY_F3 SDL_SCANCODE_F3
#define WINFEA_KEY_F4 SDL_SCANCODE_F4
#define WINFEA_KEY_F5 SDL_SCANCODE_F5
#define WINFEA_KEY_F6 SDL_SCANCODE_F6
#define WINFEA_KEY_F7 SDL_SCANCODE_F7
#define WINFEA_KEY_F8 SDL_SCANCODE_F8
#define WINFEA_KEY_F9 SDL_SCANCODE_F9
#define WINFEA_KEY_F10 SDL_SCANCODE_F10
#define WINFEA_KEY_F11 SDL_SCANCODE_F11
#define WINFEA_KEY_F12 SDL_SCANCODE_F12

#define WINFEA_KEY_UP SDL_SCANCODE_UP
#define WINFEA_KEY_DOWN SDL_SCANCODE_DOWN
#define WINFEA_KEY_LEFT SDL_SCANCODE_LEFT
#define WINFEA_KEY_RIGHT SDL_SCANCODE_RIGHT
#define WINFEA_KEY_LSHIFT SDL_SCANCODE_LSHIFT
#define WINFEA_KEY_RSHIFT SDL_SCANCODE_RSHIFT
#define WINFEA_KEY_LCTRL SDL_SCANCODE_LCTRL
#define WINFEA_KEY_RCTRL SDL_SCANCODE_RCTRL
#define WINFEA_KEY_LALT SDL_SCANCODE_LALT
#define WINFEA_KEY_RALT SDL_SCANCODE_RALT
#define WINFEA_KEY_LGUI SDL_SCANCODE_LGUI
#define WINFEA_KEY_RGUI SDL_SCANCODE_RGUI
#define WINFEA_KEY_MENU SDL_SCANCODE_MENU

class WinFeaEvent {
private:
    SDL_Event e{};
    std::vector<std::function<void()>> registeredEvents;

public:
    bool running = true;
    virtual ~WinFeaEvent() = default;

    void SetRunning(bool value) {
        running = value;
    }

    bool IsRunning() const {
        return running;
    }

    void RegisterEvent(std::function<void()> callback) {
        if (callback) {
            registeredEvents.push_back(std::move(callback));
        }
    }

    void RegisterEvent(void (*callback)(WinFeaEvent&)) {
        if (callback) {
            registeredEvents.push_back([this, callback]() {
                callback(*this);
            });
        }
    }

    void RegisterEvent(void (*callback)()) {
        if (callback) {
            registeredEvents.push_back(callback);
        }
    }

    void Update() {
        for (auto& callback : registeredEvents) {
            if (callback) {
                callback();
            }
        }
    }

    void ManageEvents() {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                running = false;
            }
        }
    }

    bool IsKeyDown(SDL_Scancode key) const {
        const bool* keyboardState = SDL_GetKeyboardState(nullptr);
        return keyboardState != nullptr && keyboardState[key];
    }

    bool IsKeyUp(SDL_Scancode key) const {
        const bool* keyboardState = SDL_GetKeyboardState(nullptr);
        return keyboardState == nullptr || !keyboardState[key];
    }
};

inline WinFeaEvent& WinFeaGetEventSystem() {
    static WinFeaEvent eventSystem;
    return eventSystem;
}

inline bool WinFeaIsKeyPressed(SDL_Scancode key) {
    return WinFeaGetEventSystem().IsKeyDown(key);
}

inline bool WinFeaIsKeyPressed(SDL_Keycode key) {
    return WinFeaIsKeyPressed(SDL_GetScancodeFromKey(key, nullptr));
}

inline bool WinFeaIsKeyUp(SDL_Scancode key) {
    return WinFeaGetEventSystem().IsKeyUp(key);
}

inline bool WinFeaIsKeyUp(SDL_Keycode key) {
    return WinFeaIsKeyUp(SDL_GetScancodeFromKey(key, nullptr));
}

#endif