#pragma once

#include <string>
#include "CHand.h"

//---------------------------------------------------------------------------------------------------------------------

class CPokerPlayer
{
private:
	using string = std::string;

	string m_name{};
	CHand m_hand{};
	unsigned int m_money{100};

public:
	CPokerPlayer(const string& name, unsigned int money = 100);

	const string& GetName() const;

	CHand& GetHand();
	const CHand& GetHand() const;
	void ClearHand();
	void SetAndOrganizeHand(const CHand& newHand);
	void ReceiveCard(const CCard& card);
	void OrganizeHand();
	void ExchangeCard(unsigned int oldCardNumber, const CCard& newCard);

	int GetMoney() const;
	bool HasAtLeastMoney(unsigned int amount);
	void AddMoney(unsigned int amount);
	bool PayMoney(unsigned int amount);
};

//---------------------------------------------------------------------------------------------------------------------
