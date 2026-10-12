#pragma once

#include <vector>
#include "CHand.h"
#include "CHandValue.h"

//---------------------------------------------------------------------------------------------------------------------

class CPokerRules
{
private:
	template<typename T> using vector = std::vector<T>;

	const unsigned int MAX_HAND_SIZE{5};

	bool IsSingleSuit(const CHand& hand) const;
	int GetStraightAndHighRank(const CHand& hand) const;

	CHandValue EvaluateHighCard(const vector<int>& rankValues) const;
	CHandValue EvaluateOnePair(const vector<int>& rankValues, const vector<int>& rankCounts) const;
	CHandValue EvaluateTwoPairs(const vector<int>& rankCounts) const;
	CHandValue EvaluateThreeOfAKind(const vector<int>& rankCounts) const;
	CHandValue EvaluateFullHouse(const vector<int>& rankCounts) const;
	CHandValue EvaluateFourOfAKind(const vector<int>& rankCounts) const;

public:
	const unsigned int GetMaxHandSize() const;
	CHandValue Evaluate(const CHand& hand) const;
	int Compare(const CHand& hand1, const CHand& hand2) const;
};

//---------------------------------------------------------------------------------------------------------------------
