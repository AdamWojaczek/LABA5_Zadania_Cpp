#pragma once

#include <vector>
#include <string>

//---------------------------------------------------------------------------------------------------------------------

enum class EHandType : int
{
	HIGH_CARD,			// Wysoka karta
	PAIR,				// Para
	TWO_PAIRS,			// Dwie pary
	THREE_OF_A_KIND,	// Trójka
	STRAIGHT,			// Strit (piêæ kart dowolnego koloru u³o¿onych po kolei)
	FLUSH,				// Kolor (piêæ kart w tym samym kolorze)
	FULL_HOUSE,			// Ful (trójka + para)
	FOUR_OF_A_KIND,		// Kareta (cztery karty o tej samej wartoœci)
	STRAIGHT_FLUSH,		// Poker (strit w kolorze - 5 kolejnych kart w tym samym kolorze)
	ROYAL_FLUSH			// Poker królewski (A, K, Q, J, 10 w tym samym kolorze)
};

//---------------------------------------------------------------------------------------------------------------------

class CHandValue
{
private:
	template<typename T> using vector = std::vector<T>;

	EHandType m_type{};
	vector<int> m_rankValues{};

public:
	CHandValue() = default;
	CHandValue(EHandType type, const vector<int>& rankValues);

	EHandType GetType() const;	
	const vector<int>& GetRankValues() const;
	void Set(EHandType type, const vector<int>& rankValues);
	int TypeAsInt() const;
	std::string GetHandName() const;
	bool operator<(const CHandValue& other) const;
	bool operator>(const CHandValue& other) const;
	bool operator==(const CHandValue& other) const;
};

//---------------------------------------------------------------------------------------------------------------------
