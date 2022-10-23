#include "Player.h"
#include "Deck.h"

void debug_display_cards(vector<Card*>* Cards)
{
    //cout << endl;
    for (auto& card : *Cards)
    {
        card->display();
        cout << " ";
    }
}

void debug_display_cards(vector<Card*>* Cards1, vector<Card*>* Cards2)
{
    //cout << endl;
    for (auto& card : *Cards1)
    {
        card->display();
        cout << " ";
    }

    for (auto& card : *Cards2)
    {
        card->display();
        cout << " ";
    }
}

void Player::test_fun(vector<Card*>& Hand, vector<Card*>& Board, Container_HP& cHP)
{
    static int i= 0;

    
    auto oppbest = rank(Hand, Board);
    debug_display_cards(&Hand,&Board);
    cout << endl;
    
    vector<Card*> ourCards;
    for (int i = 2; i != Hand.size(); i++)
        ourCards.push_back(Hand[i]);
    for (auto card : *(cHP.MyCards))
        ourCards.push_back(card);

    auto ourbest = rank(ourCards, Board);

    if (ourbest > oppbest)  cHP.HP[cHP.index][cHP.ahead] += 1;
    else if (ourbest == oppbest)  cHP.HP[cHP.index][cHP.tied] += 1;
    else cHP.HP[cHP.index][cHP.behind] += 1;
}

template<class T>
void Player::Combination(vector<T>& const_collection, vector<T>& collection, unsigned int offset, unsigned int k, Container_HP& cHP,void (*fun)(vector<T>&, vector<T>&, Container_HP& cHP)) {

    static vector<T> combination{};

    if (k == 0) {
        fun(const_collection, combination, cHP);
        return;
    }

    for (unsigned int i = offset; i <= collection.size() - k; ++i) {
        combination.push_back(collection[i]);
        Combination(const_collection, collection, i + 1, k - 1, cHP, fun);
        combination.pop_back();
    }
}



float Player::HandStrenght(vector<Card*>* BoardCards)
{
	float ahead = 0;
	float tied = 0;
	float behind = 0;

	//Create temporary deck
	Deck TDeck;
    TDeck.remove((*HandCards)[0]);
    TDeck.remove((*HandCards)[1]);
    if (BoardCards->size() > 0)
    {
        TDeck.remove((*BoardCards)[0]);
        TDeck.remove((*BoardCards)[1]);
        TDeck.remove((*BoardCards)[2]);
    }


	vector<Card*> Cards;
	for (auto& BoardCard : *BoardCards)
	{
		Cards.push_back(BoardCard);
	}
	
    Player::Ranking ourrank = rank(*HandCards, *BoardCards);

    Cards.push_back(TDeck.draw());
	while (TDeck.size() != 0)
	{
		for (int i = 0; i != TDeck.size()-1; i++)
		{
			Cards.push_back(new Card(TDeck.check_card_at(i)));
            Player::Ranking opprank = rank(Cards);
			if (ourrank > opprank) ahead++;
			else if (ourrank == opprank) tied++;
			else behind++;
            delete Cards[Cards.size() - 1];
			Cards.erase(Cards.end() -1);
		}

        if (Cards.size() == 1)
        {
            delete Cards[0];
            Cards.erase(Cards.begin());
            Cards.push_back(TDeck.draw());
        }
        else
        {
            delete Cards[2];
            Cards.erase(Cards.begin() + 2);
            Cards.push_back(TDeck.draw());
        }

	}

	float val = (ahead + tied / 2) / (ahead + tied + behind);
	return val;
}

