#include "Config.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const std::string PLAYER_FILEPATH = "D:\\DH\\HK252\\FIFA_CLONE (Visual Studio)\\sprites\\megaman-left.png";

const int GetWindowWidth(){
	return WINDOW_WIDTH;
}

const int GetWindowHeight(){
	return WINDOW_HEIGHT;
}

const std::string GetPlayerSpriteSheet()
{
	return PLAYER_FILEPATH;
}
