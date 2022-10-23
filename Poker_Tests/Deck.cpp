#include "Deck.h"
#include "Deck.h"
#include "Deck.h"
#include "Deck.h"
#include <stdlib.h>
#include <time.h> 
#include "Deck.h"
#include "Card.h"

Deck::Deck()
{
	//random values are use in Shuffle() method
	srand(time(NULL));

	for (int i = 0; i != 13; i++)
	{
		for (int j = 0; j != 4; j++)
		{
			Card* card = new Card(static_cast<Card::Kind>(i+1), static_cast<Card::Color>(j+1)) ;
			Cards.push_back(card);
		}
	}
}

void Deck::add(Card* card)
{
	Cards.push_back(card);
}

void Deck::add(Card* card, int idx)
{
	Cards.insert(Cards.begin()+idx, card);
}

Card* Deck::draw()
{
	Card* card = Cards[size()-1];
	Cards.pop_back();
	return card;
}

vector<Card*> Deck::draw(int amount)
{
	vector<Card*> cards;
	for (int i = 0; i != amount; i++)
		cards.push_back(draw());
	return cards;
}

Card Deck::check_card_at(int idx)
{
	Card card{};
	card = *Cards[idx];
	return card;
}

void Deck::shuffle()
{
	for (int i = size()-1; i != 0; i--)
	{
		int r = rand() % i;
		swap(Cards[i], Cards[r]);
	}
}

void Deck::sort()
{
	for (int i = 1; i != Cards.size(); i++)
	{
		Card* key = (Cards)[i];
		int j = i - 1;
		while (j >= 0 && *(Cards)[j] > *key)
		{
			(Cards)[j + 1] = (Cards)[j];
			j--;
		}
		(Cards)[j + 1] = key;
	}
}

void Deck::display()
{
	for(auto card : Cards)
	{
		card->display();
	}
}

void Deck::remove(Card* card)
{
	//for (int i = 0; i != Cards.size()-1; i++)
	//{
	//	if (Cards[i]->kind == card->kind && Cards[i]->color == card->color)
	//	{
	//		delete Cards[i];
	//		Cards.erase(Cards.begin()+i);
	//	}
	//}
	sort();

	int beg = 0;
	int end = Cards.size();
	int idx = (beg + end) / 2;

	while (*card != *Cards[idx])
	{
		if (*card >= *Cards[idx])
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

	delete Cards[idx];
	Cards.erase(Cards.begin()+idx);
}




void Deck::remove(Card::Kind kind, Card::Color color)
{
	//for (int i = 0; i != Cards.size(); i++)
	//{
	//	if (Cards[i]->kind == kind && Cards[i]->color == color)
	//	{
	//		Cards.erase(Cards.begin() + i);
	//	}
	//}

	int beg = 0;
	int end = Cards.size();
	int idx = (beg + end) / 2;

	while (kind != Cards[idx]->kind)
	{
		if (kind >= Cards[idx]->kind)
		{
			beg = idx;
			idx = (idx + end) / 2;
		}
		else
		{
			idx = (beg + idx) / 2;
			end = idx;
		}
	}

	delete Cards[idx];
	Cards.erase(Cards.begin() + idx);
}

