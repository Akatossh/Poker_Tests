#include <iostream>
#include "Deck.h"
#include "Card.h"
#include "Player.h"
#include "Poker.h"

using namespace std;


int main()
{
    Deck deck;
    Player player;
    deck.shuffle();

    //player.draw(deck.draw(2));
    player.draw(Card{ Card::Kind::ace , Card::Color::karo });
    player.draw(Card{ Card::Kind::queen, Card::Color::club });
    cout << player << " ";
    vector<Card> cards;
    cards.push_back(Card{ Card::Kind::three, Card::Color::heart });
    cards.push_back(Card{ Card::Kind::four, Card::Color::club });
    cards.push_back(Card{ Card::Kind::jack, Card::Color::heart });
    //cards.push_back(Card{ Card::Kind::five, Card::Color::heart });
    //cards.push_back(Card{ Card::Kind::ace, Card::Color::heart });
   // cout << endl <<"rank: " << Poker::rank(cards);

    cout << endl << Poker::rank(player) << endl;
    auto HP = player.HandPotential(cards);
    cout << endl << "HP: " << HP;
    cout << endl << "EHS: " << (player.HandStrength(cards) + (1- player.HandStrength(cards)) * HP);
    player.give_back(2);
    auto x = 'a';
    cin >> x;
}
