#include "CLifeGame.h"

#include <thread>
#include <conio.h>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "..\StrUtils.h"
#include "..\CIniFileParser.h"

//---------------------------------------------------------------------------------------------------------------------

void CLifeGame::Run()
{
    using std::chrono::milliseconds;
    using std::chrono::steady_clock;

    bool running = false, paused = false, showPauseInfo = false, updateSpeed = false;
    
    milliseconds nextGeneration(1000);
    const milliseconds speedDelta(50), sleep(25);
    auto last = steady_clock::now();

    const string filePath = GetIniFilePath();
    if (LoadConfiguration(filePath))
        running = true;
    else
        std::cout << "Game configutation error or config file error/not found '" << filePath << "'" << std::endl;

    while (running)
    {
        if (_kbhit())
        {
            const int key = _getch();
            switch (key)
            {
                case 'q': case 'Q':
                    running = false;
                    break;

                case 'p': case 'P':
                    paused = !paused;
                    showPauseInfo = paused;
                    break;

                case '+':
                    if (nextGeneration > milliseconds(SPEED_RANGE.first))
                    {
                        nextGeneration -= speedDelta;
                        if (nextGeneration < milliseconds(SPEED_RANGE.first))
                            nextGeneration = milliseconds(SPEED_RANGE.first);
                        updateSpeed = true;
                    }
                    break;

                case '-':
                    if (nextGeneration < milliseconds(SPEED_RANGE.second))
                    {
                        nextGeneration += speedDelta;
                        if (nextGeneration > milliseconds(SPEED_RANGE.second))
                            nextGeneration = milliseconds(SPEED_RANGE.second);
                        updateSpeed = true;
                    }
                    break;
            }
        }

        if (!paused && (steady_clock::now() - last >= nextGeneration))
        {
            Render(nextGeneration);
            ++m_generation;
            m_board.NextGeneration();
            last = steady_clock::now();
        }
        else if (updateSpeed)
        {
            Render(nextGeneration);
            updateSpeed = false;
        }
        else if (showPauseInfo)
        {
            std::cout << std::endl << "GAME PAUSED - PRESS [P] TO RESUME";
            showPauseInfo = false;
        }
        else
            std::this_thread::sleep_for(sleep);
    }

    std::cout << std::endl << "GAME OVER PLAYER ONE!" << std::endl;
}

//---------------------------------------------------------------------------------------------------------------------

std::string CLifeGame::GetIniFilePath() const
{
    string filePath = "";
    
    const string file = "Life.ini";
    const string dir = std::filesystem::current_path().string();
    const string paths[] = {
        dir + "\\" + file,
        dir + "\\LifeGame\\" + file,
        dir + "\\..\\x64\\Release\\" + file,
        dir + "\\..\\x64\\Debug\\" + file
    };

    for (const string& possiblePath : paths)
    {
        if (std::filesystem::exists(possiblePath))
        {
            filePath = possiblePath;
            break;
        }
    }

    return filePath;
}

//---------------------------------------------------------------------------------------------------------------------

bool CLifeGame::LoadConfiguration(const string& filePath)
{
    bool result = false;
    unsigned int width, height;
    string deadCell, liveCell;
    vector<string> initialState;
    
    result = GetConfigFromFile(filePath, width, height, deadCell, liveCell, initialState) &&
             m_board.Initialize(width, height) &&
             m_board.SetDisplayCharacters(deadCell, liveCell) &&
             m_board.SetInitialState(initialState);
    
    return result;
}

//---------------------------------------------------------------------------------------------------------------------

