#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "TicTacToeTypes.h"

class CBoard
{
private:
    const int DEFAULT_SIZE{5};

    int m_size{DEFAULT_SIZE};
    std::vector<std::vector<EBoardField>> m_fields;

public:
    CBoard();
    explicit CBoard(int size);

    int GetSize() const;
    bool SetSize(int size);
    void ClearFields();
    bool IsFull() const;   
    bool IsValid(int col, int row) const;
    bool IsEmpty(int col, int row) const;
    EBoardField GetField(int col, int row) const;
    void SetField(int col, int row, EBoardField symbol);
    void ClearField(int col, int row);
    void Display() const;
    int CountDirection(int startCol, int startRow, int dc, int dr, EBoardField symbol) const;
    bool CheckWin(int col, int row, EBoardField symbol, int winLength) const;
    int GetMaxCountDirection(int col, int row, EBoardField symbol) const;
};


