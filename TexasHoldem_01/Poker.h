#pragma once
#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Player.h"
#include "Deck.h"

class Card;
class Deck;

const int small_bet = 1;
const int big_bet = 2;

using namespace std;

class Poker
{
	
	enum class Ranking;

public: 
	vector<Card> board{};
	vector<Player> players;
	int turn_id = 0;
	int pool;

	//void next_turn();
	static float rank(vector<Card> cards);
	static float rank(Player player);
	static float rank(vector<Card> hand, vector<Card> board);
	static float rank(vector<Card> hand, vector<Card> board, vector<Card> other_cards);

	void initialization(int num);

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
void sort_cards(Deck cards);
class Data;
template<class T, class Fcn>
void Combination(vector<T>& collection, unsigned int offset, unsigned int k, Fcn fun);
