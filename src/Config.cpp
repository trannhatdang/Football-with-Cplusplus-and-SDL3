#include "Config.h"

const int WINDOW_WIDTH = 1120;
const int WINDOW_HEIGHT = 800;
const std::string PLAYER_FILEPATH = ".\\data\\sprites\\megaman-top.png";
const std::string PLAYER_TOP_RIGHT_FILEPATH = ".\\data\\sprites\\megaman-top-right.png";
const std::string PLAYER_TOP_DOWN_FILEPATH = ".\\data\\sprites\\megaman-top-down.png";
const std::string PLAYER_TOP_LEFT_FILEPATH = ".\\data\\sprites\\megaman-top-left.png";
const std::string PLAYER_TOP_UP_FILEPATH = ".\\data\\sprites\\megaman-top-up.png";
const std::string PLAYER_TWO_FILEPATH = ".\\data\\sprites\\megaman-two-top.png";
const std::string PLAYER_TWO_TOP_RIGHT_FILEPATH = ".\\data\\sprites\\megaman-two-top-right.png";
const std::string PLAYER_TWO_TOP_DOWN_FILEPATH = ".\\data\\sprites\\megaman-two-top-down.png";
const std::string PLAYER_TWO_TOP_LEFT_FILEPATH = ".\\data\\sprites\\megaman-two-top-left.png";
const std::string PLAYER_TWO_TOP_UP_FILEPATH = ".\\data\\sprites\\megaman-two-top-up.png";
const std::string GRASS_FILEPATH = ".\\data\\sprites\\grass-big.png";
const std::string BALL_FILEPATH = ".\\data\\sprites\\ball.png";
const std::string ARROW_SELECTED_FILEPATH = ".\\data\\sprites\\arrow-selected.png";
const std::string ARROW_UNSELECTED_FILEPATH = ".\\data\\sprites\\arrow-unselected.png";

int GetWindowWidth(){
	return WINDOW_WIDTH;
}

int GetWindowHeight(){
	return WINDOW_HEIGHT;
}

std::string GetPlayerTopdownSprite(int index)
{
	switch(index)
	{
		case 0:
			return PLAYER_TOP_RIGHT_FILEPATH;
			break;
		case 1:
			return PLAYER_TOP_DOWN_FILEPATH;
			break;
		case 2:
			return PLAYER_TOP_LEFT_FILEPATH;
			break;
		case 3:
			return PLAYER_TOP_UP_FILEPATH;
			break;
		default:
			return "";
			break;
	}
}

std::string GetPlayerTwoTopdownSprite(int index)
{
	switch(index)
	{
		case 0:
			return PLAYER_TWO_TOP_RIGHT_FILEPATH;
			break;
		case 1:
			return PLAYER_TWO_TOP_DOWN_FILEPATH;
			break;
		case 2:
			return PLAYER_TWO_TOP_LEFT_FILEPATH;
			break;
		case 3:
			return PLAYER_TWO_TOP_UP_FILEPATH;
			break;
		default:
			return "";
			break;
	}
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

std::string GetSelectedArrowSprite()
{
	return ARROW_SELECTED_FILEPATH;
}

std::string GetUnselectedArrowSprite()
{
	return ARROW_UNSELECTED_FILEPATH;
}
