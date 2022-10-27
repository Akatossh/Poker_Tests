#include "Player.h"
#include "Card.h"
#include <iostream>
#include <algorithm>
#include "Deck.h"
#include "Poker.h"

template<class T, class Fcn>
static void Combination(vector<T>& collection, unsigned int offset, unsigned int k, Fcn fun) {

	static vector<T> combination{};

	if (k == 0) {
		fun(combination);
		return;
	}

	for (unsigned int i = offset; i <= collection.size() - k; ++i) {
		combination.push_back(collection[i]);
		Combination(collection, i + 1, k - 1, fun);
		combination.pop_back();
	}
}

void Player::draw(Deck& deck)
{
	auto card = deck.draw();
	cards.push_back(card);
}

void Player::draw(Deck& deck, int num)
{
	for (int i = 0; i != num; i++)
	{
		auto card = deck.draw();
		cards.push_back(card);
	}
}

void Player::draw(Card card)
{
	cards.push_back(card);
}

void Player::draw(vector<Card> adding_card)
{
	for (auto card : adding_card)
		cards.push_back(card);
}

Card Player::give_back()
{
	Card card = cards[cards.size()-1];
	cards.pop_back();
	return card;
}

vector<Card> Player::give_back(int amount)
{
	vector<Card> cards;
	for (int i = 0; i != amount; i++)
	{
		cards.push_back(give_back());
	}
	return cards;
}

float Player::HandStrength(vector<Card> board)
{
	int ahead = 0;
	int behind = 0;
	int tied = 0;

	float ourrank = Poker::rank(cards, board);

	Deck deck;
	deck.remove(cards);
	deck.remove(board);
	vector<Card> remaining_cards;
	for (auto card : deck)
		remaining_cards.push_back(card);

	Combination(remaining_cards, 0, 2, [&](vector<Card> set) {

			float opprank = Poker::rank(board, set);
			if (ourrank > opprank) ahead++;
			else if (ourrank == opprank) tied++;
			else behind++;
		});
	
	return (ahead+tied/2.0)/(ahead+tied+behind);

}

float Player::HandPotential(vector<Card> board)
{
	long index = 0;
	long ahead = 0;
	long tied = 1;
	long behind = 2;
	long HP[3][3] = {{0, 0,0}, {0,0,0}, {0,0,0}};
	long HPTotal[3] = { 0,0,0 };

	float ourrank = Poker::rank(cards, board);

	Deck deck;
	deck.remove(cards);
	deck.remove(board);
	vector<Card> remaining_cards;
	for (auto& card : deck)
		remaining_cards.push_back(card);

	Combination(remaining_cards, 0, 2, [&](vector<Card> set) {

		float opprank = Poker::rank(set, board);
		if (ourrank > opprank) index = ahead;
		else if (ourrank == opprank) index = tied;
		else index = behind;
		HPTotal[index]++;

		Deck deck2;
		deck2.remove(cards);
		deck2.remove(set);
		deck2.remove(board);
		vector<Card> remaining_cards_2;
		for (auto& card : deck2)
			remaining_cards_2.push_back(card);
		remaining_cards_2.push_back(deck2.draw());

		Combination(remaining_cards_2, 0, 5 - board.size(), [&](vector<Card> set2) {

			vector<Card> temp;
			for (auto& card : board) temp.push_back(card);
			for (auto& card : set2) temp.push_back(card);

			float ourbest = Poker::rank(cards, temp);
			float oppbest = Poker::rank(set, temp);

			if (ourbest > oppbest) HP[index][ahead]++;
			else if (ourbest == oppbest) HP[index][tied]++;
			else HP[index][behind] ++;

		});

	});

	float Ppot = (HP[behind][ahead] + HP[behind][tied] / 2.0 + HP[tied][ahead]/2.0) / ((HPTotal[behind] + HPTotal[tied]));
	//float Npot = 0.0;
	return Ppot;
}

bool Player::add_to_pool(int points, int& pool)
{
	if (this->points < points) return false;

	this->points -= points;
	pool += points;

	return true;
}

ostream& operator<<(ostream& os, Player player)
{
	{
		for (auto card : player.cards)
		{
			os << card << " ";
		}

		return os;
	}
}