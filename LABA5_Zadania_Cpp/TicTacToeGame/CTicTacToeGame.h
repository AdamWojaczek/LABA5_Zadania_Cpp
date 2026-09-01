#pragma once

#include <string>
#include <random>
#include <map>
#include "..\CIOStream.h"
#include "..\StrUtils.h"
#include "CBoard.h"
#include "CPlayer.h"

class CTicTacToeGame
{
private:
    using string = std::string;
    const int DEFAULT_SIZE{5}, MIN_SIZE{3}, MAX_SIZE{25};

    CIOStream ios;
    std::mt19937 m_generator{std::random_device{}()};

    CBoard m_board{DEFAULT_SIZE};
    CPlayer m_playerOne{"PLAYER ONE", EBoardField::O, false};
    CPlayer m_playerTwo{"PLAYER TWO", EBoardField::X, false};
    CPlayer *m_pCurrentPlayer{&m_playerOne};

    int m_winLength{DEFAULT_SIZE - 1};
    bool m_showOneStepBoardWeights{false};

    void ShowMenu();
    EGameState GetMenuAction();
    EGameState ConfigGame();    
    EGameState ConfigPlayerNames();
    EGameState SwitchDisplayBoardWeights();
    EGameState PlayGame();
    int GetBoardSize();
    int ClampSize(int size);
    int GetWinLength();
    string GetPlayerName(EBoardField symbol);    
    void SetComputerPlayer();
    void ClearComputerPlayer();
    void RenderGamePlay();
    int GetRandomValue(int min = 0, int max = 1);
    bool IsValidMove(int col, int row);
    void SetFirstPlayer();
    void SwitchPlayer();
    std::pair<int, int> GetBestColRowField() const;
    int GetFieldWeight(int col, int row, EBoardField mySymbol, EBoardField opponentSymbol) const;
    void DisplayBoardWeights() const;
    EBoardField GetOpponentSymbol() const;

public:
    CTicTacToeGame() = default;
    void Run();
};
