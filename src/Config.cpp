#include "Config.h"

const int WINDOW_WIDTH = 1120;
const int WINDOW_HEIGHT = 160*5;
const std::string PLAYER_FILEPATH = "D:\\DH\\HK252\\FIFA_CLONE (Visual Studio)\\sprites\\megaman-left.png";
const std::string GRASS_FILEPATH = "D:\\DH\\HK252\\FIFA_CLONE (Visual Studio)\\sprites\\grass-big.png";

int GetWindowWidth(){
	return WINDOW_WIDTH;
}

int GetWindowHeight(){
	return WINDOW_HEIGHT;
}

std::string GetPlayerSpriteSheet()
{
	return PLAYER_FILEPATH;
}

std::string GetGrassSpriteSheet()
{
	return GRASS_FILEPATH;
}
