#include "CTicTacToeGame.h"

void CTicTacToeGame::Run()
{
    EGameState gameState = EGameState::MENU;

    while (gameState != EGameState::EXIT_GAME)
    {
        switch (gameState)
        {
            case EGameState::MENU:
                ShowMenu();
                gameState = GetMenuAction();
                break;
            
            case EGameState::CONFIG_GAME:
                gameState = ConfigGame();
                break;

            case EGameState::CONFIG_PLAYERS:
                gameState = ConfigPlayerNames();
                break;

            case EGameState::SWITCH_DISPLAY_BOARD_WEIGHTS:
                gameState = SwitchDisplayBoardWeights();
                break;

            case EGameState::GAME_PVC:
                SetComputerPlayer();
                gameState = PlayGame();
                break;

            case EGameState::GAME_PVP:
                ClearComputerPlayer();
                gameState = PlayGame();
                break;

            default:
                gameState = EGameState::EXIT_GAME;
        }
    }
}

void CTicTacToeGame::ShowMenu()
{
    ios.ClearScreen();
    ios.PrintLine("[OOO]  KOLKO I KRZYZYK  [XXX]");
    ios.PrintLine("-----------------------------");
    ios.PrintLine("---        MENU GRY       ---");
    ios.PrintLine();
    ios.PrintLine(" [1] Ustawienia gry (planszy)");
    ios.PrintLine(" [2] Zmien nazwy graczy");
    ios.PrintLine(" [3] Tablica waga jednego kroku -> jest " +
                  string(m_showOneStepBoardWeights ? "wyswietlana" : "ukryta"));
    ios.PrintLine(" [4] Gra: 'Gracz' vs 'Komputer'");
    ios.PrintLine(" [5] Gra: 'Gracz' vs 'Gracz'");
    ios.PrintLine("");
    ios.PrintLine(" [0] Koniec gry");
    ios.PrintLine("");
}

EGameState CTicTacToeGame::GetMenuAction()
{
    EGameState actionState = EGameState::MENU;
    int actionNumber = -1;
    
    if (ios.ReadInt("Wybierz:", actionNumber) && (actionNumber > -1))
    {
        switch (actionNumber)
        {
            case 0: actionState = EGameState::EXIT_GAME; break;
            case 1: actionState = EGameState::CONFIG_GAME; break;
            case 2: actionState = EGameState::CONFIG_PLAYERS; break;
            case 3: actionState = EGameState::SWITCH_DISPLAY_BOARD_WEIGHTS;  break;
            case 4: actionState = EGameState::GAME_PVC; break;
            case 5: actionState = EGameState::GAME_PVP; break;
            
            default:
                actionNumber = -1;
        }
    }

    if (actionNumber < 0)
    {
        actionState = EGameState::MENU;
        ios.Print("Brak takiej opcji!");
        ios.WaitForEnter();
    }

    return actionState;
}

EGameState CTicTacToeGame::ConfigGame()
{
    ios.ClearScreen();
    ios.PrintLine("[OOO]  KOLKO I KRZYZYK  [XXX]");
    ios.PrintLine("-----------------------------");
    ios.PrintLine("---   KONFIGURACJA GRY    ---");
    ios.PrintLine();

    int boardSize = GetBoardSize();
    m_board.SetSize(boardSize);
    m_winLength = GetWinLength();

    ios.WaitForEnter();

    return EGameState::MENU;
}

int CTicTacToeGame::GetBoardSize()
{
    int boardSize = DEFAULT_SIZE;
    bool result = false;

    if (ios.ReadInt("Podaj rozmiar planszy <" + StrUtils::IntToStr(MIN_SIZE) + "-" +
        StrUtils::IntToStr(MAX_SIZE) + ">: ", boardSize))
    {
        result = (boardSize >= MIN_SIZE) && (boardSize <= MAX_SIZE);
        if (!result)
            boardSize = ClampSize(boardSize);
    }
    else
        boardSize = DEFAULT_SIZE;

    if (!result)
    {
        ios.PrintLine("Podano nieprawidlowa wartosc. Ustawiono rozmiar planszy na: " + StrUtils::IntToStr(boardSize));
        result = true;
    }

    return boardSize;
}

int CTicTacToeGame::ClampSize(int size)
{
    int clampedSize;

    if (size < MIN_SIZE)
        clampedSize = MIN_SIZE;
    else if (size > MAX_SIZE)
        clampedSize = MAX_SIZE;
    else
        clampedSize = size;

    return clampedSize;
}

int CTicTacToeGame::GetWinLength()
{
    int boardSize = m_board.GetSize();
    int winLenght = boardSize;
    bool result = false;

    if (ios.ReadInt("Podaj zwycieska liczbe znakow w linii (maks. " + StrUtils::IntToStr(boardSize) + "): ", winLenght))
        result = (winLenght >= MIN_SIZE) && (winLenght <= boardSize);

    if (!result)
    {
        winLenght = boardSize;
        ios.PrintLine("Podano nieprawidlowa wartosc. Ustawiono zwycieska dlugosc na: " + StrUtils::IntToStr(winLenght));
    }

    return winLenght;
}

