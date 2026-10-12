#include "CPokerGame.h"

#include <Windows.h>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include "..\StrUtils.h"

//---------------------------------------------------------------------------------------------------------------------

void CPokerGame::Run()
{
	const UINT originalOutputCP = GetConsoleOutputCP();
	const UINT originalInputCP = GetConsoleCP();

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	bool playAgain = true;

	while (playAgain)
	{
		PlayRound();
		
		if (HasEnoughMoney())
			playAgain = AskPlayAgain();
		else
		{
			m_ios.PrintLine("\nKoniec gry. Jeden z graczy nie ma juz zetonow.");
			playAgain = false;
		}
	}

	SetConsoleOutputCP(originalOutputCP);
	SetConsoleCP(originalInputCP);
}

//---------------------------------------------------------------------------------------------------------------------

void CPokerGame::PlayRound()
{
	m_ios.ClearScreen();
	const string suits = {"| \xE2\x99\xA3 \xE2\x99\xA6 \xE2\x99\xA5 \xE2\x99\xA0 |"};
	string caption = suits + "        GRA W POKERA Z KOMPUTEREM        " + suits;
	string line = string(caption.length() - 16, '-');
	m_ios.PrintLine(line);
	m_ios.PrintLine(caption);
	m_ios.PrintLine(line);
	m_ios.PrintLine();

	if (InitPot())
	{
		m_deck.Shuffle();
		m_player.ClearHand();
		m_computer.ClearHand();

		DealCards(m_player);
		DealCards(m_computer);
		
		m_ios.PrintLine("--- KARTY GRACZA ---");
		ShowHand(m_player);
		m_ios.PrintLine();

		bool continueRound = BettingRound();
		if (continueRound)
		{
			ExchangePlayerCards();
			ExchangeComputerCards();

			m_ios.PrintLine();
			m_ios.PrintLine("--- KARTY GRACZA PO WYMIANIE ---");
			ShowHand(m_player);
			m_ios.PrintLine();

			continueRound = BettingRound();
		}

		if (continueRound)
			ShowResult();
	}
}

//---------------------------------------------------------------------------------------------------------------------

void CPokerGame::DealCards(CPokerPlayer& player)
{
	const unsigned int maxHandSize = m_rules.GetMaxHandSize();

	for (unsigned int i = 0; i < maxHandSize; ++i)
		player.ReceiveCard(m_deck.Draw());

	player.OrganizeHand();	
}

//---------------------------------------------------------------------------------------------------------------------

void CPokerGame::ShowHand(const CPokerPlayer& player)
{
	string text = player.GetName() + ":   ";

	for (unsigned int i = 0; i < player.GetHand().GetSize(); ++i)
		text += "K" + StrUtils::UIntToStr(i + 1) + ": [" + player.GetHand().GetCard(i).ToString() + "]   ";

	m_ios.PrintLine(text);
}

//---------------------------------------------------------------------------------------------------------------------

void CPokerGame::ExchangePlayerCards()
{
	const unsigned int maxHandSize = m_rules.GetMaxHandSize();
	std::vector<unsigned int> toExchange;

	m_ios.PrintLine("Podaj numery kart do wymiany oddzielane spacja (np.: 1 2 5).");
	m_ios.PrintLine("Wpisz 0, aby zachowac wszystkie karty (brak wymiany).");

	bool validInput = false;
	while (!validInput)
	{
		string inputString = "";
		if (m_ios.ReadString("Karty do wymiany: ", inputString))
		{
			std::istringstream stream(inputString);
			string singleValueAsString = ""; 
			bool valid = true;
			while ((stream >> singleValueAsString) && valid)
			{
				unsigned int cardNumber = maxHandSize + 1;
				if (StrUtils::StrToUInt(singleValueAsString, cardNumber) && (cardNumber <= maxHandSize))
				{
					if ((toExchange.size() < maxHandSize) &&
						(std::find(toExchange.begin(), toExchange.end(), cardNumber) == toExchange.end()) &&
						((cardNumber > 0) || ((toExchange.size() == 0) && (cardNumber == 0))))
					{
						toExchange.push_back(cardNumber);
					}
					else
						valid = false;
				}
				else
					valid = false;
			}

			validInput = valid && (toExchange.size() > 0);
		}

		if (!validInput)
		{
			toExchange.clear();
			m_ios.PrintLine("\nNieprawidlowe dane. Podaj numery kart do wymiany (od 1 do " +
						   StrUtils::UIntToStr(maxHandSize) + ") lub samo 0 (rezygnacja z wymiany).");
		}
	}

	if (validInput && !((toExchange.size() == 1) && (toExchange[0] == 0)))
	{
		for (unsigned int i = 0; i < toExchange.size(); ++i)
			m_player.ExchangeCard(toExchange[i], m_deck.Draw());

		m_player.OrganizeHand();
	}
}

