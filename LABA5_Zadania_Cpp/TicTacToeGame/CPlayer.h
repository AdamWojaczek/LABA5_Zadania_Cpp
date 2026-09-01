#pragma once

#include <string>
#include "..\StrUtils.h"
#include "TicTacToeTypes.h"

class CPlayer
{
private:
    using string = std::string;

    string m_name{"Gracz"};
    bool m_isComputer{false};
    EBoardField m_symbol{EBoardField::EMPTY};

public:
    CPlayer() = default;
    CPlayer(const string& name, EBoardField symbol, bool isComputer);

    void SetName(const string& name);
    string GetName() const;

    void SetSymbol(EBoardField symbol);
    EBoardField GetSymbol() const;
    string GetSymbolAsString() const;

    void SetNameAndSymbol(std::pair<string, EBoardField> playerId);
    string GetPlayerDescription() const;

    bool IsComputer() const;
    void SetComputer();
    void SetHuman();
};