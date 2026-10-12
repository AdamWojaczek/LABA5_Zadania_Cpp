#include "CHandValue.h"

//---------------------------------------------------------------------------------------------------------------------

CHandValue::CHandValue(EHandType type, const vector<int>& rankValues)
{
	m_type = type;
	m_rankValues = rankValues;
}

//---------------------------------------------------------------------------------------------------------------------

EHandType CHandValue::GetType() const
{
	return m_type;
}

//---------------------------------------------------------------------------------------------------------------------

const std::vector<int>& CHandValue::GetRankValues() const
{
	return m_rankValues;
}

//---------------------------------------------------------------------------------------------------------------------

void CHandValue::Set(EHandType type, const vector<int>& rankValues)
{
	m_type = type;
	m_rankValues = rankValues;
};

//---------------------------------------------------------------------------------------------------------------------

int CHandValue::TypeAsInt() const
{
	return static_cast<int>(m_type);
}

//---------------------------------------------------------------------------------------------------------------------

bool CHandValue::operator<(const CHandValue& other) const
{
	if (m_type != other.m_type)
		return (m_type < other.m_type);

	return m_rankValues < other.m_rankValues;
}

//---------------------------------------------------------------------------------------------------------------------

bool CHandValue::operator>(const CHandValue& other) const
{
	if (m_type != other.m_type)
		return (m_type > other.m_type);

	return m_rankValues > other.m_rankValues;
}

//---------------------------------------------------------------------------------------------------------------------

bool CHandValue::operator==(const CHandValue& other) const
{
	return (m_type == other.m_type) && (m_rankValues == other.m_rankValues);
}

//---------------------------------------------------------------------------------------------------------------------

std::string CHandValue::GetHandName() const
{
	std::string result;

	switch (m_type)
	{
		case EHandType::HIGH_CARD: result = "wysoka karta"; break;
		case EHandType::PAIR: result = "para"; break;
		case EHandType::TWO_PAIRS: result = "dwie pary"; break;
		case EHandType::THREE_OF_A_KIND: result = "trojka"; break;
		case EHandType::STRAIGHT: result = "strit"; break;
		case EHandType::FLUSH: result = "kolor"; break;
		case EHandType::FULL_HOUSE: result = "full"; break;
		case EHandType::FOUR_OF_A_KIND: result = "kareta"; break;
		case EHandType::STRAIGHT_FLUSH: result = "poker"; break;
		case EHandType::ROYAL_FLUSH: result = "poker krolewski"; break;
	}

	return result;
}

//---------------------------------------------------------------------------------------------------------------------
