#pragma once

//---------------------------------------------------------------------------------------------------------------------

class CLifeCell
{
private:
    bool m_alive{false};

public:
    CLifeCell() = default;
    explicit CLifeCell(bool alive);

    bool IsAlive() const;
    void SetAlive();
    void SetDead();
};

//---------------------------------------------------------------------------------------------------------------------
