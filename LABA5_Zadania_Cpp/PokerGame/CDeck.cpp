#include "CDeck.h"

//---------------------------------------------------------------------------------------------------------------------

CDeck::CDeck()
	: m_generator(std::random_device{}())
{
	Create();
}

//---------------------------------------------------------------------------------------------------------------------

void CDeck::Create()
{
	m_cards.clear();
	m_cards.reserve(RANK_COUNT * SUIT_COUNT);

	for (ESuit suit = ESuit::CLUBS; suit <= ESuit::SPADES; ++suit)
	{
		for (ERank rank = ERank::TWO; rank <= ERank::ACE; ++rank)
			m_cards.emplace_back(rank, suit);
	}
}

//---------------------------------------------------------------------------------------------------------------------

void CDeck::Shuffle()
{
	std::shuffle(m_cards.begin(), m_cards.end(), m_generator);
	m_position = 0;
}

//---------------------------------------------------------------------------------------------------------------------

CCard CDeck::Draw()
{
	return m_cards[m_position++];
}

//---------------------------------------------------------------------------------------------------------------------

