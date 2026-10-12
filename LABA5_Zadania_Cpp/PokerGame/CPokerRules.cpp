#include "CPokerRules.h"

#include <algorithm>

//---------------------------------------------------------------------------------------------------------------------

bool CPokerRules::IsSingleSuit(const CHand& hand) const
{
	bool result = false;

	if (hand.GetSize() == MAX_HAND_SIZE)
	{
		const ESuit firstCardSuit = hand.GetCard(0).GetSuit();
		bool allSameSuit = true;

		for (unsigned int i = 1; (i < hand.GetSize()) && allSameSuit; ++i)
		{
			if (hand.GetCard(i).GetSuit() != firstCardSuit)
				allSameSuit = false;
		}

		result = allSameSuit;
	}

	return result;
}

//---------------------------------------------------------------------------------------------------------------------

int CPokerRules::GetStraightAndHighRank(const CHand& hand) const
{
	int result = 0;

	if (hand.GetSize() == MAX_HAND_SIZE)
	{
		const vector<int> rankValues = hand.GetRankValues(true);
		bool sequential = true;
		for (unsigned int i = 0; (i + 1 < rankValues.size()) && sequential; ++i)
		{
			if (rankValues[i + 1] != rankValues[i] + 1)
				sequential = false;
		}

		if (sequential)
			result = rankValues.back();
		else if ((rankValues[4] == Int(ERank::ACE)) &&
				 (rankValues[0] == Int(ERank::TWO)) &&
				 (rankValues[1] == Int(ERank::THREE)) &&
				 (rankValues[2] == Int(ERank::FOUR)) &&
				 (rankValues[3] == Int(ERank::FIVE)))
		{
			result = Int(ERank::FIVE);
		}
	}

	return result;
}

//---------------------------------------------------------------------------------------------------------------------

CHandValue CPokerRules::EvaluateHighCard(const vector<int>& rankValues) const
{
	return CHandValue(EHandType::HIGH_CARD, rankValues);
}

//---------------------------------------------------------------------------------------------------------------------

CHandValue CPokerRules::EvaluateOnePair(const vector<int>& rankValues, const vector<int>& rankCounts) const
{
	int pairRank = 0;
	vector<int> tempRankValues;

	for (ERank rank = ERank::ACE; rank >= ERank::TWO; --rank)
	{
		if (rankCounts[Int(rank)] == 2)
		{
			pairRank = Int(rank);
			tempRankValues.push_back(pairRank);
		}
	}

	if (tempRankValues.size() == 1)
	{
		for (int rankValue : rankValues)
		{
			if (rankValue != pairRank)
				tempRankValues.push_back(rankValue);
		}
	}
	
	return CHandValue(EHandType::PAIR, std::move(tempRankValues));
}

//---------------------------------------------------------------------------------------------------------------------

CHandValue CPokerRules::EvaluateTwoPairs(const vector<int>& rankCounts) const
{
	int highPair = 0, lowPair = 0, kicker = 0;

	for (ERank rank = ERank::ACE; rank >= ERank::TWO; --rank)
	{
		const int rankValue = Int(rank);
		if (rankCounts[rankValue] == 2)
		{
			if (highPair == 0)
				highPair = rankValue;
			else
				lowPair = rankValue;
		}
		else if (rankCounts[rankValue] == 1)
			kicker = rankValue;
	}

	return CHandValue(EHandType::TWO_PAIRS, {highPair, lowPair, kicker});
}

//---------------------------------------------------------------------------------------------------------------------

CHandValue CPokerRules::EvaluateThreeOfAKind(const vector<int>& rankCounts) const
{
	int threeRank = 0;
	vector<int> tempRankValues;

	for (ERank rank = ERank::ACE; rank >= ERank::TWO; --rank)
	{
		if (rankCounts[Int(rank)] == 3)
		{
			threeRank = Int(rank);
			tempRankValues.push_back(threeRank);
		}
	}

	if (tempRankValues.size() == 1)
	{
		for (ERank rank = ERank::ACE; rank >= ERank::TWO; --rank)
		{
			if (rankCounts[Int(rank)] == 1)
				tempRankValues.push_back(Int(rank));
		}
	}

	return CHandValue(EHandType::THREE_OF_A_KIND, std::move(tempRankValues));
}

