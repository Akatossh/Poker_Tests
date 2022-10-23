#pragma once
#include <vector>
#include <iostream>

#include "Player.h"

class Deck;
class Card;


using namespace std;

static class Poker
{
	enum class Ranking;

public: 

	vector<Card> board{};
	int turn_id = 0;
	int players;
	int pool = 0;

	//void next_turn();
	static float rank(vector<Card> cards);
	static float rank(Player player);
	static float rank(vector<Card> hand, vector<Card> board);
	static float rank(vector<Card> hand, vector<Card> board, vector<Card> other_cards);

	friend ostream& operator<<(ostream& os, Ranking rank);

	enum SubTurn
	{
		preflot,
		flop,
		turn,
		river
	};

	enum class Ranking
	{
		none = 0,
		HightCard = 1,
		Pair = 2,
		TwoPairs = 3,
		Tries = 4,
		Straight = 5,
		Flush = 6,
		FullHouse = 7,
		Four = 8,
		StraightFlush = 9,
		RoyalFlush = 10
	};
};


void sort_cards(vector<Card>& cards);
void sert_cards(Deck cards);
class Data;
template<class T, class Fcn>
static void Combination(vector<T>& collection, unsigned int offset, unsigned int k, Fcn fun);
