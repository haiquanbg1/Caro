#ifndef SDLSUPPORT_H
#define SDLSUPPORT_H

#include <iostream>
#include "SDL_mixer.h"

using namespace std;

SDL_Texture* loadMedia(SDL_Renderer* Renderer, string path){
    SDL_Texture* gTexture;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str());
    if( loadedSurface == NULL ){
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else{
//        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
        gTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
        if( gTexture == NULL ){
        printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        SDL_FreeSurface( loadedSurface );
    }
    return gTexture;
}


void RenderMedia(SDL_Renderer* renderer, SDL_Texture* gTexture, int topX, int topY, int width, int height){
    SDL_Rect Dest;
    Dest.x = topX + 1;
    Dest.y = topY + 1;
    Dest.w = width - 1;
    Dest.h = height - 1;
    SDL_RenderCopy( renderer, gTexture, NULL, &Dest );
}

void logSDLError(std::ostream& os, const std::string &msg, bool fatal){
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, string WINDOW_TITLE){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi th�ng thu?ng ch?y v?i m�i tru?ng b�nh thu?ng ? nh�
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                          SDL_RENDERER_PRESENTVSYNC);
    //Khi ch?y ? m�y th?c h�nh WinXP ? tru?ng (m�y ?o)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
}


void quitSDL(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* dataImage[20][20];
Mix_Chunk* dataChunk[10];
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
static const string WINDOW_TITLE = "CARO";

enum typeOfImage
{
    ENTER_PREGAME,
    CHOICE_MAP_PREGAME,
    CHOICE_MAP_SUCCESS_PREGAME,
    SQUARE_GAME,
    SQUARE_GAME_HAVEPLAYED,
    RESTART_GAME,
    RETURN_MENU_GAME,
    CHOICE_PLAYER_AI_PREGAME,
    CHOICE_PLAYER_AI_SUCCESS_PREGAME,
    CHOOSE_AI_PREGAME,
    CHOOSE_MAP_PREGAME,
    HEADING_PREGAME,
    PAUSE_GAME,
    BULLETIN_BOARD_PREGAME,
    ENDGAME_GAME,
    CHOICE_LEVEL_PREGAME,
    CHOICE_LEVEL_SUCCESS_PREGAME,
    SOUND_PREGAME,
};

enum stateOfBULLETINBOARD {
    EMPTY,
    NOT_CHOOSE_PLAYER_AND_MAP,
    NOT_CHOOSE_PLAYER,
    NOT_CHOOSE_MAP,
    CAN_NOT_PLAY_MAP1212_WITH_AI,
    CAN_NOT_PLAY_MAP55_WITH_AI,
    YOUR_TURN,
    AI_TURN,
    PLAYER1_TURN,
    PLAYER2_TURN,
    ENDGAME,
    ENDGAME_ADMIT_LOSE,
    NOT_CHOOSE_LEVEL
};

enum stateOfEndGameBULLETINBOARD {
    YOU_WIN,
    YOU_LOSE,
    DRAW,
    PLAYER1_WIN,
    PLAYER2_WIN
};

enum stateOfaSquare {
    STATE_EMPTY,
    STATE_PLAYER,
    STATE_AI
};

enum stateButtonMap {
    NOT_CHOOSE,
    MAP_33,
    MAP_55,
    MAP_99,
    MAP_1212
};

enum stateOfPlayer {
    NOT_ENDGAME,
    FIRST_PLAYER,
    SECOND_PLAYER,
    TWO_PLAYER_DRAW,
};
enum stateChunk {
    CLICK,
    ENDGAME_MUSIC,
    ERROR
};
enum stateLevelGame {
    NOT_HAVE_ANYTHING,
    EASY,
    MEDIUM,
    HARD
};
enum stateOfSound {
    NULLLLLL,
    ON,
    OFF,
};
enum sizeOfSomething {
    SIZE_OF_CHOICE_PLAYER_AI = 2,
    SIZE_OF_CHOICE_LEVEL = 3,
    SIZE_OF_CHOICE_MAP = 4
};
void setData(SDL_Renderer* renderer){

    dataImage[ENTER_PREGAME][1] = loadMedia(renderer , "pictures/EnterGameButton.png");
    dataImage[CHOICE_MAP_PREGAME][MAP_33] = loadMedia(renderer , "pictures/choice33.png");
    dataImage[CHOICE_MAP_PREGAME][MAP_55] = loadMedia(renderer , "pictures/choice55.png");
    dataImage[CHOICE_MAP_PREGAME][MAP_99] = loadMedia(renderer , "pictures/choice99.png");
    dataImage[CHOICE_MAP_PREGAME][MAP_1212] = loadMedia(renderer , "pictures/choice1212.png");
    dataImage[CHOICE_MAP_SUCCESS_PREGAME][MAP_33] = loadMedia(renderer , "pictures/choice33success.png");
    dataImage[CHOICE_MAP_SUCCESS_PREGAME][MAP_55] = loadMedia(renderer , "pictures/choice55success.png");
    dataImage[CHOICE_MAP_SUCCESS_PREGAME][MAP_99] = loadMedia(renderer , "pictures/choice99success.png");
    dataImage[CHOICE_MAP_SUCCESS_PREGAME][MAP_1212] = loadMedia(renderer , "pictures/choice1212success.png");
    dataImage[CHOICE_PLAYER_AI_SUCCESS_PREGAME][STATE_PLAYER] = loadMedia(renderer , "pictures/choicePlayPlayerSuccess.png");
    dataImage[CHOICE_PLAYER_AI_SUCCESS_PREGAME][STATE_AI] = loadMedia(renderer , "pictures/choicePlayAISuccess.png");
    dataImage[CHOICE_PLAYER_AI_PREGAME][STATE_PLAYER] = loadMedia(renderer , "pictures/choicePlayPlayer.png");
    dataImage[CHOICE_PLAYER_AI_PREGAME][STATE_AI] = loadMedia(renderer , "pictures/choicePlayAI.png");
    dataImage[SQUARE_GAME][FIRST_PLAYER] = loadMedia(renderer , "pictures/player1_X.png");
    dataImage[SQUARE_GAME][SECOND_PLAYER] = loadMedia(renderer , "pictures/player2_O.png");
    dataImage[SQUARE_GAME_HAVEPLAYED][FIRST_PLAYER] = loadMedia(renderer , "pictures/player1_X_havePlayed.png");
    dataImage[SQUARE_GAME_HAVEPLAYED][SECOND_PLAYER] = loadMedia(renderer , "pictures/player2_O_havePlayed.png");
    dataImage[RESTART_GAME][1] = loadMedia(renderer, "pictures/RestartGame.png");
    dataImage[RETURN_MENU_GAME][1] = loadMedia(renderer, "pictures/returnMenu.png");
    dataImage[CHOOSE_AI_PREGAME][1] = loadMedia(renderer, "pictures/chooseAI.png");
    dataImage[CHOOSE_MAP_PREGAME][1] = loadMedia(renderer, "pictures/chooseMap.png");
    dataImage[HEADING_PREGAME][1] = loadMedia(renderer, "pictures/heading.png");
    dataImage[BULLETIN_BOARD_PREGAME][EMPTY] = loadMedia(renderer, "pictures/bulletinBoard.png");
    dataImage[BULLETIN_BOARD_PREGAME][NOT_CHOOSE_PLAYER_AND_MAP] = loadMedia(renderer, "pictures/bulletinBoard_chooseAIandMap.png");
    dataImage[BULLETIN_BOARD_PREGAME][NOT_CHOOSE_PLAYER] = loadMedia(renderer, "pictures/bulletinBoard_chooseAI.png");
    dataImage[BULLETIN_BOARD_PREGAME][NOT_CHOOSE_MAP] = loadMedia(renderer, "pictures/bulletinBoard_chooseMap.png");
    dataImage[BULLETIN_BOARD_PREGAME][CAN_NOT_PLAY_MAP1212_WITH_AI] = loadMedia(renderer, "pictures/bulletinBoard_notSupportAIwith1212.png");
    dataImage[BULLETIN_BOARD_PREGAME][CAN_NOT_PLAY_MAP55_WITH_AI] = loadMedia(renderer, "pictures/bulletinBoard_notSupportAIwith55.png");
    dataImage[BULLETIN_BOARD_PREGAME][YOUR_TURN] = loadMedia(renderer, "pictures/bulletinBoard_yourTurn.png");
    dataImage[BULLETIN_BOARD_PREGAME][AI_TURN] = loadMedia(renderer, "pictures/bulletinBoard_AIturn.png");
    dataImage[BULLETIN_BOARD_PREGAME][PLAYER1_TURN] = loadMedia(renderer, "pictures/bulletinBoard_turnPlayer1.png");
    dataImage[BULLETIN_BOARD_PREGAME][PLAYER2_TURN] = loadMedia(renderer, "pictures/bulletinBoard_turnPlayer2.png");
    dataImage[BULLETIN_BOARD_PREGAME][ENDGAME] = loadMedia(renderer, "pictures/bulletinBoard_endGame.png");
    dataImage[BULLETIN_BOARD_PREGAME][ENDGAME_ADMIT_LOSE] = loadMedia(renderer, "pictures/bulletinBoard_endGameAdmit.png");
    dataImage[BULLETIN_BOARD_PREGAME][NOT_CHOOSE_LEVEL] = loadMedia(renderer, "pictures/bulletinBoard_chooseLevel.png");
    dataImage[ENDGAME_GAME][YOU_WIN] = loadMedia(renderer, "pictures/bulletinBoard_youWin.png");
    dataImage[ENDGAME_GAME][YOU_LOSE] = loadMedia(renderer, "pictures/bulletinBoard_youLose.png");
    dataImage[ENDGAME_GAME][DRAW] = loadMedia(renderer, "pictures/bulletinBoard_draw.png");
    dataImage[ENDGAME_GAME][PLAYER1_WIN] = loadMedia(renderer, "pictures/bulletinBoard_player1win.png");
    dataImage[ENDGAME_GAME][PLAYER2_WIN] = loadMedia(renderer, "pictures/bulletinBoard_player2win.png");
    dataImage[CHOICE_LEVEL_PREGAME][EASY] = loadMedia(renderer, "pictures/choiceLevelEasy.png");
    dataImage[CHOICE_LEVEL_PREGAME][MEDIUM] = loadMedia(renderer, "pictures/choiceLevelMedium.png");
    dataImage[CHOICE_LEVEL_PREGAME][HARD] = loadMedia(renderer, "pictures/choiceLevelHard.png");
    dataImage[CHOICE_LEVEL_SUCCESS_PREGAME][EASY] = loadMedia(renderer, "pictures/choiceLevelEasy_success.png");
    dataImage[CHOICE_LEVEL_SUCCESS_PREGAME][MEDIUM] = loadMedia(renderer, "pictures/choiceLevelMedium_success.png");
    dataImage[CHOICE_LEVEL_SUCCESS_PREGAME][HARD] = loadMedia(renderer, "pictures/choiceLevelHard_success.png");
    dataImage[SOUND_PREGAME][ON] = loadMedia(renderer, "pictures/sound_on.png");
    dataImage[SOUND_PREGAME][OFF] = loadMedia(renderer, "pictures/sound_off.png");

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1){
        printf("%s", Mix_GetError());
    }
    dataChunk[CLICK] = Mix_LoadWAV("sounds/click.wav");
    dataChunk[ENDGAME_MUSIC] = Mix_LoadWAV("sounds/endGame.wav");
    dataChunk[ERROR] = Mix_LoadWAV("sounds/error.wav");

}

#endif


