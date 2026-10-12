#pragma once

#include "..\CIOStream.h"
#include "CDeck.h"
#include "CPokerPlayer.h"
#include "CPokerRules.h"

//---------------------------------------------------------------------------------------------------------------------

class CPokerGame
{
private:
	using string = std::string;

	const unsigned int m_raiseAmount{10};
	unsigned int m_pot{};
	CIOStream m_ios{};
	CDeck m_deck{};
	CPokerRules m_rules{};
	CPokerPlayer m_player{"Player One"};
	CPokerPlayer m_computer{"ATARI"};

	void PlayRound();
	void DealCards(CPokerPlayer& player);
	void ShowHand(const CPokerPlayer& player);
	void ExchangePlayerCards();
	void ExchangeComputerCards();
	bool InitPot();
	bool BettingRound();
	void ShowResult();
	bool AskPlayAgain();
	bool HasEnoughMoney() const;
	void AwardPot(CPokerPlayer& player);

public:
	void Run();
};

//---------------------------------------------------------------------------------------------------------------------