EGameState CTicTacToeGame::ConfigPlayerNames()
{
    ios.ClearScreen();
    ios.PrintLine("[OOO]  KOLKO I KRZYZYK  [XXX]");
    ios.PrintLine("-----------------------------");
    ios.PrintLine("---   USTAWIENIA GRACZY   ---");
    ios.PrintLine();

    m_playerOne.SetName(GetPlayerName(m_playerOne.GetSymbol()));
    m_playerTwo.SetName(GetPlayerName(m_playerTwo.GetSymbol()));
    
    return EGameState::MENU;
}

std::string CTicTacToeGame::GetPlayerName(EBoardField symbol)
{
    string name = "";

    ios.ReadString(string("Podaj nazwe gracza o symbolu '") + static_cast<char>(symbol) + "': ", name);   
    name = StrUtils::StrTrim(name);

    if (name.empty())
        name = "Gracz " + static_cast<char>(symbol);

    return name;
}

EGameState CTicTacToeGame::SwitchDisplayBoardWeights()
{
    m_showOneStepBoardWeights = !m_showOneStepBoardWeights;
    return EGameState::MENU;
}

void CTicTacToeGame::SetComputerPlayer()
{
    ios.ClearScreen();
    ios.PrintLine("[OOO]    KOLKO I KRZYZYK     [XXX]");
    ios.PrintLine("----------------------------------");
    ios.PrintLine("--- WYBOR KOMPUTEROWEGO GRACZA ---");
    ios.PrintLine();

    ios.PrintLine("[1] " + m_playerOne.GetPlayerDescription());
    ios.PrintLine("[2] " + m_playerTwo.GetPlayerDescription());
    
    int playerNumber = 0;
    while ((playerNumber != 1) && (playerNumber != 2))
        ios.ReadInt("Wybierz gracza dla komputera [1 lub 2]: ", playerNumber);

    if (playerNumber == 1)
    {
        m_playerOne.SetComputer();
        m_playerTwo.SetHuman();
    }
    else
    {
        m_playerOne.SetHuman();
        m_playerTwo.SetComputer();
    }

    ios.WaitForEnter();
}

void CTicTacToeGame::ClearComputerPlayer()
{
    m_playerOne.SetHuman();
    m_playerTwo.SetHuman();
}

EGameState CTicTacToeGame::PlayGame()
{
    bool finishGame = false;
    std::map<EBoardField, int> moveCounter { {m_playerOne.GetSymbol(), 0}, {m_playerTwo.GetSymbol(), 0} };
    
    m_board.ClearFields();

    while (!finishGame)
    {   
        moveCounter[m_pCurrentPlayer->GetSymbol()]++;
        RenderGamePlay();

        ios.PrintLine();
        ios.PrintLine("Ruch nr " + StrUtils::IntToStr(moveCounter.at(m_pCurrentPlayer->GetSymbol())) + " " +
                      m_pCurrentPlayer->GetPlayerDescription());

        int row = -1, col = -1;
        if (m_pCurrentPlayer->IsComputer())
        {
            auto cr = GetBestColRowField();
            col = cr.first;
            row = cr.second;
        }
        else
        {
            const string boardSizeString = StrUtils::IntToStr(m_board.GetSize());
            do
            {
                ios.ReadInt("Kolumna 1-" + boardSizeString + ": ", col);
                ios.ReadInt("Wiersz  1-" + boardSizeString + ": ", row);
            } while (!IsValidMove(--col, --row));
        }
        m_board.SetField(col, row, m_pCurrentPlayer->GetSymbol());

        if (m_pCurrentPlayer->IsComputer())
            ios.WaitForEnter();
        
        if (m_board.CheckWin(col, row, m_pCurrentPlayer->GetSymbol(), m_winLength))
        {
            RenderGamePlay();
            ios.PrintLine();
            ios.PrintLine("WYGRYWA " + m_pCurrentPlayer->GetPlayerDescription());
            finishGame = true;
        }
        else if (m_board.IsFull())
        {
            RenderGamePlay();
            ios.PrintLine();
            ios.PrintLine("REMIS!");
            finishGame = true;
        }

        if (finishGame)
        {
            ios.PrintLine();
            ios.PrintLine("--- KONIEC GRY ---");
            ios.WaitForEnter();
        }
        else
            SwitchPlayer();
    }
    
    return EGameState::MENU;
}