//---------------------------------------------------------------------------------------------------------------------

void CPokerGame::ExchangeComputerCards()
{
/*
	Simplified AI, computer game logic. The computer keeps:
		- a pair,
		- two pairs,
		- three of a kind,
		- four of a kind.
	In the case of two pairs, it will keep both pairs.
*/
	const CHand& currentHand = m_computer.GetHand();
	CHand newHand;

	std::vector<int> rankCounts = currentHand.GetRankCounts();

	for (unsigned int i = 0; i < currentHand.GetSize(); ++i)
	{
		const CCard& card = currentHand.GetCard(i);
		if (rankCounts[Int(card.GetRank())] >= 2)
			newHand.AddCard(card);
	}

	const unsigned int cardsToDraw = m_computer.GetHand().GetSize() - newHand.GetSize();

	for (unsigned int i = 0; i < cardsToDraw; ++i)
		newHand.AddCard(m_deck.Draw());

	m_computer.SetAndOrganizeHand(newHand);
}

//---------------------------------------------------------------------------------------------------------------------

bool CPokerGame::InitPot()
{
	bool result = false;
	m_pot = 0;

	if (m_computer.HasAtLeastMoney(m_raiseAmount) && m_player.HasAtLeastMoney(m_raiseAmount))
	{
		m_computer.PayMoney(m_raiseAmount);
		m_player.PayMoney(m_raiseAmount);
		m_pot += (2 * m_raiseAmount);
		m_ios.PrintLine("Komputer i gracz daja do puli po " + StrUtils::IntToStr(m_raiseAmount) + " zetonow.");
		m_ios.PrintLine();
		result = true;
	}

	return result;
}

//---------------------------------------------------------------------------------------------------------------------

bool CPokerGame::BettingRound()
{
	// Implemented very simple bidding logic for a computer player.

	bool result = true;
	unsigned int computerContribution = 0, playerContribution = 0;
	const CHandValue computerValue = m_rules.Evaluate(m_computer.GetHand());

	m_ios.PrintLine("Liczba zetonow komputera: " + StrUtils::IntToStr(m_computer.GetMoney()));
	m_ios.PrintLine("Liczba zetonow gracza: " + StrUtils::IntToStr(m_player.GetMoney()));

	if (computerValue.GetType() >= EHandType::PAIR)
	{
		if (m_computer.PayMoney(m_raiseAmount))
		{
			computerContribution += m_raiseAmount;
			m_pot += m_raiseAmount;
			m_ios.PrintLine("Komputer stawia " + StrUtils::IntToStr(m_raiseAmount) + " zetonow.");
		}
		else
			m_ios.PrintLine("Komputer nie moze wiecej postawic.");
	}
	else
		m_ios.PrintLine("Komputer czeka.");
	
	m_ios.PrintLine("Pula: " + StrUtils::IntToStr(m_pot));
	m_ios.PrintLine();
	m_ios.PrintLine("Decyzja gracza " + m_player.GetName() + ":");
	m_ios.PrintLine("[1] Pas");
	m_ios.PrintLine("[2] Czekanie/sprawdzanie");
	m_ios.PrintLine("[3] Podbicie o " + StrUtils::IntToStr(m_raiseAmount));
	m_ios.PrintLine();
	
	int choice = 0;
	while ((choice < 1) || (choice > 3))
		m_ios.ReadInt("Twoj wybor: ", choice);

	if (choice == 1)
	{
		m_ios.PrintLine("Pasujesz. Komputer wygrywa pule.");
		AwardPot(m_computer);
		result = false;
	}
	else if (choice == 2)
	{
		if (computerContribution > 0)
		{
			unsigned int delta = computerContribution - playerContribution;
			if (m_player.PayMoney(delta))
			{
				m_pot += delta;
				m_ios.PrintLine("Wyrownujesz stawke.");
				m_ios.PrintLine();
			}
			else
			{
				m_ios.PrintLine("Nie masz wystarczajacej liczby zetonow. Pasujesz.");
				AwardPot(m_computer);
				result = false;
			}
		}
		else
			m_ios.PrintLine("Czekasz.");
	}
	else if (choice == 3)
	{
		playerContribution = computerContribution + m_raiseAmount;

		if (m_player.PayMoney(playerContribution))
		{
			m_pot += playerContribution;
			m_ios.PrintLine("Podbijasz stawke.");

			const bool computerCalls = (computerValue.GetType() >= EHandType::THREE_OF_A_KIND);
			unsigned int delta = playerContribution - computerContribution;
			if (computerCalls && m_computer.PayMoney(delta))
			{
				m_pot += delta;
				m_ios.PrintLine("Komputer sprawdza.");
			}
			else
			{
				m_ios.PrintLine("Komputer pasuje. Wygrywasz pule.");
				AwardPot(m_player);
				result = false;
			}
		}
		else
		{
			m_ios.PrintLine("Nie masz wystarczajacej liczby zetonow.");
			result = false;
			AwardPot(m_computer);
		}
	}

	return result;
}

