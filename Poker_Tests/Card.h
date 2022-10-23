#pragma once
#include <iostream>
using namespace std;

class Card
{
public:
    enum class Color;
    enum class Kind;
    Color color;
    Kind kind;

public:
    Card() : kind{ Kind::none }, color{ Color::none } {};
    Card(Kind kind, Color color) : kind{ kind }, color{ color } {};
    Card(Card* card) : kind{ card->kind }, color{ card->color } {};
    void display();
    
    Card& operator=(Card card);
    bool operator==(Card card);
    bool operator!=(Card card);
    bool operator>(Card card);
    bool operator>=(Card card);
    bool operator<(Card card);
    bool operator<=(Card card);

    enum class Color
    {
        none,
        heart,
        karo,
        spade,
        club
    };

    enum class Kind
    {
        none,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        jack,
        queen,
        king,
        ace,
    };
};
