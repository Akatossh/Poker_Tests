#pragma once
#include <vector>
#include <iostream>
#include "Card.h"

using namespace std;

class Card;

class Player
{
public:
	vector<Card> cards;


	void draw(Card card);
	void draw(vector<Card> adding_card);

	Card give_back();
	vector<Card> give_back(int amount);

	float HandStrength(vector<Card> board);
	float HandPotential(vector<Card> board);
	friend ostream& operator<<(ostream& os, Player player);

};
