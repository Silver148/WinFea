/*
WinFea(Window Feather)
A lightweight framework to build light apps :).
Made by: Juan Yaguaro(aka silverhacker)
License: GPL-2.0

WinFea(Window Feather) Test
*/

#include <WinFea>

int main() {
    WinFea::Context winfea(VIDEO | AUDIO); //Init WinFea

    render r = nullptr;
    win w = nullptr;

    if (WinFea::MakeWindow(r, w, "WinFea Example", 1000, 1000) == nullptr) { //Create Window
        return -1;
    }

    /*Variables for window, image, "hello world" and music*/
    WinFea::WinFeaWindow winExample;
    WinFeaImage image;
    WinFeaText text;
    WinFeaMusic music;

    int x = 250, y = 250;

    image.LoadImage(r, "../logo/WinFea-logo.png", 0, 0); //Load Image
    image.RedimensionTexture(1000, 1000); //Redimension Image to 1000x1000px
    WinFea::Render(winExample, image); //Render Image

    text.LoadFont("../fonts/stocky.ttf", 48); //Load TTF Font with 48 size
    text.ShowText(r, "Hello World!", WHITE, x, y); //"Hello World!" with white color
    WinFea::Render(winExample, text); //Render "Hello World!"

    music.LoadMusic("../test/test.ogg"); //Load Music
    music.PlayMusic(1.0f, -1); //Play Music with loop

    WinFeaEvent events;

    events.RegisterEvent([&x, &y, &text, &winExample, &r](){
        if(WinFeaIsKeyPressed(WINFEA_KEY_UP)){
            y -= 5;
            text.ShowText(r, "Hello World!", WHITE, x, y); //"Hello World!" with white color
            WinFea::Render(winExample, text); //Render "Hello World!"
        }
        if(WinFeaIsKeyPressed(WINFEA_KEY_DOWN)){
            y += 5;
            text.ShowText(r, "Hello World!", WHITE, x, y); //"Hello World!" with white color
            WinFea::Render(winExample, text); //Render "Hello World!"
        }
        if(WinFeaIsKeyPressed(WINFEA_KEY_LEFT)){
            x -= 5;
            text.ShowText(r, "Hello World!", WHITE, x, y); //"Hello World!" with white color
            WinFea::Render(winExample, text); //Render "Hello World!"
        }
        if(WinFeaIsKeyPressed(WINFEA_KEY_RIGHT)){
            x += 5;
            text.ShowText(r, "Hello World!", WHITE, x, y); //"Hello World!" with white color
            WinFea::Render(winExample, text); //Render "Hello World!"
        }
    });


    events.RegisterEvent([&events](){
        if(WinFeaIsKeyPressed(WINFEA_KEY_ESCAPE)){
            events.SetRunning(false);
        }
    });

    winExample.Loop(w, r, &events);

    return 0;
}