#include "CHand.h"

#include <algorithm>

//---------------------------------------------------------------------------------------------------------------------

void CHand::Clear()
{
	m_cards.clear();
}

//---------------------------------------------------------------------------------------------------------------------

unsigned int CHand::GetSize() const
{
	return static_cast<unsigned int>(m_cards.size());
}

//---------------------------------------------------------------------------------------------------------------------

void CHand::Sort()
{
	auto sortRule = [](const CCard& card1, const CCard& card2) {
		return static_cast<int>(card1.GetRank()) < static_cast<int>(card2.GetRank());
		};

	std::sort(m_cards.begin(), m_cards.end(), sortRule);
}

//---------------------------------------------------------------------------------------------------------------------

void CHand::AddCard(const CCard& card)
{
	m_cards.push_back(card);
}

//---------------------------------------------------------------------------------------------------------------------

CCard& CHand::GetCard(unsigned int index)
{
	return m_cards[index];
}

//---------------------------------------------------------------------------------------------------------------------

const CCard& CHand::GetCard(unsigned int index) const
{
	return m_cards[index];
}

//---------------------------------------------------------------------------------------------------------------------

void CHand::ExchangeCard(unsigned int oldCardNumber, const CCard& newCard)
{
	if (oldCardNumber > 0)
		m_cards[oldCardNumber - 1] = newCard;
}

//---------------------------------------------------------------------------------------------------------------------

auto CHand::GetCards() const -> TCards
{
	return TCards();
}

//---------------------------------------------------------------------------------------------------------------------

std::vector<int> CHand::GetRankValues(bool ascending) const
{
	std::vector<int> rankValues;
	rankValues.reserve(m_cards.size());

	for (const auto& card : m_cards)
		rankValues.push_back(Int(card.GetRank()));
	
	if (ascending)
		std::sort(rankValues.begin(), rankValues.end());
	else
		std::sort(rankValues.rbegin(), rankValues.rend());

	return rankValues;
}

//---------------------------------------------------------------------------------------------------------------------

std::vector<int> CHand::GetRankCounts() const
{
	std::vector<int> rankCounts(RANK_COUNT + 2, 0);		// additional/empty fields [0] and [1] for simply mapping

	for (unsigned int i = 0; i < m_cards.size(); ++i)
	{
		const int rankValue = Int(m_cards[i].GetRank());
		++rankCounts[rankValue];
	}

	return rankCounts;
}

//---------------------------------------------------------------------------------------------------------------------

