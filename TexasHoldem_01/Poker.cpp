#include "Poker.h"
#include <iostream>
#include "Deck.h"


ostream& operator<<(ostream& os, Poker::Ranking rank)
{
    switch (rank)
    {
    case Poker::Ranking::none:

        break;

    case  Poker::Ranking::HightCard:
        cout << "Hight card" << endl;
        break;

    case  Poker::Ranking::Pair:
        cout << "Pair";
        break;
    case Poker::Ranking::TwoPairs:
        cout << "Two Pairs" << endl;
        break;
    case  Poker::Ranking::Tries:
        cout << "Tries " << endl;
        break;
    case  Poker::Ranking::Straight:
        cout << "Straight";
        break;
    case  Poker::Ranking::Flush:
        cout << "Flush" << endl;
        break;
    case Poker::Ranking::FullHouse:
        cout << "FullHouse" << endl;
        break;
    case  Poker::Ranking::Four:
        cout << "Four";
        break;
    case  Poker::Ranking::StraightFlush:
        cout << "StraightFlus";
        break;
    case  Poker::Ranking::RoyalFlush:
        cout << "RoyalFlush " << endl;
        break;
    default:

        break;
    }

    return os;
}

void sort_cards(vector<Card>& cards)
{
	for (int i = 1; i != cards.size(); i++)
	{
		Card key = (cards)[i];
		int j = i - 1;
		while (j >= 0 && (cards)[j] > key)
		{
			(cards)[j + 1] = (cards)[j];
			j--;
		}
		(cards)[j + 1] = key;
	}
}

void sert_cards(Deck cards)
{
	cout << "TO DO: implement sorting in Poker class";
}

bool check_for_royalStraight(vector<Card> cards)
{
    int checker = 0;


    for (int i = 0; i != cards.size() -1; i++)
    {

        if (static_cast<int>(cards[i].kind) + 1 == static_cast<int>(cards[i + 1].kind))
        {
            checker++;
        }
        else
        {
            if (static_cast<int>(cards[i].kind) != static_cast<int>(cards[i + 1].kind))
            checker = 0;
        }
        if (checker >= 4 and cards[i+1].kind == Card::Kind::ace )
            return true;

    }

    return false;
}

bool chech_for_staight(vector<Card> cards)
{
    //for (int i = 0; i != cards.size() - 1; i++)
    //{
    //    if (static_cast<int>(cards[i].kind) + 1 != static_cast<int>(cards[i + 1].kind))
    //    {
    //        if (cards[cards.size()-1].kind == Card::Kind::ace and cards[0].kind == Card::Kind::two)
    //        {
    //            for (int j = 0; j != cards.size() - 2; j++)
    //            {
    //                if (static_cast<int>(cards[j].kind) + 1 != static_cast<int>(cards[j + 1].kind))
    //                    return false;
    //            }
    //        }
    //        else
    //            return false;
    //    }
    //}

    int checker = 0;


    for (int i = 0; i != cards.size() - 1; i++)
    {

        if (static_cast<int>(cards[i].kind) + 1 == static_cast<int>(cards[i + 1].kind))
        {
            checker++;
        }
        else
        {
            if(static_cast<int>(cards[i].kind) != static_cast<int>(cards[i + 1].kind))
                checker = 0;
        }
        if (checker == 4)
            return true;

    }

    //Ace can also has value of one
    if (cards[0].kind == Card::Kind::two and cards[cards.size() - 1].kind == Card::Kind::ace)
    {
        checker = 0;

        for (int i = 0; i != cards.size() - 1; i++)
        {
            if (static_cast<int>(cards[i].kind) + 1 < static_cast<int>(cards[i + 1].kind))
                return false;

            if (static_cast<int>(cards[i].kind) + 1 == static_cast<int>(cards[i + 1].kind))
            {
                checker++;
            }
            if (checker == 3)
                return true;
        }
    }

    return false;
}

bool chceck_for_flush(vector<Card> cards)
{
    //for (int i = 0; i != cards.size() - 1; i++)
    //{
    //    if (cards[i].color != cards[i + 1].color)
    //        return false;
    //}
    //return true;

    int colors[4] = {0, 0, 0, 0};


    for (int i = 0; i != cards.size(); i++)
    {

        colors[static_cast<int>(cards[i].color)-1]++;
    }

    for (int i = 0; i != 4; i++)
        if (colors[i] >= 5) return true;

    return false;
}

bool chcek_for_stright_flush(vector<Card> cards)
{
    return chceck_for_flush(cards) and chech_for_staight(cards);
}

bool check_for_four(vector<Card> cards)
{
    //if (cards[0].kind == cards[1].kind and cards[1].kind == cards[2].kind and cards[2].kind == cards[3].kind) return true;
    //if (cards[1].kind == cards[2].kind and cards[2].kind == cards[3].kind and cards[3].kind == cards[4].kind) return true;

    int checker = 0;
    for (int i = 0; i != cards.size() - 1; i++)
    {
        if (cards[i].kind == cards[i + 1].kind)
        {
            checker++;
        }
        else
        {
            checker = 0;
        }
        if (checker == 3)
            return true;
    }
    return false;
}