float Player::HandPotential(vector<Card*>* BoardCards)
{



    Container_HP cHP;


    Ranking ourbest;
    Ranking oppbest;
    int debug_iters = 0;

    const int BoardCardsNUM = BoardCards->size();
    //Create temporary deck
    Deck TDeck;
    TDeck.remove((*HandCards)[0]);
    TDeck.remove((*HandCards)[1]);
    for (auto& card : *BoardCards)
        TDeck.remove((card));

    vector<Card*> oppcards;
    oppcards.push_back(TDeck.draw());
    //oppcards.push_back(new Card());

    Ranking ourrank = rank( *HandCards, *BoardCards);

    //for each posible combination of 2 enemy cards left in the deck
    while (TDeck.size() != 0)
    {
        for (int i = 0; i != TDeck.size() - 1; i++)
        {
            oppcards.push_back(TDeck.draw());
            //debug_display_cards(&oppcards);
            //cout << endl;

            Ranking opprank = rank( oppcards, *BoardCards);
            if (ourrank > opprank) cHP.index = cHP.ahead;
            else if (ourrank == opprank)  cHP.index = cHP.tied;
            else  cHP.index = cHP.behind;
            cHP.HPTotal[cHP.index]++;


            //if all 5 cards are on board
            if (BoardCardsNUM == 5)
            {
                Ranking ourbest = rank(*HandCards, *BoardCards);
                Ranking oppbest = rank(oppcards, *BoardCards);
                if (ourbest > oppbest) cHP.HP[cHP.index][cHP.ahead]++;
                else if (ourbest == oppbest) cHP.HP[cHP.index][cHP.tied]++;
                else cHP.HP[cHP.index][cHP.behind];
                continue;
            }
                
           
            vector<Card*> collection{};
            for (auto card : oppcards)
                collection.push_back(card);
            for (auto card : *BoardCards)
                collection.push_back(card);
          
            vector<Card*> TDeck2{};
            for (int i = 0; i != TDeck.size(); i++)
                    TDeck2.push_back(new Card(TDeck.check_card_at(i)));

         

            cHP.MyCards = HandCards;
            cHP.EnemyCards = &oppcards;

           if(TDeck2.size() > 5 - BoardCards->size())
                Combination(collection, TDeck2,0, 5 - BoardCards->size(), cHP, &this->test_fun);
            
            //delete oppcards[1];
            oppcards.erase(oppcards.begin()+1);
            
            TDeck.add(oppcards[oppcards.size()-1], 0);
        }
        

        //oppcards.erase(oppcards.begin());
        oppcards[0] = (TDeck.draw());
        //oppcards.push_back(new Card{});
    }

    cout << endl << "Debug iters: " << debug_iters;
    //Ppot
    float Ppot = (cHP.HP[cHP.behind][cHP.ahead] + cHP.HP[cHP.behind][cHP.tied] / 2 + cHP.HP[cHP.tied][cHP.ahead] / 2) / (cHP.HPTotal[cHP.behind]+ cHP.HPTotal[cHP.tied]);
    float Npot = (cHP.HP[cHP.ahead][cHP.behind] + cHP.HP[cHP.tied][cHP.behind] / 2 + cHP.HP[cHP.ahead][cHP.tied] / 2) / (cHP.HPTotal[cHP.ahead] + cHP.HPTotal[cHP.tied]);
    return Ppot;
}

Player::Player()
{
    HandCards = new vector<Card*>();
}

void Player::addCard(Card* card)
{
    HandCards->push_back(card);
}

void Player::displayCards()
{
    for (auto* card : *HandCards)
    {
        card->display();
    }
}

