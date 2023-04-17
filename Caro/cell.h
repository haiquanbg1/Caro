#include <SDL.h>
#include <SDL_image.h>

//Trạng thái ô
enum Status{
    Default,
    Mousemotion,
    X,
    O,
    Total
};

class cell
{
    public:

        //Khởi tạo ô
        cell();

        //Khởi tạo lại ô
        void initCell();

        //Khởi tạo vị trí ô
        void setPosition( int x, int y );

        //Kiểm tra Event
        void handleEvent( SDL_Event* e, bool& humanRound );

        //Vẽ ô theo Event
        void render( SDL_Texture* CellTexture[], SDL_Renderer* gRenderer );

        //Lấy Event hiện tại
        Status getEvent();

    private:

        //Trạng thái ô
        Status currentEvent;

        //Vị trí ô
        SDL_Point Pos;
};
