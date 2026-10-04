#include "CLifeBoard.h"

#include <iostream>
#include <cstddef>
#include <sstream>

//---------------------------------------------------------------------------------------------------------------------

bool CLifeBoard::Initialize(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;

    m_cells.assign(m_height, vector<CLifeCell>(m_width));
    m_nextCells = m_cells;

    return (m_cells.size() == m_height) && (m_cells.size() == m_nextCells.size());
}

//---------------------------------------------------------------------------------------------------------------------

bool CLifeBoard::SetInitialState(const vector<string>& state)
{
    bool error = false;

    if (state.size() != m_height)
        error = true;
    else
    {
        for (unsigned int y = 0; (y < m_height) && !error; ++y)
        {
            if (state[y].length() != m_width)
                error = true;
            else
            {
                for (unsigned int x = 0; (x < m_width) && !error; ++x)
                {
                    if (state[y][x] == DEAD_CELL_INIT_SET)
                        m_cells[y][x].SetDead();
                    else if (state[y][x] == LIVE_CELL_INIT_SET)
                        m_cells[y][x].SetAlive();
                    else
                        error = true;
                }
            }
        }
    }
    
    return !error;
}

//---------------------------------------------------------------------------------------------------------------------

bool CLifeBoard::SetDisplayCharacters(const string& deadCell, const string& liveCell)
{
    m_deadCell = deadCell;
    m_liveCell = liveCell;

    if (m_deadCell.length() != m_liveCell.length())
    {
        if (m_deadCell.length() < m_liveCell.length())
            m_deadCell.append(m_liveCell.length() - m_deadCell.length(), ' ');
        else if (m_liveCell.length() < m_deadCell.length())
            m_liveCell.append(m_deadCell.length() - m_liveCell.length(), ' ');
    }

    return (m_deadCell != m_liveCell);
}

//---------------------------------------------------------------------------------------------------------------------

void CLifeBoard::NextGeneration()
{
    for (unsigned int y = 0; y < m_height; ++y)
    {
        for (unsigned int x = 0; x < m_width; ++x)
        {
            const unsigned int neighbours = CountAliveNeighbours(x, y);
            const bool alive = m_cells[y][x].IsAlive();
            bool nextAlive;

            if (alive)
                nextAlive = (neighbours == 2) || (neighbours == 3);
            else
                nextAlive = (neighbours == 3);

            nextAlive ? m_nextCells[y][x].SetAlive() : m_nextCells[y][x].SetDead();
        }
    }

    m_cells.swap(m_nextCells);      // fastest approach, m_nextCells state is no longer relevant in this turn
}

//---------------------------------------------------------------------------------------------------------------------

void CLifeBoard::Display() const
{
    std::ostringstream buffer;
    string separator(GetDispltWidth(), '-');

    buffer << " " << separator << " " << std::endl;
    for (unsigned int y = 0; y < m_height; ++y)
    {
        buffer << "|";
        for (unsigned int x = 0; x < m_width; ++x)
            buffer << (m_cells[y][x].IsAlive() ? m_liveCell : m_deadCell);

        buffer << "|" << std::endl;
    }
    buffer << " " << separator << " " << std::endl;

    std::cout << buffer.str();
}

//---------------------------------------------------------------------------------------------------------------------

unsigned int CLifeBoard::GetDispltWidth() const
{
    return m_width * static_cast<unsigned int>(m_deadCell.length());
}

//---------------------------------------------------------------------------------------------------------------------

unsigned int CLifeBoard::CountAliveNeighbours(unsigned int x, unsigned int y) const
{
    unsigned int count = 0;
    const int MAX_X = static_cast<int>(m_width), MAX_Y = static_cast<int>(m_height);
    const int X = static_cast<int>(x), Y = static_cast<int>(y);

    for (int offY = -1; offY < 2; ++offY)
    {
        for (int offX = -1; offX < 2; ++offX)
        {
            if ((offX == 0) && (offY == 0))
                continue;
            else
            {
                const int neighbourX = X + offX;
                const int neighbourY = Y + offY;

                if ((neighbourX > -1) && (neighbourX < MAX_X) &&
                    (neighbourY > -1) && (neighbourY < MAX_Y) &&
                    m_cells[neighbourY][neighbourX].IsAlive())
                {
                    ++count;
                }
            }
        }
    }

    return count;
}

//---------------------------------------------------------------------------------------------------------------------
