#include "cell.h"
#include "board.h"
#include "menu.h"

#include <iostream>
#include <vector>
#include <algorithm>

cell Cell[ CELL_NUMW ][ CELL_NUMH ];
bool humanRound = true;

//Hình ảnh mỗi ô
SDL_Texture* CellTexture[ Total ];
//Hình ảnh mỗi Menu
SDL_Texture* MenuTexture[ TotalMenu ];

//Cửa sổ game
SDL_Window* gWindow;

//Màn hình game
SDL_Renderer* gRenderer;

//Trạng thái bàn cờ
bool x[ CELL_NUMW ][ CELL_NUMH ];
bool o[ CELL_NUMW ][ CELL_NUMH ];

typedef std::pair< int, int > ii;
std::vector < ii > xx, oo;

bool Endgame = false;

//Khởi tạo trạng thái bàn cờ
void initBoard()
{
    gWindow = NULL;
    gRenderer = NULL;

    for( int i=0; i<CELL_NUMW; i++ )
    {
        for( int j=0; j<CELL_NUMH; j++ )
        {
            x[i][j] = 0;
            o[i][j] = 0;
        }
    }
}

void initTexture( SDL_Texture* CellTexture[] )
{
    CellTexture[ Default ] = NULL;
    CellTexture[ Mousemotion ] = loadTexture( gRenderer, "Mousemotion.png");

    //Font chữ XO
	TTF_Font* gFont = TTF_OpenFont( "Menu.ttf", 48 );

	//Màu X
	SDL_Color XColor = { 223, 0, 0 };
    CellTexture[ X ] = loadFromRenderedText( gRenderer, "X", gFont, XColor );

    //Màu O
    SDL_Color OColor = { 0, 223, 0 };
    CellTexture[ O ] = loadFromRenderedText( gRenderer, "O", gFont, OColor );

    for( int i=1; i<CELL_NUMW; i++ )
    {
        for( int j=1; j<CELL_NUMH; j++ )
        {
            int positionX = CELL_WIDTH*i ;
            int positionY = CELL_HEIGHT*j ;
            Cell[ i ][ j ].setPosition( positionX, positionY );
        }
    }
}

void initText()
{
    //Font chữ
	TTF_Font* gFont = TTF_OpenFont( "Menu.ttf", 200 );

	//Màu chữ
	SDL_Color textColor1 = { 70, 70, 70 };
	//Menu trên
	MenuTexture[ MenuUE ] = loadFromRenderedText( gRenderer, "Caro", gFont, textColor1 );

	//Màu chữ
	SDL_Color textColor2 = { 0, 66, 99 };
	//Menu dưới
	MenuTexture[ MenuSHITA ] = loadFromRenderedText( gRenderer, "Menu", gFont, textColor2 );

	//Màu chữ
	SDL_Color textColor3 = { 0, 66, 99 };
	//Menu trái
	MenuTexture[ Menu1 ] = loadFromRenderedText( gRenderer, "New Game", gFont, textColor3 );

	//Màu chữ
	SDL_Color textColor4 = { 0, 66, 99 };
	//Menu phải
	MenuTexture[ Menu2 ] = loadFromRenderedText( gRenderer, "Exit", gFont, textColor4 );

	//Màu chữ
	SDL_Color textColor5 = { 0, 66, 99 };
	//Menu dưới dưới
	MenuTexture[ Menu3 ] = loadFromRenderedText( gRenderer, "Move Back", gFont, textColor5 );

	//Màu chữ
	SDL_Color textColor6 = { 0, 100, 100 };
	//Win
	MenuTexture[ Wingame ] = loadFromRenderedText( gRenderer, "X Win!", gFont, textColor6 );
	//Lose
	MenuTexture[ Losegame ] = loadFromRenderedText( gRenderer, "O Win!", gFont, textColor6 );
	//Không có gì
	MenuTexture[ Naii ] = NULL;
}

void initWindow()
{
    //Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Caro", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				}

                //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
				}
			}
		}
	}
}