Player::Ranking Player::rank(vector<Card*>& In_cards)
{
    Player::Ranking currentRank = Player::Ranking::none;
    vector<Card*> CardsCopy;
    for (auto card : In_cards)
    {
        CardsCopy.push_back(new Card{ card->kind, card->color });
    }
    sort(CardsCopy);
    vector<Card*>& cards = CardsCopy;

    //Check for Straight
    int i = 0;
    Card::Kind lastKind = Card::Kind::none;
    for (auto card : cards)
    {
        if (static_cast<int>(lastKind) + 1 == static_cast<int>(card->kind)) i++;
        lastKind = card->kind;
    }
    if (i == 4)
    {
        currentRank = Player::Ranking::Straight;
    }

    //Check for Four and House
    int j = 0;
    lastKind = Card::Kind::none;
    for (auto card : cards)
    {
        if (static_cast<int>(lastKind) == static_cast<int>(card->kind)) j++;
        lastKind = card->kind;
    }
    if (j == 3)
    {
        if ((cards)[0]->kind == (cards)[1]->kind and (cards)[3]->kind == (cards)[4]->kind)
            currentRank = Player::Ranking::FullHouse;
        else
            currentRank = Player::Ranking::Four;
    }
    //Check for tries
    if (j == 2)
    {
        if (cards[2]->kind == cards[0]->kind || cards[2]->kind == cards[4]->kind
            || (cards[2]->kind == cards[1]->kind && cards[2]->kind == cards[3]->kind))
            currentRank = Player::Ranking::Tries;
        else
            currentRank = Player::Ranking::TwoPairs;
    }
    //Check for pair
    if (j == 1)
    {
        currentRank = Player::Ranking::Pair;
    }

    //Check for Flush and StraightFlush
    i = 0;
    Card::Color lastColor = Card::Color::none;
    for (auto card : cards)
    {
        if (static_cast<int>(lastColor) == static_cast<int>(card->color)) i++;
        lastColor = card->color;
    }
    if (i == 4)
    {
        if (currentRank == Player::Ranking::Straight)
            currentRank = Player::Ranking::StraightFlush;
        else
            currentRank = Player::Ranking::Flush;
    }

    //Chech for RoyalFlush
    if (currentRank == Player::Ranking::StraightFlush)
    {
        if ((cards)[4]->kind == Card::Kind::ace)
        {
            currentRank = Player::Ranking::RoyalFlush;
        }
    }

    //If non elese it is HighCard
    if (currentRank == Player::Ranking::none)
        currentRank = Player::Ranking::HightCard;

    return currentRank;
}

//Gets from 2 to 7 cards and find the best rank for them
Player::Ranking Player::rank(vector<Card*>& PlayerCards, vector<Card*>& BoardCards)
{
    vector<Card*> Cards;
    Ranking ran = Ranking::HightCard;

    if (BoardCards.size() == 0 || BoardCards.size() == 3)
    {
    for (auto& card : PlayerCards)
        Cards.push_back(card);

    for (auto& card : BoardCards)

        Cards.push_back(card);

        return rank(Cards);
    }
    else
    {
        vector<Card*> BoardCardsCopy;
        for (auto card : BoardCards)
        {
            BoardCardsCopy.push_back(new Card{ card->kind, card->color });
        }

        for (auto& card : PlayerCards)
            Cards.push_back(card);

        //draw cards to 4
        for(int i=0;Cards.size() < 4; i++)
        {
            Cards.push_back(BoardCardsCopy[0]);
            BoardCardsCopy.erase(BoardCardsCopy.begin());
        }

        Cards.push_back(new Card{});
        while (BoardCardsCopy.size() > 0)
        {
            for (auto& x : BoardCardsCopy)
            {
                Cards[4] = x;
                auto temp = rank(Cards);
                //debug_display_cards(&Cards);
                if (temp > ran)
                    ran = temp;
            }

            Cards.erase(Cards.begin());
            Cards.push_back(BoardCardsCopy[0]);
            delete BoardCardsCopy[0];
            BoardCardsCopy.erase(BoardCardsCopy.begin());
        }

    }

    return ran;
}

void Player::sort(vector<Card*>& cards)
{
	for (int i = 1; i != cards.size(); i++)
	{
		Card* key = (cards)[i];
		int j = i - 1;
		while (j >= 0 && *(cards)[j] > *key)
		{
			(cards)[j + 1] = (cards)[j];
			j--;
		}
		(cards)[j + 1] = key;
	}
}

void Player::displayRank()
{
    switch (currentRank)
    {
    case Player::Ranking::none:

        break;

    case  Player::Ranking::HightCard:
        cout << "Hight card" << endl;
        break;

    case  Player::Ranking::Pair:
        cout << "Pair";
        break;
    case Player::Ranking::TwoPairs:
        cout << "Two Pairs" << endl;
        break;
    case  Player::Ranking::Tries:
        cout << "Tries " << endl;
        break;
    case  Player::Ranking::Straight:
        cout << "Straight";
        break;
    case  Player::Ranking::Flush:
        cout << "Flush" << endl;
        break;
    case Player::Ranking::FullHouse:
        cout << "FullHouse" << endl;
        break;
    case  Player::Ranking::Four:
        cout << "Four";
        break;
    case  Player::Ranking::StraightFlush:
        cout << "StraightFlus";
        break;
    case  Player::Ranking::RoyalFlush:
        cout << "RoyalFlush " << endl;
        break;
    default:

        break;
    }
}