bool check_for_fullhouse(vector<Card> cards)
{
    //if (cards[0].kind == cards[1].kind and cards[2].kind == cards[3].kind and cards[3].kind == cards[4].kind) return true;
    //if (cards[0].kind == cards[1].kind and cards[1].kind == cards[2].kind and cards[3].kind == cards[4].kind) return true;
    //return false;


    int checker = 0;
    bool pair = false;
    bool tries = false;

    for (int i = 0; i != cards.size() - 1; i++)
    {
        if (cards[i].kind == cards[i + 1].kind)
        {
            checker++;
        }
        else
        {
            if (checker == 1)
                pair = true;
            if (checker == 2) 
                tries = true;
            checker = 0;
        }
        if (pair == true and tries == true)
            return true;
        if (pair == true and checker == 2)
            return true;
    }
    return false;
}

bool check_for_doublepair(vector<Card> cards)
{
    //if (cards[0].kind == cards[1].kind and cards[2].kind == cards[3].kind) return true;
    //if (cards[1].kind == cards[2].kind and cards[3].kind == cards[4].kind) return true;
    //if (cards[0].kind == cards[1].kind and cards[3].kind == cards[4].kind) return true;
    //return false;
    int checker = 0;

    for (int i = 0; i != cards.size() - 1; i++)
    {
        if (cards[i].kind == cards[i + 1].kind)
        {
            checker++;
            if (checker == 2) return true;
        }
    }
    return false;
}

bool chec_for_tries(vector<Card> cards)
{
    //for (int i = 0; i != cards.size() - 2; i++)
    //{
    //    if (cards[i].kind == cards[i + 1].kind and cards[i+1].kind == cards[i + 2].kind)
    //        return true;
    //}
    //return false;

    int checker = 0;
    for (int i = 0; i != cards.size() - 1; i++)
    {
        if (cards[i].kind == cards[i + 1].kind)
        {
            checker++;
        }
        else
        {
            checker = 0;
        }
        if (checker == 2)
            return true;
    }
    return false;
}

bool check_for_pair(vector<Card> cards)
{
    for (int i = 0; i != cards.size() - 1; i++)
    {
        if (cards[i].kind == cards[i + 1].kind)
            return true;
    }
    return false;
}

float Poker::rank(vector<Card> copy_cards)
{
    sort_cards(copy_cards);

    if (copy_cards.size() == 2)
    {
        if (check_for_pair(copy_cards)) return static_cast<float>(Poker::Ranking::Pair);
        return static_cast<float>((*max(copy_cards.begin(), copy_cards.end()-1)).kind) / 100.0;
    }


    if (chech_for_staight(copy_cards))
    {
        if (chceck_for_flush(copy_cards))
        {
            if(check_for_royalStraight(copy_cards))
                return static_cast<float>(Poker::Ranking::RoyalFlush);
            else
                return static_cast<float>(Poker::Ranking::StraightFlush);
        }
        else
            return static_cast<float>(Poker::Ranking::Straight);
    }

    if(chceck_for_flush(copy_cards)) return static_cast<float>(Poker::Ranking::Flush);
    if(check_for_four(copy_cards)) return static_cast<float>(Poker::Ranking::Four);
    if(check_for_fullhouse(copy_cards)) return static_cast<float>(Poker::Ranking::FullHouse);
    if (chec_for_tries(copy_cards)) return static_cast<float>(Poker::Ranking::Tries);
    if(check_for_doublepair(copy_cards)) return static_cast<float>(Poker::Ranking::TwoPairs);
    if (check_for_pair(copy_cards)) return static_cast<float>(Poker::Ranking::Pair);

    return static_cast<float>((*max(copy_cards.begin(), copy_cards.end()-1)).kind) /100.0;
}

float Poker::rank(Player player)
{
    float temp = rank(player.cards);

    return temp;
}

float Poker::rank(vector<Card> hand, vector<Card> board)
{
    vector<Card> cards;
    for (auto& card : hand)
        cards.push_back(card);
    for (auto& card : board)
        cards.push_back(card);

    //float best = 0;
    //Combination(cards, 0, 5, [&](vector<Card> set)->void {
    //    auto temp = rank(set);
    //    if (temp > best) best = temp;
    //});

    return rank(cards);
}

float Poker::rank(vector<Card> hand, vector<Card> board, vector<Card> other_cards)
{
    cout << "TO DO: ";
    return 0.0;
}

void Poker::initialization(int num)
{
    //for (int i = 0; i != num; i++)
    //    players.push_back(Player());

    //this->pool = 0;

    //for (auto& player : players)
    //    player.draw(deck.draw(2));
    //
    //int rnd = rand() % players.size();
    //players[rnd].add_to_pool(small_bet, this->pool);
    //if (rnd + 1 > players.size()) rnd = 0;
    //players[rnd+1].add_to_pool(big_bet, this->pool);


}

template<class T, class Fcn>
static void Combination(vector<T>& collection, unsigned int offset, unsigned int k, Fcn fun) {

    static vector<T> combination{};

    if (k == 0) {
        fun(combination);
        return;
    }

    for (unsigned int i = offset; i <= collection.size() - k; ++i) {
        combination.push_back(collection[i]);
        Combination(collection, i + 1, k - 1, fun);
        combination.pop_back();
    }
}