#include "Card.h"

ostream& operator<<(ostream& os, Card card)
{
    card.display();
    return os;
}

void Card::display()
{
    switch (kind)
    {
    case Kind::ace:
        cout << "Ace";
        break;
    case Kind::king:
        cout << "King";
        break;
    case Kind::queen:
        cout << "Queen";
        break;
    case Kind::jack:
        cout << "Jack";
        break;
    case Kind::ten:
        cout << "Ten";
        break;
    case Kind::nine:
        cout << "Nine";
        break;
    case Kind::eight:
        cout << "Eight";
        break;
    case Kind::seven:
        cout << "Seven";
        break;
    case Kind::six:
        cout << "Six";
        break;
    case Kind::five:
        cout << "Five";
        break;
    case Kind::four:
        cout << "Four";
        break;
    case Kind::three:
        cout << "Three";
        break;
    case Kind::two:
        cout << "Two";
        break;

        break;
    default:
        break;
    }

    switch (color)
    {
    case Color::heart:
        cout << (char)3;
        break;
    case Color::karo:
        cout << (char)4;
        break;
    case Color::spade:
        cout << (char)5;
        break;
    case Color::club:
        cout << (char)6;
        break;
    default:
        break;
    }
}

bool Card::operator==(Card card)
{
    if (kind == card.kind)
    {
        return color == card.color;
    }
    return  kind == card.kind;;
}

bool Card::operator!=(Card card)
{
    if (kind == card.kind)
    {
        return color != card.color;
    }
    return  kind != card.kind;
}

bool Card::operator>(Card card)
{
    if (kind == card.kind)
    {
        return color > card.color;
    }
    return kind > card.kind;
}

bool Card::operator>=(Card card)
{
    if (kind == card.kind)
    {
        return color >= card.color;
    }
    return  kind >= card.kind;
}

bool Card::operator<(Card card)
{
    if (kind == card.kind)
    {
        return color < card.color;
    }
    return kind < card.kind;
}

bool Card::operator<=(Card card)
{
    if (kind == card.kind)
    {
        return color <= card.color;
    }
    return  kind <= card.kind;;
}

Card& Card::operator=(Card card)
{
    this->kind = card.kind;
    this->color = card.color;
    return *this;
}