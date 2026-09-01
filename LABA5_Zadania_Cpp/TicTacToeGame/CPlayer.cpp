#include "CPlayer.h"

CPlayer::CPlayer(const string& name, EBoardField symbol, bool isComputer)
    : m_name(name),
      m_symbol(symbol),
      m_isComputer(isComputer)
{
}

void CPlayer::SetName(const string& name)
{
    m_name = StrUtils::StrTrim(name);
}

std::string CPlayer::GetName() const
{
    return m_name;
}

void CPlayer::SetSymbol(EBoardField symbol)
{
    m_symbol = symbol;
}

EBoardField CPlayer::GetSymbol() const
{
    return m_symbol;
}

auto CPlayer::GetSymbolAsString() const -> string
{
    return "'" + std::string(1, static_cast<char>(m_symbol)) + "'";
}

void CPlayer::SetNameAndSymbol(std::pair<string, EBoardField> playerId)
{
    SetName(playerId.first);
    SetSymbol(playerId.second);
}

auto CPlayer::GetPlayerDescription() const -> string
{
    return "Gracz" + string(m_isComputer ? " KOMPUTER" :  "") + ": " + GetSymbolAsString() + " " + m_name;
}

bool CPlayer::IsComputer() const
{
    return m_isComputer;
}

void CPlayer::SetComputer()
{
    m_isComputer = true;
}

void CPlayer::SetHuman()
{
    m_isComputer = false;
}
