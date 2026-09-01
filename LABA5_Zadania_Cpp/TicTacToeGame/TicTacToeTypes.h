#pragma once

enum class EGameState : int
{
	MENU,
	CONFIG_GAME,
	CONFIG_PLAYERS,
	SWITCH_DISPLAY_BOARD_WEIGHTS,
	GAME_PVC,
	GAME_PVP,
	EXIT_GAME
};

enum class EBoardField : char
{
	INVALID = 0,
	EMPTY = ' ',
	O = 'O',
	X = 'X'
};
