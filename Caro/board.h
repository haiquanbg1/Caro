#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

//Kích thước màn hình
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 810;

//Mỗi ô
const int CELL_WIDTH = 30;
const int CELL_HEIGHT = 30;

//Số ô
const int CELL_NUMW = 30;
const int CELL_NUMH = 26;

enum Menu
{
    MenuUE,
    MenuSHITA,
    Menu1,
    Menu2,
    Menu3,
    Wingame,
    Losegame,
    Naii,
    TotalMenu
};

//Vẽ bàn cờ
void renderTable( SDL_Renderer* gRenderer );

//Tải hình ảnh
SDL_Texture* loadTexture( SDL_Renderer* gRenderer, std::string path );

//Load chữ thành hình ảnh
SDL_Texture* loadFromRenderedText( SDL_Renderer* gRenderer, std::string textureText, TTF_Font* gFont, SDL_Color textColor );
