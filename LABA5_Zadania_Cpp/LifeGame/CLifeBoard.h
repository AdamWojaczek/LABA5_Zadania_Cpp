#pragma once

#include <string>
#include <vector>

#include "LifeConstans.h"
#include "CLifeCell.h"

//---------------------------------------------------------------------------------------------------------------------

class CLifeBoard
{
private:
    using string = std::string;
    template<typename T> using vector = std::vector<T>;

    unsigned int m_width{0};
    unsigned int m_height{0};

    vector<vector<CLifeCell>> m_cells;
    vector<vector<CLifeCell>> m_nextCells;

    string m_deadCell{DEFAULT_DEAD_CELL_DISPLAY};
    string m_liveCell{DEFAULT_LIVE_CELL_DISPLAY};

    unsigned int CountAliveNeighbours(unsigned int x, unsigned int y) const;

public:
    bool Initialize(unsigned int width, unsigned int height);
    bool SetInitialState(const vector<string>& state);
    bool SetDisplayCharacters(const string& deadCell, const string& liveCell);
    void NextGeneration();
    void Display() const;
    unsigned int GetDispltWidth() const;
};

//---------------------------------------------------------------------------------------------------------------------
