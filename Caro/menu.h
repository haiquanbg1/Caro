#include <SDL.h>

enum StatusMenu
{
    nul,
    unnul,
    totalnul
};

void initTextureMenu( SDL_Renderer* gRenderer );

const SDL_Rect Rect1 = { CELL_NUMW*33+1, CELL_HEIGHT*16+1, CELL_WIDTH*6-2, CELL_HEIGHT*3-2 };
const SDL_Rect Rect2 = { CELL_NUMW*41+1, CELL_HEIGHT*16+1, CELL_WIDTH*6-2, CELL_HEIGHT*3-2 };
const SDL_Rect Rect3 = { CELL_NUMW*36+1, CELL_HEIGHT*20+1, CELL_WIDTH*8-2, CELL_HEIGHT*3-2 };

//Viết chữ lên dòng kẻ
const SDL_Rect Line = { CELL_NUMW*38, CELL_HEIGHT*10, CELL_WIDTH*4, CELL_HEIGHT };

void drawMenu( SDL_Renderer* gRenderer );

void renderMenu( SDL_Renderer* gRenderer, SDL_Texture* MenuTexture[] ,StatusMenu S1, StatusMenu S2, StatusMenu S3 );

StatusMenu eventMenu( SDL_Event* e, SDL_Rect Demo );
