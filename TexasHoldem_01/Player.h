#pragma once
#include <vector>
#include <iostream>
#include "Card.h"

using namespace std;

class Card;
class Deck;

class Player
{
	int points = 1000;

public:
	vector<Card> cards;

	void draw(Deck& deck);
	void draw(Deck& deck, int num);
	void draw(Card card);
	void draw(vector<Card> adding_card);

	Card give_back();
	vector<Card> give_back(int amount);

	float HandStrength(vector<Card> board);
	float HandPotential(vector<Card> board);

	bool add_to_pool(int points, int& pool);
	int remaining_points() { return points; };
	friend ostream& operator<<(ostream& os, Player player);

};