//---------------------------------------------------------------------------------------------------------------------

void CPokerGame::ShowResult()
{
	const CHandValue playerValue = m_rules.Evaluate(m_player.GetHand());
	const CHandValue computerValue = m_rules.Evaluate(m_computer.GetHand());
	
	m_ios.PrintLine("--- KARTY KOMPUTERA ---");
	ShowHand(m_computer);
	m_ios.PrintLine();
	m_ios.PrintLine("--- KARTY GRACZA ---");
	ShowHand(m_player);
	m_ios.PrintLine();
	m_ios.PrintLine("Uklad gracza: " + playerValue.GetHandName());
	m_ios.PrintLine("Uklad komputera: " + computerValue.GetHandName());
	m_ios.PrintLine();

	const int comparison = m_rules.Compare(m_player.GetHand(), m_computer.GetHand());
	if (comparison > 0)
	{
		m_ios.PrintLine("WYGRYWA: " + m_player.GetName() + "!");
		AwardPot(m_player);
	}
	else if (comparison < 0)
	{
		m_ios.PrintLine("WYGRYWA: " + m_computer.GetName() + "!");
		AwardPot(m_computer);
	}
	else
	{
		m_ios.PrintLine("REMIS. Pula zostaje podzielona.");

		const int playerShare = m_pot / 2;
		m_player.AddMoney(playerShare);
		m_computer.AddMoney(playerShare);
		m_pot = 0;
	}

	m_ios.PrintLine();
	m_ios.PrintLine("Aktualny stan zetonow:");
	m_ios.PrintLine("GRACZ: " + StrUtils::IntToStr(m_player.GetMoney()));
	m_ios.PrintLine("KOMPUTER: " + StrUtils::IntToStr(m_computer.GetMoney()));
	m_ios.PrintLine();
}

//---------------------------------------------------------------------------------------------------------------------

void CPokerGame::AwardPot(CPokerPlayer& player)
{
	player.AddMoney(m_pot);
	m_pot = 0;
}

//---------------------------------------------------------------------------------------------------------------------

bool CPokerGame::HasEnoughMoney() const
{
	return (m_player.GetMoney() >= m_raiseAmount) && (m_computer.GetMoney() >= m_raiseAmount);
}

//---------------------------------------------------------------------------------------------------------------------

bool CPokerGame::AskPlayAgain()
{
	bool result = false;
	int choice = 0;

	m_ios.PrintLine();
	m_ios.PrintLine("Gramy dalej?");
	m_ios.PrintLine("[1] - Kolejna runda");
	m_ios.PrintLine("[0] - Koniec gry");

	if (m_ios.ReadInt("Wybor: ", choice))
		result = (choice == 1);

	return result;
}

//---------------------------------------------------------------------------------------------------------------------
