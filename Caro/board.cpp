#include "board.h"

void renderTable( SDL_Renderer* gRenderer )
{
    //Vẽ background bàn:
    //Rect cái bàn
    SDL_Rect TableRect = { CELL_WIDTH-1, CELL_HEIGHT-1, SCREEN_WIDTH - CELL_WIDTH*21, SCREEN_HEIGHT - CELL_HEIGHT*2 };
    //Màu background
    SDL_SetRenderDrawColor( gRenderer, 0x55, 0x55, 0x55, 0xFF );
    //Vẽ background
    SDL_RenderFillRect( gRenderer, &TableRect );

    //Vẽ bàn:
    //Màu của bàn
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF );
    for( int i=1; i<=CELL_NUMW; i++ )
    {
        //Vẽ cột
        SDL_RenderDrawLine( gRenderer, CELL_WIDTH*i-1, CELL_HEIGHT - 1, CELL_WIDTH*i-1, SCREEN_HEIGHT - CELL_HEIGHT - 1 );
    }
    for( int i=1; i<=CELL_NUMH; i++ )
    {
        //Vẽ hàng
        SDL_RenderDrawLine( gRenderer, CELL_WIDTH - 1, CELL_HEIGHT*i-1, CELL_NUMW*30 - 1, CELL_HEIGHT*i-1 );
    }
}

SDL_Texture* loadTexture( SDL_Renderer* gRenderer, std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

	SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );

	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

//Load chữ ra hình ảnh
SDL_Texture* loadFromRenderedText( SDL_Renderer* gRenderer, std::string textureText, TTF_Font* gFont, SDL_Color textColor )
{
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        SDL_Texture* mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
		//Return success
        return mTexture;
	}
}
