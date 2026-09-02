#include "winfea.hpp"
#include "winfea_images.hpp"
#include "winfea_text.hpp"

int main(){

    render r = nullptr; //renderer variable
    win w = nullptr; //window variable

    WinFea::WinFeaWindow winExample; //Win class
    WinFeaImage image;

    WinFea::Init(VIDEO); //Init WinFea
    WinFea::MakeWindow(r, w, "Example", 1000, 1000); //Make the window

    image.LoadImage(r, "../logo/WinFea-logo.png", 0, 0); //Show the image
    image.RedimensionTexture(1000, 1000); //Resize the image

    WinFeaText text; //Text class
    text.LoadFont("../fonts/stocky.ttf", 48); //Load the font
    text.ShowText(r, "Hello World!", WHITE, 250, 250); //Show the text    

    WinFea::Render(winExample, image); //Register the renderable object
    WinFea::Render(winExample, text); //Register the renderable object

    winExample.Loop(w, r); //Render Loop

    return 0;
}