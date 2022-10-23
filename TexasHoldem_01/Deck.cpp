#include <stdlib.h>
#include <time.h> 
#include "Deck.h"
#include "Card.h"

Deck::Deck()
{
	//random values are use in Shuffle() method
	srand(time(NULL));

	for (int i = 1; i != 14; i++)
	{
		for (int j = 0; j != 4; j++)
		{
			cards.push_back(Card(static_cast<Card::Kind>(i + 1), static_cast<Card::Color>(j + 1)));
		}
	}
}

void Deck::display()
{
	for (auto& card : cards)
	{
		card.display();
		cout << endl;
	}
}

Card Deck::draw()
{
	Card card = cards[size() - 1];
	cards.pop_back();
	return card;
}

vector<Card> Deck::draw(int amount)
{
	vector<Card> vec{};
	for (int i = 0; i != amount; i++)
	{
		vec.push_back(draw());
	}
	return vec;
}



void Deck::insert(Card card)
{
	cards.push_back(card);
}

void Deck::insert(Card card, int idx)
{
	cards.insert(cards.begin() + idx, card);
}

void Deck::insert(Card::Kind kind, Card::Color color)
{
	cards.push_back(Card{ kind,color });
}

void Deck::insert(Card::Kind kind, Card::Color color, int idx)
{
	cards.insert(cards.begin() + idx, Card{kind,color});
}

void Deck::insert(vector<Card> inserting_cards)
{
	for (auto card : inserting_cards)
		insert(card);
	
}

int Deck::find(Card my_card)
{
	sort_cards(cards);

	int beg = 0;
	int end = size();
	int idx = (beg + end) / 2;

	while (my_card != cards[idx])
	{
		if (my_card >= cards[idx])
		{
			beg = idx;
			idx = (idx + end) / 2;
		}
		else
		{
			end = idx;
			idx = (beg + idx) / 2;
		}
	}
	
	return idx;
}

int Deck::find(Card::Kind kind, Card::Color color)
{
	return find(Card{kind, color});
}

Card Deck::get(int idx)
{
	Card card = cards[idx];
	cards.erase(cards.begin() + idx);
	return card;
}

vector<Card> Deck::get(int beg, int end)
{
	vector<Card> vec;
	for (int i = beg; i != end; i++)
		vec.push_back(cards[i]);

	for (int i = beg; i != end; i++)
		cards.erase(cards.begin() + beg);

	return vec;
}

void Deck::shuffle()
{
	for (int i = size() - 1; i != 0; i--)
	{
		int r = rand() % i;
		swap(cards[i], cards[r]);
	}
}

Card Deck::check_card_at(int idx)
{
	return cards[idx];
}

void Deck::remove(Card card)
{
	cards.erase(cards.begin() + find(card));
}

void Deck::remove(int idx)
{
	cards.erase(cards.begin() + idx);
}
