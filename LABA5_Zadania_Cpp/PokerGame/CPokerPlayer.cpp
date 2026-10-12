#include "CPokerPlayer.h"

//---------------------------------------------------------------------------------------------------------------------

CPokerPlayer::CPokerPlayer(const string& name, unsigned int money)
	: m_name(name),
	  m_money(money)
{
}

//---------------------------------------------------------------------------------------------------------------------

const std::string& CPokerPlayer::GetName() const
{
	return m_name;
}

//---------------------------------------------------------------------------------------------------------------------

CHand& CPokerPlayer::GetHand()
{
	return m_hand;
}

//---------------------------------------------------------------------------------------------------------------------

const CHand& CPokerPlayer::GetHand() const
{
	return m_hand;
}

//---------------------------------------------------------------------------------------------------------------------

void CPokerPlayer::ClearHand()
{
	m_hand.Clear();
}

//---------------------------------------------------------------------------------------------------------------------

void CPokerPlayer::SetAndOrganizeHand(const CHand& newHand)
{
	m_hand = newHand;
	OrganizeHand();
}

//---------------------------------------------------------------------------------------------------------------------

void CPokerPlayer::ReceiveCard(const CCard& card)
{
	m_hand.AddCard(card);
}

//---------------------------------------------------------------------------------------------------------------------

void CPokerPlayer::OrganizeHand()
{
	m_hand.Sort();
}

//---------------------------------------------------------------------------------------------------------------------

void CPokerPlayer::ExchangeCard(unsigned int oldCardNumber, const CCard& newCard)
{
	m_hand.ExchangeCard(oldCardNumber, newCard);
}

//---------------------------------------------------------------------------------------------------------------------

int CPokerPlayer::GetMoney() const
{
	return m_money;
}

//---------------------------------------------------------------------------------------------------------------------

bool CPokerPlayer::HasAtLeastMoney(unsigned int amount)
{
	return (m_money >= amount);
}

//---------------------------------------------------------------------------------------------------------------------

void CPokerPlayer::AddMoney(unsigned int amount)
{
	m_money += amount;
}

//---------------------------------------------------------------------------------------------------------------------

bool CPokerPlayer::PayMoney(unsigned int amount)
{
	bool result = HasAtLeastMoney(amount);

	if (result)
		m_money -= amount;

	return result;
}

//---------------------------------------------------------------------------------------------------------------------
