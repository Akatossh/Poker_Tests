#include <iostream>
#include "Deck.h"
#include "Card.h"
#include "Player.h"
#include "Poker.h"

void start_game(int player_num);

int main()
{
    Deck deck;
    Player player;
    //deck.shuffle();
    //player.draw(deck, 21);
    //int i = 0;
    //for (auto card : deck)
    //    cout << i++ << ": " << card << endl;

    //player.draw(deck.draw(2));
    player.draw(Card{ Card::Kind::ace , Card::Color::karo });
    player.draw(Card{ Card::Kind::queen, Card::Color::club });

    cout << player << " ";
    vector<Card> board;
    board.push_back(Card{ Card::Kind::three, Card::Color::heart });
    board.push_back(Card{ Card::Kind::four, Card::Color::club });
    board.push_back(Card{ Card::Kind::jack, Card::Color::heart });
    board.push_back(Card{ Card::Kind::king, Card::Color::heart });
    //board.push_back(Card{ Card::Kind::king, Card::Color::heart });
    //cards.push_back(Card{ Card::Kind::ace, Card::Color::heart });
    //cards.push_back(Card{ Card::Kind::queen, Card::Color::karo });


    //cout << endl <<"rank: " << Poker::rank(cards);

    //cout << endl << Poker::rank(cards) << endl;
    auto HP = player.HandPotential(board);
    //cout << endl << "HP: " << HP;
    //cout << endl << "EHS: " << (player.HandStrength(cards) + (1- player.HandStrength(cards)) * HP);
    //player.give_back(2);
    //auto x = 'a';
    //cin >> x;
}

void start_game(int player_num)
{
    Poker poker;
    
    poker.initialization(player_num);

    for (auto& player : poker.players)
    {
        cout << player;
        cout << " rem_points: " << player.remaining_points();
    }   cout << endl;
}