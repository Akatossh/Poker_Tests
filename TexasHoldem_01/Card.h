#pragma once
#include <iostream>
using namespace std;


class Card
{
    enum class Color;
    enum class Kind;

public:
    Color color;
    Kind kind;

    Card() : kind{ Kind::none }, color{ Color::none } {};
    Card(Kind kind, Color color) : kind{ kind }, color{ color } {};
    Card(Card* card) : kind{ card->kind }, color{ card->color } {};
    void display();

    Card& operator=(Card card);
    bool operator==(Card card);
    bool operator!=(Card card);
    bool operator>(Card card);
    bool operator<(Card card) const;
    bool operator>=(Card card);
    bool operator<(Card card);
    bool operator<=(Card card);
    

    enum class Color
    {
        none = 0,
        heart = 1,
        karo = 2,
        spade = 3,
        club = 4
    };

    enum class Kind
    {
        none =0,
        two = 2,
        three = 3,
        four = 4,
        five = 5,
        six = 6,
        seven = 7,
        eight = 8,
        nine = 9,
        ten = 10,
        jack = 11,
        queen = 12,
        king = 13,
        ace = 14,
    };
};

ostream& operator<<(ostream& os, Card card);