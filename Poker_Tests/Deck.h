#pragma once
#include <vector>
#include "Card.h"

using namespace std;

class Deck
{
    vector<Card*> Cards;

public:
    Deck();
    void add(Card* card);
    void add(Card* card, int idx);
    Card* draw();
    vector<Card*> draw(int amount);
    Card check_card_at(int idx);
    int size() { return Cards.size(); }
    void shuffle();
    void sort();
    void display();
    void remove(Card* card);
    void remove(Card::Kind kind, Card::Color color);

};