bool CLifeGame::GetConfigFromFile(const string& filePath, unsigned int& width, unsigned int& height,
                                  string& deadCell, string& liveCell, vector<string>& initialState) const
{
    bool result = false;

    CIniFileParser file(filePath);

    if (file.IsValid() &&
        file.HasSection("BOARD") &&
        file.HasSection("DISPLAY") &&
        file.HasSection("INITIAL_STATE"))
    {
        // [BOARD]
        if (!StrUtils::StrToUInt(file.GetVariable("BOARD", "Width"), width) || 
            (width < WIDTH_RANGE.first) || (width > WIDTH_RANGE.second))
        {
            width = (WIDTH_RANGE.second - WIDTH_RANGE.first) / 2;
        }
            
        if (!StrUtils::StrToUInt(file.GetVariable("BOARD", "Height"), height) ||
            (height < HEIGHT_RANGE.first) || (height > HEIGHT_RANGE.second))
        {
            height = (HEIGHT_RANGE.second - HEIGHT_RANGE.first) / 2;
        }

        // [DISPLAY]
        deadCell = file.GetVariable("DISPLAY", "DeadCell");
        liveCell = file.GetVariable("DISPLAY", "LiveCell");

        ValidateDisplayValues(deadCell, liveCell);

        // [INITIAL_STATE]
        const std::unordered_map<string, string> initMap = file.GetVariables("INITIAL_STATE");
        const string extraRow(width, DEAD_CELL_INIT_SET);
        initialState.reserve(height);

        for (unsigned int i = 0; i < height; ++i)
        {
            if (i < initMap.size())
            {
                initialState.push_back(initMap.at(StrUtils::UIntToStr(i + 1)));

                // Check and truncate or extend the row to the required width.
                string& row = initialState[i];                
                if (row.length() > width)
                    row.erase(width);
                else if (row.length() < width)
                    row += string(width - row.length(), DEAD_CELL_INIT_SET);
            }
            else
                initialState.push_back(extraRow);   // add default row
        }

        result = true;
    }

    return result;
}

//---------------------------------------------------------------------------------------------------------------------

void CLifeGame::ValidateDisplayValues(string& deadCell, string& liveCell) const
{
    if (deadCell.empty())
        deadCell = DEFAULT_DEAD_CELL_DISPLAY;
    else if (deadCell.length() > 2)
        deadCell = deadCell.substr(0, 2);
    
    if (liveCell.empty())
        liveCell = DEFAULT_LIVE_CELL_DISPLAY;
    else if (liveCell.length() > 2)
        liveCell = liveCell.substr(0, 2);

    if (deadCell.length() > liveCell.length())
        liveCell += " ";
    else if (deadCell.length() < liveCell.length())
        deadCell += " ";

    if (StrUtils::StrTrim(deadCell) == StrUtils::StrTrim(liveCell))
    {
        deadCell = DEFAULT_DEAD_CELL_DISPLAY;
        liveCell = DEFAULT_LIVE_CELL_DISPLAY;
    }
}

//---------------------------------------------------------------------------------------------------------------------

void CLifeGame::Render(std::chrono::milliseconds period)
{
    system("cls");
    
    int displayWidth = static_cast<int>(m_board.GetDispltWidth()) + 2;
    string separatorLine = string(displayWidth, '-');

    string title = "GAME OF LIFE";
    int titleOffset = GetCenteredTextOffset(title, displayWidth);

    string menu = "Generation: " + StrUtils::UIntToStr(m_generation) + ", " +
                  "next in: " + StrUtils::UIntToStr(static_cast<unsigned int>(period.count())) + " ms | " +
                  "[+][-] Change speed | [P] Pause | [Q] Quit";
    int menuOffset = GetCenteredTextOffset(menu, displayWidth);

    std::ostringstream buffer;
    buffer << std::endl << separatorLine << std::endl;
    buffer << string(titleOffset, ' ') << title << std::endl << std::endl;
    buffer << string(menuOffset, ' ') << menu << std::endl << std::endl;
    std::cout << buffer.str();

    m_board.Display();
}

//---------------------------------------------------------------------------------------------------------------------

int CLifeGame::GetCenteredTextOffset(const string& text, int displayWidth)
{
    int offset = (displayWidth - static_cast<int>(text.length())) / 2;

    if (offset < 0)
        offset = 0;

    return offset;
}

//---------------------------------------------------------------------------------------------------------------------
