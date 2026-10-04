#pragma once

#include <string>
#include <vector>
#include <chrono>

#include "LifeConstans.h"
#include "CLifeBoard.h"

//---------------------------------------------------------------------------------------------------------------------

class CLifeGame
{
private:
    using string = std::string;
    template<typename T> using vector = std::vector<T>;

    CLifeBoard m_board;
    unsigned int m_generation{0};

    string GetIniFilePath() const;
    bool LoadConfiguration(const string& filePath);
    bool GetConfigFromFile(const string& filePath, unsigned int& width, unsigned int& height,
                           string& deadCell, string& liveCell, vector<string>& initialState) const;
    void ValidateDisplayValues(string& deadCell, string& liveCell) const;
    void Render(std::chrono::milliseconds period);
    int GetCenteredTextOffset(const string& text, int displayWidth);

public:
    void Run();
};

//---------------------------------------------------------------------------------------------------------------------