void close()
{
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Newgame()
{
    for( int i=0; i<CELL_NUMW; i++ )
    {
        for( int j=0; j<CELL_NUMH; j++ )
        {
            x[i][j] = 0;
            o[i][j] = 0;
        }
    }

    for( int i=0; i<CELL_NUMW; i++ )
    {
        for( int j=0; j<CELL_NUMH; j++ )
        {
            Cell[ i ][ j ].initCell();
        }
    }

    xx.clear();
    oo.clear();

    humanRound = true;
    Endgame = false;
}

void Moveback()
{
    if( !humanRound )
    {
        if( xx.empty() )
            return;

        ii Backx = xx.back();
        x[ Backx.first ][ Backx.second ] = 0;
        Cell[ Backx.first ][ Backx.second ].initCell();
        xx.pop_back();
        humanRound = true;
    }
    else
    {
        if( oo.empty() )
            return;

        ii Backo = oo.back();
        o[ Backo.first ][ Backo.second ] = 0;
        Cell[ Backo.first ][ Backo.second ].initCell();
        oo.pop_back();
        humanRound = false;
    }
}

bool CheckX( int u, int v )
{
    //Dọc
    for(int i=u; i<u+5; i++)
    {
        bool ok = true;
        for(int j=v; j<v+5; j++)
        if( !x[i][j] )
        {
            ok = false;
            break;
        }
        if( ok )
            return 1;
    }
    //Ngang
    for(int j=u; j<u+5; j++)
    {
        bool ok = true;
        for(int i=v; i<v+5; i++)
        if( !x[i][j] )
        {
            ok = false;
            break;
        }
        if( ok )
            return 1;
    }
    //Chéo
    bool ok = true;
    for(int i=1; i<=5; i++)
    {
        if( !x[u+i-1][v+i-1] )
        {
            ok = false;
            break;
        }
    }
    if( ok )
        return 1;
    ok = true;
    for(int i=1; i<=5; i++)
    {
        if( !x[u+i-1][v+5-i] )
        {
            ok = false;
            break;
        }
    }
    if( ok )
        return 1;
    return 0;
}

bool CheckO( int u, int v )
{
    //Dọc
    for(int i=u; i<u+5; i++)
    {
        bool ok = true;
        for(int j=v; j<v+5; j++)
        if( !o[i][j] )
        {
            ok = false;
            break;
        }
        if( ok )
            return 1;
    }
    //Ngang
    for(int j=u; j<u+5; j++)
    {
        bool ok = true;
        for(int i=v; i<v+5; i++)
        if( !o[i][j] )
        {
            ok = false;
            break;
        }
        if( ok )
            return 1;
    }
    //Chéo
    bool ok = true;
    for(int i=1; i<=5; i++)
    {
        if( !o[u+i-1][v+i-1] )
        {
            ok = false;
            break;
        }
    }
    if( ok )
        return 1;
    ok = true;
    for(int i=1; i<=5; i++)
    {
        if( !o[u+i-1][v+5-i] )
        {
            ok = false;
            break;
        }
    }
    if( ok )
        return 1;
    return 0;
}

bool CheckBoard( bool X )
{
    for(int i=1; i<=CELL_NUMW-5; i++)
    {
        for(int j=1; j<=CELL_NUMH-5; j++)
        {
            bool ok = false;
            if( X )
                ok = CheckX( i, j );
            else
                ok = CheckO( i, j );
            if( ok )
                return 1;
        }
    }
    return 0;
}

int main(int argc, char** args)
{
    //Khởi tạo mọi thứ
    initBoard();
    initWindow();
    initTexture( CellTexture );
    initText();
    initTextureMenu( gRenderer );

    bool quit = false;
    SDL_Event e;

    StatusMenu S1, S2, S3;
    Menu game = Naii;

    while( !quit )
    {
        if( S3 == totalnul )
            S3 = nul;

        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else
            {
                if( !Endgame )
                {
                    for(int i=0; i<CELL_NUMW; i++)
                    {
                        for(int j=0; j<CELL_NUMH; j++)
                        {
                            Cell[ i ][ j ].handleEvent( &e, humanRound );

                            Status sta = Cell[ i ][ j ].getEvent();
                            if( sta == X && x[ i ][ j ] == false )
                            {
                                x[ i ][ j ] = true;
                                xx.push_back( {i, j} );
                            }
                            else if( sta == O && o[ i ][ j ] == false )
                            {
                                o[ i ][ j ] = true;
                                oo.push_back( {i, j} );
                            }
                        }
                    }
                }
                S1 = eventMenu( &e, Rect1 );
                S2 = eventMenu( &e, Rect2 );
                S3 = eventMenu( &e, Rect3 );
            }
        }

        if( S3 == totalnul && !Endgame )
        {
            Moveback();
        }
        if( S1 == totalnul )
        {
            Newgame();
        }
        if( S2 == totalnul )
        {
            quit = true;
        }

        if( CheckBoard(1) )
        {
            game = Wingame;
        }
        else
            if( CheckBoard(0) )
        {
            game = Losegame;
        }
        else
        {
            game = Naii;
        }

        //Xoá màn hình cũ
        SDL_SetRenderDrawColor( gRenderer, 0x36, 0x36, 0x36, 0 );
        SDL_RenderClear( gRenderer );

        //Vẽ cái bàn
        renderTable( gRenderer );

        //Vẽ cái menu
        drawMenu( gRenderer );
        renderMenu( gRenderer, MenuTexture, S1, S2, S3 );
        //Viết trạng thái game
        SDL_RenderCopy( gRenderer, MenuTexture[ game ], NULL, &Line );

        //Vẽ mỗi ô
        for(int x=0; x<CELL_NUMW; x++)
        {
            for(int y=0; y<CELL_NUMH; y++)
            {
                Cell[ x ][ y ].render( CellTexture, gRenderer );
            }
        }

        //Cập nhật màn hình
        SDL_RenderPresent( gRenderer );

        if( game == Wingame || game == Losegame )
        {
            Endgame = true;
        }
    }
    close();
}
