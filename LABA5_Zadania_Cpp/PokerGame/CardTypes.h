#pragma once

//---------------------------------------------------------------------------------------------------------------------

enum class ERank : int
{
	TWO = 2,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE
};

inline constexpr int RANK_COUNT = 13;

inline constexpr int Int(ERank rank)
{
	return static_cast<int>(rank);
}

inline ERank& operator++(ERank& rank)
{
	rank = static_cast<ERank>(static_cast<int>(rank) + 1);
	return rank;
}

inline ERank& operator--(ERank& rank)
{
	rank = static_cast<ERank>(static_cast<int>(rank) - 1);
	return rank;
}

//---------------------------------------------------------------------------------------------------------------------

enum class ESuit : int
{
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES
};

inline constexpr int SUIT_COUNT = 4;

inline constexpr int Int(ESuit suit)
{
	return static_cast<int>(suit);
}

inline ESuit& operator++(ESuit& suit)
{
	suit = static_cast<ESuit>(static_cast<int>(suit) + 1);
	return suit;
}

inline ESuit& operator--(ESuit& suit)
{
	suit = static_cast<ESuit>(static_cast<int>(suit) - 1);
	return suit;
}

//---------------------------------------------------------------------------------------------------------------------
