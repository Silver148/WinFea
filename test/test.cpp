#include "winfea.hpp"

int main(){

    render r = nullptr; //renderer variable
    win w = nullptr; //window variable

    WinFea::WinFeaWindow winExample; //Win class

    WinFea::Init(VIDEO); //Init WinFea
    WinFea::MakeWindow(r, w, "Example", 640, 480); //Make the window

    winExample.Loop(w, r); //Render Loop

    return 0;
}