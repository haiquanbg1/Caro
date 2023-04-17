#include "cell.h"
#include "board.h"
#include <iostream>

cell::cell()
{
    currentEvent = Default;
    //Không cho ấn
    Pos.x = -1000;
    Pos.y = -1000;
}

void cell::initCell()
{
    currentEvent = Default;
}

void cell::setPosition( int x, int y )
{
    Pos.x = x;
    Pos.y = y;
}

void cell::handleEvent( SDL_Event* e, bool& humanRound)
{
        //If mouse event happened
        if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN )
        {
            //Get mouse position
            int x, y;
            SDL_GetMouseState( &x, &y );

            //Check if mouse is in button
            bool inside = true;

            //Mouse is left of the button
            if( x < Pos.x )
            {
                inside = false;
            }
            //Mouse is right of the button
            else if( x > Pos.x + CELL_WIDTH )
            {
                inside = false;
            }
            //Mouse above the button
            else if( y < Pos.y )
            {
                inside = false;
            }
            //Mouse below the button
            else if( y > Pos.y + CELL_HEIGHT )
            {
                inside = false;
            }

            //Mouse is outside button
            if( !inside )
            {
                if(currentEvent == Mousemotion)
                {
                    currentEvent = Default;
                }
            }
            //Mouse is inside button
            else
            {
                //Set mouse over sprite
                if( currentEvent == Default || currentEvent == Mousemotion )
                    switch( e->type )
                    {
                        case SDL_MOUSEMOTION:
                        {
                            currentEvent = Mousemotion;
                            break;
                        }

                        case SDL_MOUSEBUTTONDOWN:
                        {
                            if( humanRound )
                            {
                                currentEvent = X;
                                humanRound = false;
                            }
                            else
                            {
                                currentEvent = O;
                                humanRound = true;
                            }
                            break;
                        }
                    }
            }
        }
}

void cell::render( SDL_Texture* CellTexture[], SDL_Renderer* gRenderer )
{
    SDL_Rect rect;
    if( currentEvent == Mousemotion )
        rect = { Pos.x, Pos.y, CELL_WIDTH-1, CELL_HEIGHT-1 };
    else
        rect = { Pos.x+3, Pos.y+4, CELL_WIDTH-6, CELL_HEIGHT-6 };
    SDL_RenderCopy( gRenderer, CellTexture[ currentEvent ], NULL, &rect );
}

Status cell::getEvent()
{
    return currentEvent;
}

