#include "Config.h"

const int WINDOW_WIDTH = 1120;
const int WINDOW_HEIGHT = 800;
const std::string PLAYER_FILEPATH = "D:\\DH\\HK252\\FIFA_CLONE (Visual Studio)\\sprites\\megaman-top.png";
const std::string PLAYER_TWO_FILEPATH = "D:\\DH\\HK252\\FIFA_CLONE (Visual Studio)\\sprites\\megaman-top-2.png";
const std::string GRASS_FILEPATH = "D:\\DH\\HK252\\FIFA_CLONE (Visual Studio)\\sprites\\grass-big.png";
const std::string BALL_FILEPATH = "D:\\DH\\HK252\\FIFA_CLONE (Visual Studio)\\sprites\\ball.png";

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

std::string GetPlayerTwoSpriteSheet()
{
	return PLAYER_TWO_FILEPATH;
}

std::string GetGrassSpriteSheet()
{
	return GRASS_FILEPATH;
}

std::string GetBallSprite()
{
	return BALL_FILEPATH;
}
