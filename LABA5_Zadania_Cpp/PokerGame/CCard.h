#pragma once

#include <string>
#include "CardTypes.h"

//---------------------------------------------------------------------------------------------------------------------

class CCard
{
private:
	ERank m_rank;
	ESuit m_suit;

public:
	CCard(ERank rank, ESuit suit);

	ERank GetRank() const;
	ESuit GetSuit() const;
	std::string ToString() const;
};

//---------------------------------------------------------------------------------------------------------------------
