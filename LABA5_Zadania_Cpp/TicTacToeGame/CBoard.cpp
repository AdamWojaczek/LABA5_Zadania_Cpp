#include "CBoard.h"

CBoard::CBoard()
{
    SetSize(DEFAULT_SIZE);
}

CBoard::CBoard(int size)
{
    SetSize(size);
}

bool CBoard::SetSize(int size)
{
    bool result = false;

    if (size > 0)
    {
        m_size = size;
        m_fields.assign(m_size, std::vector<EBoardField>(m_size, EBoardField::EMPTY));
        result = true;
    }

    return result;
}

int CBoard::GetSize() const
{
    return m_size;
}

void CBoard::ClearFields()
{
    for (auto& row : m_fields)
        std::fill(row.begin(), row.end(), EBoardField::EMPTY);
}

bool CBoard::IsFull() const
{
    for (const auto& row : m_fields)
    {
        for (EBoardField field : row)
        {
            if (field == EBoardField::EMPTY)
                return false;
        }
    }

    return true;
}

bool CBoard::IsValid(int col, int row) const
{
    return (col > -1) && (col < m_size) && (row > -1) && (row < m_size);
}

bool CBoard::IsEmpty(int col, int row) const
{
    return IsValid(col, row) && (m_fields[row][col] == EBoardField::EMPTY);
}

EBoardField CBoard::GetField(int col, int row) const
{
    return IsValid(col, row) ? m_fields[row][col] : EBoardField::INVALID;
}

void CBoard::SetField(int col, int row, EBoardField symbol)
{
    if (IsEmpty(col, row) && ((symbol == EBoardField::O) || (symbol == EBoardField::X)))
        m_fields[row][col] = symbol;
}

void CBoard::ClearField(int col, int row)
{
    if (IsValid(col, row))
        m_fields[row][col] = EBoardField::EMPTY;
}

void CBoard::Display() const
{
    std::ostringstream display;
    std::string newLeftMargin = "\n    ";
    int fieldWidth = 2;

    auto drawHorizontalLine = [&]()
    {
        display << newLeftMargin;
        for (int col = 0; col < m_size; ++col)
            display << "+---";
        display << "+";
    };

    display << newLeftMargin;
    for (int col = 1; col <= m_size; ++col)
        display << " " << std::setw(fieldWidth) << col << " ";

    drawHorizontalLine();

    for (int row = 0; row < m_size; ++row)
    {
        display << "\n " << std::setw(fieldWidth) << row + 1 << " ";
        for (int col = 0; col < m_size; ++col)
            display << "| " << static_cast<char>(m_fields[row][col]) << " ";
        display << "|";

        drawHorizontalLine();
    }

    display << '\n';

    std::cout << display.str();
}

int CBoard::CountDirection(int startCol, int startRow, int dc, int dr, EBoardField symbol) const
{
    int count = 0;
    int col = startCol + dc;
    int row = startRow + dr;

    while (IsValid(col, row) && (GetField(col, row) == symbol))
    {
        count++;
        col += dc;
        row += dr;
    }

    return count;
}

bool CBoard::CheckWin(int col, int row, EBoardField symbol, int winLength) const
{
    return (CountDirection(col, row, -1,  0, symbol) + 1 + CountDirection(col, row, +1,  0, symbol) >= winLength) ||
           (CountDirection(col, row,  0, -1, symbol) + 1 + CountDirection(col, row,  0, +1, symbol) >= winLength) ||
           (CountDirection(col, row, -1, -1, symbol) + 1 + CountDirection(col, row, +1, +1, symbol) >= winLength) ||
           (CountDirection(col, row, -1, +1, symbol) + 1 + CountDirection(col, row, +1, -1, symbol) >= winLength);
}

int CBoard::GetMaxCountDirection(int col, int row, EBoardField symbol) const
{
    const int MAX_VALUES = 4;

    int values[MAX_VALUES] = {
        CountDirection(col, row, -1, 0, symbol) + CountDirection(col, row, +1, 0, symbol),
        CountDirection(col, row, 0, -1, symbol) + CountDirection(col, row, 0, +1, symbol),
        CountDirection(col, row, -1, -1, symbol) + CountDirection(col, row, +1, +1, symbol),
        CountDirection(col, row, -1, +1, symbol) + CountDirection(col, row, +1, -1, symbol)
    };

    int max = values[0];
    for (int i = 1; i < MAX_VALUES; ++i)
    {
        if (values[i] > max)
            max = values[i];
    }

    return max;
}