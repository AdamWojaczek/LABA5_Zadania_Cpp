#pragma once

#include "CCard.h"
#include <vector>

//---------------------------------------------------------------------------------------------------------------------

class CHand
{
private:
	using TCards = std::vector<CCard>;
	template<typename T> using vector = std::vector<T>;

	TCards m_cards{};

public:
	void Clear();
	unsigned int GetSize() const;
	void Sort();

	void AddCard(const CCard& card);
	CCard& GetCard(unsigned int index);
	const CCard& GetCard(unsigned int index) const;
	void ExchangeCard(unsigned int oldCardNumber, const CCard& newCard);

	TCards GetCards() const;
	vector<int> GetRankValues(bool ascending = true) const;
	vector<int> GetRankCounts() const;
};

//---------------------------------------------------------------------------------------------------------------------