//---------------------------------------------------------------------------------------------------------------------

CHandValue CPokerRules::EvaluateFullHouse(const vector<int>& rankCounts) const
{
	int threeRank = 0, pairRank = 0;

	for (ERank rank = ERank::ACE; rank >= ERank::TWO; --rank)
	{
		const int rankValue = Int(rank);
		if (rankCounts[rankValue] == 3)
			threeRank = rankValue;
		else if (rankCounts[rankValue] == 2)
			pairRank = rankValue;
	}

	return CHandValue(EHandType::FULL_HOUSE, {threeRank, pairRank});
}

//---------------------------------------------------------------------------------------------------------------------

CHandValue CPokerRules::EvaluateFourOfAKind(const vector<int>& rankCounts) const
{
	int fourRank = 0, kicker = 0;

	for (ERank rank = ERank::ACE; rank >= ERank::TWO; --rank)
	{
		const int rankValue = Int(rank);
		if (rankCounts[rankValue] == 4)
			fourRank = rankValue;
		else if (rankCounts[rankValue] == 1)
			kicker = rankValue;
	}
	return CHandValue(EHandType::FOUR_OF_A_KIND, {fourRank, kicker});
}

//---------------------------------------------------------------------------------------------------------------------

const unsigned int CPokerRules::GetMaxHandSize() const
{
	return MAX_HAND_SIZE;
}

//---------------------------------------------------------------------------------------------------------------------

CHandValue CPokerRules::Evaluate(const CHand& hand) const
{
	CHandValue result;

	if (hand.GetSize() == MAX_HAND_SIZE)
	{
		const vector<int> rankValues = hand.GetRankValues(false);
		const vector<int> rankCounts = hand.GetRankCounts();
		const bool isSingleSuit = IsSingleSuit(hand);
		const int straightHigh = GetStraightAndHighRank(hand);

		if (isSingleSuit && (straightHigh == Int(ERank::ACE)))
			result.Set(EHandType::ROYAL_FLUSH, {int(ERank::ACE)});
		else if (isSingleSuit && (straightHigh != 0))
			result.Set(EHandType::STRAIGHT_FLUSH, {straightHigh});
		else
		{
			bool hasFour = false, hasThree = false;
			int pairCount = 0;

			for (int rank = Int(ERank::ACE); rank >= Int(ERank::TWO); --rank)
			{
				if		(rankCounts[rank] == 4)	hasFour = true;
				else if (rankCounts[rank] == 3)	hasThree = true;
				else if (rankCounts[rank] == 2)	++pairCount;
			}

			if (hasFour)
				result = EvaluateFourOfAKind(rankCounts);
			else if (hasThree && (pairCount == 1))
				result = EvaluateFullHouse(rankCounts);
			else if (isSingleSuit)
				result.Set(EHandType::FLUSH, rankValues);
			else if (straightHigh != 0)
				result.Set(EHandType::STRAIGHT, {straightHigh});
			else if (hasThree)
				result = EvaluateThreeOfAKind(rankCounts);
			else if (pairCount == 2)
				result = EvaluateTwoPairs(rankCounts);
			else if (pairCount == 1)
				result = EvaluateOnePair(rankValues, rankCounts);
			else
				result = EvaluateHighCard(rankValues);
		}
	}

	return result;
}

//---------------------------------------------------------------------------------------------------------------------

int CPokerRules::Compare(const CHand& hand1, const CHand& hand2) const
{
	int result = 0;
	const CHandValue handValue1 = Evaluate(hand1), handValue2 = Evaluate(hand2);

	if (handValue1 > handValue2)
		result = 1;
	else if (handValue1 < handValue2)
		result = -1;

	return result;
}

//---------------------------------------------------------------------------------------------------------------------