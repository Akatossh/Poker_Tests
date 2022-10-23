#pragma once

#include "Card.h"
#include <vector>

using namespace std;


class Player
{
	enum class Ranking;
	vector<Card*>* HandCards;
	Ranking currentRank = Ranking::none;

	static Ranking rank(vector<Card*>& cards);

	class Container_HP
	{
	public:
		int HP[3][3]{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
		int HPTotal[3]{ 0,0,0 };
		vector<Card*>* MyCards;
		vector<Card*>* Board;
		vector<Card*>* EnemyCards;

		int ahead = 0;
		int tied = 1;
		int behind = 2;
		int index;
	};

public:
	Player();
	void addCard(Card* card);
	void displayCards();
	
	static Ranking rank(vector<Card*>& PlayerCards, vector<Card*>& BoardCards);
	static void sort(vector<Card*>& cards);

	float HandStrenght(vector<Card*>* BoardCard);
	float HandPotential(vector<Card*>* BoardCard);
	vector<Card*>* get_player_cards() { return HandCards; };
	
	void displayRank();
	void set_rank(Ranking rank) { currentRank = rank; };

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

private:

	static void test_fun(vector<Card*>& Hand, vector<Card*>& Board, Container_HP& cHP);

	template<class T>
	void Combination(vector<T>& const_collection, vector<T>& collection, unsigned int offset, unsigned int k, Container_HP& cHP, void (*fun)(vector<T>&, vector<T>&, Container_HP& cHP));
};

