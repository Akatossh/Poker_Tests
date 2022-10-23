#include <iostream>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Player.h"

using namespace std;

int main()
{
    Deck deck;
    Player player;
    //deck.shuffle();
    player.addCard(new Card(Card::Kind::eight, Card::Color::karo));
    player.addCard(new Card(Card::Kind::four, Card::Color::club));
    player.displayCards();
    vector<Card*> Board;
    Board.push_back(new Card(Card::Kind::two, Card::Color::spade));
    Board.push_back(new Card(Card::Kind::four, Card::Color::karo));
    Board.push_back(new Card(Card::Kind::two, Card::Color::club));
    //Board.push_back(new Card(Card::Kind::jack, Card::Color::heart));
    //Board.push_back(new Card(Card::Kind::ace, Card::Color::karo));
    player.set_rank(player.rank(*player.get_player_cards(), Board));
    player.displayRank();
   // float HS = player.HandStrenght(&Board); TO DO: this function messing with given cards
    float Ppot = player.HandPotential(&Board);
    cout << "Ppot" << Ppot;
    //cout << endl << HS + (1 - HS) * Ppot;

}
