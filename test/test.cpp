#include "winfea.hpp"
#include "winfea_images.hpp"

int main(){

    render r = nullptr; //renderer variable
    win w = nullptr; //window variable

    WinFea::WinFeaWindow winExample; //Win class
    WinFeaImage image;

    WinFea::Init(VIDEO); //Init WinFea
    WinFea::MakeWindow(r, w, "Example", 1280, 720); //Make the window
    image.ShowImage(r, "../logo/WinFea-logo.png", 0, 0); //Show the image
    image.RedimensionTexture(1280, 720); //Resize the image

    WinFea::Render(winExample, image); //Register the renderable object

    winExample.Loop(w, r); //Render Loop

    return 0;
}