void CTicTacToeGame::RenderGamePlay()
{
    ios.ClearScreen();
    ios.PrintLine("[OOO]  KOLKO I KRZYZYK  [XXX]");
    ios.PrintLine("-----------------------------");
    ios.PrintLine(m_playerOne.GetPlayerDescription());
    ios.PrintLine(m_playerTwo.GetPlayerDescription());
    ios.PrintLine("Zwycieska liczba znakow: " + StrUtils::IntToStr(m_winLength));
    m_board.Display();
    if (m_showOneStepBoardWeights)
    {
        ios.PrintLine();
        DisplayBoardWeights();
    }
}

bool CTicTacToeGame::IsValidMove(int col, int row)
{
    bool result = false;
        
    if (m_board.IsEmpty(col, row))
        result = true;
    else if (!m_board.IsValid(col, row))
        ios.PrintLine("Podane wspolrzedne pola sa poza plansza!");
    else
        ios.PrintLine("Podane pole jest juz zajete!");

    return result;
}

int CTicTacToeGame::GetRandomValue(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(m_generator);
}

void CTicTacToeGame::SetFirstPlayer()
{
    m_pCurrentPlayer = (GetRandomValue() == 0) ? &m_playerOne : &m_playerTwo;
}

void CTicTacToeGame::SwitchPlayer()
{
    m_pCurrentPlayer = (m_pCurrentPlayer == &m_playerOne) ? &m_playerTwo : &m_playerOne;
}

std::pair<int, int> CTicTacToeGame::GetBestColRowField() const
{
    const EBoardField mySymbol = m_pCurrentPlayer->GetSymbol();
    const EBoardField opponentSymbol = GetOpponentSymbol();
    int bestCol = -1, bestRow = -1, bestWeight = -1, boardSize = m_board.GetSize();

    for (int row = 0; row < boardSize; ++row)
    {
        for (int col = 0; col < boardSize; ++col)
        {
            int weight = GetFieldWeight(col, row, mySymbol, opponentSymbol);

            if (weight > bestWeight)
            {
                bestWeight = weight;
                bestCol = col;
                bestRow = row;
            }
        }
    }

    return {bestCol, bestRow};
}

int CTicTacToeGame::GetFieldWeight(int col, int row, EBoardField mySymbol, EBoardField opponentSymbol) const
{
    /*
        WAGI:
         - pole wygrywaj¹ce = winLength * 100000
         - pole wygrywaj¹ce przeciwnika = winLength * 70000
         - pole daj¹ce w³asne symbole w linii (bez aktualnego): n * 1000
         - pole daj¹ce przeciwnikowi symbole w linii (bez aktualnego): n * 700
         - bonus centrum 1 .. (2 * rozmiar planszy)
    */

    const int myWinField = 100000, opponentWinField = 70000, myWeight = 1000, opponentWeight = 700;
    int weight = 0;

    if (m_board.IsEmpty(col, row))
    {
        // pole zapewniaj¹ce zwyciêstwo
        if (m_board.CheckWin(col, row, mySymbol, m_winLength))
            weight += myWinField;

        // pole blokuje zwyciestwo przeciwnika
        if (m_board.CheckWin(col, row, opponentSymbol, m_winLength))
            weight += opponentWinField;

        // obliczenie potencja³u pola dla siebie
        weight += m_board.GetMaxCountDirection(col, row, mySymbol) * myWeight;

        // obliczenie potencja³u pola dla przeciwnika
        weight += m_board.GetMaxCountDirection(col, row, opponentSymbol) * opponentWeight;

        // bli¿ej centrum - troszkê lepiej
        const int boardSize = m_board.GetSize(), center = boardSize / 2;
        weight += 2 * boardSize - std::abs(col - center) - std::abs(row - center);
    }
    else
        weight = 0;

    return weight;
}

void CTicTacToeGame::DisplayBoardWeights() const
{
    const EBoardField mySymbol = m_pCurrentPlayer->GetSymbol();
    const EBoardField opponentSymbol = GetOpponentSymbol();
    const int boardSize = m_board.GetSize();

    std::vector<std::vector<int>> fields(boardSize, std::vector<int>(boardSize, 0));
    for (int row = 0; row < boardSize; ++row)
        for (int col = 0; col < boardSize; ++col)
            fields[row][col] = GetFieldWeight(col, row, mySymbol, opponentSymbol);

    std::ostringstream display;
    display << std::internal << std::setfill('0') << "Tablica wag jednego kroku";
    for (int row = 0; row < boardSize; ++row)
    {
        display << '\n';
        for (int col = 0; col < boardSize; ++col)
            display << "[" << std::setw(6) << static_cast<int>(fields[row][col]) << "] ";
    }
    display << '\n';
    std::cout << display.str();
}

EBoardField CTicTacToeGame::GetOpponentSymbol() const
{
    return (m_pCurrentPlayer->GetSymbol() == EBoardField::X) ? EBoardField::O : EBoardField::X;
}