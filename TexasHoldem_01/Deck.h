#pragma once
#include <vector>
#include "Card.h"
#include "Poker.h"

using namespace std;

class Deck
{
    vector<Card> cards;

public:
    Deck();
    
    Card draw();
    vector<Card> draw(int amount);

    void insert(Card card);
    void insert(Card card, int idx);
    void insert(Card::Kind kind, Card::Color color);
    void insert(Card::Kind kind, Card::Color color, int idx);
    void insert(vector<Card> inserting_cards);

    void remove(Card card);
    void remove(Card::Kind kind, Card::Color color);
    void remove(vector<Card> removeing_cards)
    {
        for (auto card : removeing_cards) remove(card);
    };
    void remove(int idx);

    int find(Card card);
    int find(Card::Kind kind, Card::Color color);

    Card get(int idx);
    vector<Card> get(int beg, int end);

    Card check_card_at(int idx);

    void shuffle();
    void display();
    int size() { return cards.size(); };

private:
    class iterator {
        Card* curr;
    public:
        iterator(Card* card) : curr(card) { };
        iterator& operator++() { curr = curr++; return *this; };
        iterator& operator--() { curr = curr--; return *this; };
        Card& operator*() { return *curr; };
        bool operator==(const iterator& b) const { return curr == b.curr; };
        bool operator!=(const iterator& b) const { return curr != b.curr; };
    };

public:
    iterator begin() { return &cards[0]; };
    iterator end() { return &(*(cards.end()-1))+1; };
};


