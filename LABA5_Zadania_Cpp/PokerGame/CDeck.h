#pragma once

#include "CCard.h"
#include <vector>
#include <random>
#include "CardTypes.h"

//---------------------------------------------------------------------------------------------------------------------

class CDeck
{
private:
	using TCards = std::vector<CCard>;

	TCards m_cards{};
	unsigned int m_position{};
	std::mt19937 m_generator;

	void Create();

public:
	CDeck();

	void Shuffle();
	CCard Draw();
};

//---------------------------------------------------------------------------------------------------------------------
