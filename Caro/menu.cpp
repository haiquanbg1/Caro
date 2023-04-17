#include "board.h"
#include "menu.h"

void drawMenu( SDL_Renderer* gRenderer )
{
    //Vẽ menu:
    //Rect cái menu
    SDL_Rect MenuRect = { CELL_NUMW*32, CELL_HEIGHT, CELL_WIDTH*16, CELL_HEIGHT*25 - 1 };
    //Màu menu
    SDL_SetRenderDrawColor( gRenderer, 0xCC, 0xCC, 0x99, 0xFF );
    //Vẽ menu
    SDL_RenderFillRect( gRenderer, &MenuRect );

    SDL_SetRenderDrawColor( gRenderer, 0, 0x99, 0x99, 0xFF );
    //Dòng kẻ ngăn cách 2 Menu
    SDL_RenderDrawLine( gRenderer, CELL_NUMW*33, CELL_HEIGHT*11, CELL_NUMW*47, CELL_HEIGHT*11 );

    //Vẽ ô vuông trong Menu
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );

    SDL_Rect MENU1 = { CELL_NUMW*33, CELL_HEIGHT*16, CELL_WIDTH*6, CELL_HEIGHT*3 };
    SDL_RenderDrawRect( gRenderer, &MENU1 );

    SDL_Rect MENU2 = { CELL_NUMW*41, CELL_HEIGHT*16, CELL_WIDTH*6, CELL_HEIGHT*3 };
    SDL_RenderDrawRect( gRenderer, &MENU2 );

    SDL_Rect MENU3 = { CELL_NUMW*36, CELL_HEIGHT*20, CELL_WIDTH*8, CELL_HEIGHT*3 };
    SDL_RenderDrawRect( gRenderer, &MENU3 );
}

//Rect cái Menu trên
    SDL_Rect MenuUERect = { CELL_NUMW*34, CELL_HEIGHT*3, CELL_WIDTH*12, CELL_WIDTH*6 };
//Rect cái Menu dưới
    SDL_Rect MenuSHITARect = { CELL_NUMW*37, CELL_HEIGHT*12, CELL_WIDTH*6, CELL_HEIGHT*3 };
//Viết chữ vào 3 ô vuông
    SDL_Rect RectMenu1 = { CELL_NUMW*34 - 5, CELL_HEIGHT*17, CELL_WIDTH*4 + 10, CELL_HEIGHT };
    SDL_Rect RectMenu2 = { CELL_NUMW*43, CELL_HEIGHT*17, CELL_WIDTH*2, CELL_HEIGHT };
    SDL_Rect RectMenu3 = { CELL_NUMW*38 - 5, CELL_HEIGHT*21, CELL_WIDTH*4 + 10, CELL_HEIGHT };

//Hình ảnh trên ô menu
SDL_Texture* Menuleft[ totalnul ];
SDL_Texture* Menuright[ totalnul ];
SDL_Texture* Menubottom[ totalnul ];

void initTextureMenu( SDL_Renderer* gRenderer )
{
    Menuleft[ nul ] = NULL;
    Menuleft[ unnul ] = loadTexture( gRenderer, "Mousemotion.png" );
    Menuleft[ totalnul ] = NULL;

    Menuright[ nul ] = NULL;
    Menuright[ unnul ] = loadTexture( gRenderer, "Mousemotion.png" );
    Menuright[ totalnul ] = NULL;

    Menubottom[ nul ] = NULL;
    Menubottom[ unnul ] = loadTexture( gRenderer, "Mousemotion.png" );
    Menubottom[ totalnul ] = loadTexture( gRenderer, "Mousemotion.png" );
}

void renderMenu( SDL_Renderer* gRenderer, SDL_Texture* MenuTexture[], StatusMenu S1, StatusMenu S2, StatusMenu S3 )
{
    //Vẽ Menu trên
    SDL_RenderCopy( gRenderer, MenuTexture[ MenuUE ], NULL, &MenuUERect );

    //Vẽ Menu dưới
    SDL_RenderCopy( gRenderer, MenuTexture[ MenuSHITA ], NULL, &MenuSHITARect );

    //render hình lên Menu
    SDL_RenderCopy( gRenderer, Menuleft[ S1 ], NULL, &Rect1 );
    SDL_RenderCopy( gRenderer, Menuright[ S2 ], NULL, &Rect2 );
    SDL_RenderCopy( gRenderer, Menubottom[ S3 ], NULL, &Rect3 );

    //Viết chữ vào 2 ô
    SDL_RenderCopy( gRenderer, MenuTexture[ Menu1 ], NULL, &RectMenu1 );//trái
    SDL_RenderCopy( gRenderer, MenuTexture[ Menu2 ], NULL, &RectMenu2 );//phải
    SDL_RenderCopy( gRenderer, MenuTexture[ Menu3 ], NULL, &RectMenu3 );//dưới

    //
}

StatusMenu eventMenu( SDL_Event* e, SDL_Rect Demo )
{
    StatusMenu ans;
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if( x < Demo.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > Demo.x + Demo.w )
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < Demo.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > Demo.y + Demo.h )
        {
            inside = false;
        }

        //Mouse is outside button
        if( !inside )
        {
            ans = nul;
        }
        //Mouse is inside button
        else
        {
                switch( e->type )
                {
                    case SDL_MOUSEMOTION:
                    {
                        ans = unnul;
                        break;
                    }

                    case SDL_MOUSEBUTTONDOWN:
                    {
                        ans = totalnul;
                        break;
                    }
                }
            }
        }
        return ans;
}
