// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <vector>
#include <fstream>
#include <istream>
#include "Card.h"
#include "Pack.h"
#include "Player.h"

using namespace std;

class Game {
    private:
    vector<Player*> players;
    Pack deck;
    Card upcard;
    int score[2];
    int dealer_ind;
    int order_up_ind;
    string trump;

    public:
    Game(vector<Player*> players, istream& fin) : 
            players(players), deck(Pack(fin)), score{0,0}, dealer_ind(0) {}

    ~Game() {
        for(size_t i=3; i>-1; --i) {
            delete players[i];
        }
    }

    void shuffle() {
        deck.shuffle();
    }

    void deal() {
        for(int i=0; i<3; ++i) {
            players[(dealer_ind + 1)%4]->add_card(deck.deal_one());
        }
        for(int i=0; i<2; ++i) {
            players[(dealer_ind + 2)%4]->add_card(deck.deal_one());
        }
        for(int i=0; i<3; ++i) {
            players[(dealer_ind + 3)%4]->add_card(deck.deal_one());
        }
        for(int i=0; i<2; ++i) {
            players[(dealer_ind)%4]->add_card(deck.deal_one());
        }
        for(int i=0; i<2; ++i) {
            players[(dealer_ind + 1)%4]->add_card(deck.deal_one());
        }
        for(int i=0; i<3; ++i) {
            players[(dealer_ind + 2)%4]->add_card(deck.deal_one());
        }
        for(int i=0; i<2; ++i) {
            players[(dealer_ind + 3)%4]->add_card(deck.deal_one());
        }
        for(int i=0; i<3; ++i) {
            players[(dealer_ind)%4]->add_card(deck.deal_one());
        }
        upcard = deck.deal_one();
    }

    void making_phase() {
        string order_up_suit;
        bool ordered_up = false;
        for(int i=1; i<5 && !ordered_up; ++i) {
            bool is_dealer = (dealer_ind+i)%4 == dealer_ind;
            if(players[(dealer_ind+i)%4]->make_trump(upcard,is_dealer,1,order_up_suit)){
                cout << *players[(dealer_ind+i)%4] << " orders up " 
                << order_up_suit << endl;
                players[(dealer_ind)%4]->add_and_discard(upcard);
                order_up_ind = (dealer_ind+i)%4;
                ordered_up = true;
            }
            else {
                cout << *players[(dealer_ind+i)%4] << " passes" << endl;
            }
        }
        for(int i=1; i<5 && !ordered_up; ++i) {
            bool is_dealer = (dealer_ind+i)%4 == dealer_ind;
            if(players[(dealer_ind+i)%4]->make_trump(upcard,is_dealer,2,order_up_suit)){
                order_up_ind = (dealer_ind+i)%4;
                cout << *players[(dealer_ind+i)%4] << " orders up " 
                << order_up_suit << endl;
                ordered_up = true;
            }
            else {
                cout << *players[(dealer_ind+i)%4] << " passes" << endl;
            }
        }
        trump = order_up_suit;
    }



    int first_trick_taking(int &t1_tricks_won, int &t2_tricks_won) {
        vector<Card> played_cards;
        vector<int> played_ind;
        Card c1 = players[(dealer_ind+1)%4]->lead_card(trump);
        played_cards.push_back(c1);
        played_ind.push_back((dealer_ind+1)%4);
        cout << c1 << " led by " << *players[(dealer_ind+1)%4] << endl;
        Card c2 = players[(dealer_ind+2)%4]->play_card(c1, trump);
        played_cards.push_back(c2);
        played_ind.push_back((dealer_ind+2)%4);
        cout << c2 << " played by " << *players[(dealer_ind+2)%4] << endl;
        Card c3 = players[(dealer_ind+3)%4]->play_card(c1, trump);
        played_cards.push_back(c3);
        played_ind.push_back((dealer_ind+3)%4);
        cout << c3 << " played by " << *players[(dealer_ind+3)%4] << endl;
        Card c4 = players[(dealer_ind+4)%4]->play_card(c1, trump);
        played_cards.push_back(c4);
        played_ind.push_back((dealer_ind+4)%4);
        cout << c4 << " played by " << *players[(dealer_ind)%4] << endl;

        Card high_card = played_cards[0];
        int winner_ind = played_ind[0];
        for(int i=1; i<4; ++i) {
            if(Card_less(high_card, played_cards[i], c1, trump)) {
                high_card = played_cards[i];
                winner_ind = played_ind[i];
            }
        }

        cout << *players[winner_ind] << " takes the trick" << endl;
        cout << endl;

        if(winner_ind == 0 || winner_ind == 2) {
            ++t1_tricks_won;
        }
        else {
            ++t2_tricks_won;
        }
        return winner_ind;
    }

    void trick_taking(int winner_ind, int &t1_tricks_won, int &t2_tricks_won) {
        vector<Card> played_cards;
        vector<int> played_ind;

        for(int j=0; j<4; ++j) {
            Card c1 = players[(winner_ind)%4]->lead_card(trump);
            played_cards.push_back(c1);
            played_ind.push_back((winner_ind)%4);
            cout << c1 << " led by " << *players[played_ind[0]] << endl;
            Card c2 = players[(winner_ind+1)%4]->play_card(c1, trump);
            played_cards.push_back(c2);
            played_ind.push_back((winner_ind+1)%4);
            cout << c2 << " played by " << *players[played_ind[1]] << endl;
            Card c3 = players[(winner_ind+2)%4]->play_card(c1, trump);
            played_cards.push_back(c3);
            played_ind.push_back((winner_ind+2)%4);
            cout << c3 << " played by " << *players[played_ind[2]] << endl;
            Card c4 = players[(winner_ind+3)%4]->play_card(c1, trump);
            played_cards.push_back(c4);
            played_ind.push_back((winner_ind+3)%4);
            cout << c4 << " played by " << *players[played_ind[3]] << endl;

            Card high_card = played_cards[0];
            for(int i=1; i<4; ++i) {
                if(Card_less(high_card, played_cards[i], c1, trump)) {
                    high_card = played_cards[i];
                    winner_ind = played_ind[i];
                }
            }

            cout << *players[winner_ind] << " takes the trick" << endl;
            cout << endl;
            played_cards.clear();
            played_ind.clear();

            if(winner_ind == 0 || winner_ind == 2) {
                ++t1_tricks_won;
            }
            else {
                ++t2_tricks_won;
            }
        }

        score_trick(t1_tricks_won, t2_tricks_won, order_up_ind, score);
    }

    void score_trick(int t1_tricks, int t2_tricks, int order_up_ind, int score[2]) {
        if(t1_tricks > t2_tricks) {
            if(order_up_ind == 0 || order_up_ind == 2) {
                if(t1_tricks == 3 || t1_tricks == 4) {
                    cout << *players[0] << " and " << *players[2] 
                    << " win the hand" << endl;
                    score[0] += 1;
                }
                else {
                    cout << *players[0] << " and " << *players[2] 
                    << " win the hand" << endl;
                    cout << "march!" << endl;
                    score[0] += 2;
                }
            }
            else {
                cout << *players[0] << " and " << *players[2] << " win the hand" << endl;
                cout << "euchred!" << endl;
                score[0] += 2;
            }
        }
        else {
            if(order_up_ind == 1 || order_up_ind == 3) {
                if(t2_tricks == 3 || t2_tricks == 4) {
                    cout << *players[1] << " and " << *players[3] 
                    << " win the hand" << endl;
                    score[1] += 1;
                }
                else {
                    cout << *players[1] << " and " << *players[3] 
                    << " win the hand" << endl;
                    cout << "march!" << endl;
                    score[1] += 2;
                }
            }
            else {
                cout << *players[1] << " and " << *players[3] << " win the hand" << endl;
                cout << "euchred!" << endl;
                score[1] += 2;
            }
        }
        cout << *players[0] << " and " << *players[2] 
        << " have " << score[0] << " points" << endl;
        cout << *players[1] << " and " << *players[3] 
        << " have " << score[1] << " points" << endl;
        cout << endl;
    }

    void play(bool shuffle, int MAX_SCORE) {
        int hand_num = 0;
        while(score[0] < MAX_SCORE && score[1] < MAX_SCORE) {
            if(shuffle) {this->shuffle();}
            cout << "Hand " << hand_num << endl;
            cout << *players[dealer_ind] << " deals" << endl;
            deal();
            cout << upcard << " turned up" << endl;
            making_phase();
            cout << endl;
            int t1_tricks_won = 0;
            int t2_tricks_won = 0;
            int winner_ind = first_trick_taking(t1_tricks_won, t2_tricks_won);
            trick_taking(winner_ind, t1_tricks_won, t2_tricks_won);
            ++hand_num;
            dealer_ind = (dealer_ind + 1)%4;
            deck.reset();
        }
        if(score[0] >= MAX_SCORE) {
            cout << *players[0] << " and " << *players[2] << " win!";
            cout << endl;
        }
        else {
            cout << *players[1] << " and " << *players[3] << " win!";
            cout << endl;
        }
    }
};

int main(int argc, char *argv[]) {
    for(int i=0; i<12; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl;

    string arg2 = string(argv[2]);
    string arg4 = string(argv[4]);
    string arg5 = string(argv[5]);
    string arg6 = string(argv[6]);
    string arg7 = string(argv[7]);
    string arg8 = string(argv[8]);
    string arg9 = string(argv[9]);
    string arg10 = string(argv[10]);
    string arg11 = string(argv[11]);
    if(argc!=12 && (*argv[3] > 0 && *argv[3] < 101) && 
        (arg2 == "shuffle" || arg2 == "noshuffle") &&
        (arg5 == "Simple" || arg5 == "Human") &&
        (arg7 == "Simple" || arg7 == "Human") &&
        (arg9 == "Simple" || arg9 == "Human") &&
        (arg11 == "Simple" || arg11 == "Human")) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] " 
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
    }

    string fileIn;
    bool deck_order;
    fileIn = argv[1];
    if(arg2 == "shuffle") {
        deck_order = true;
    }
    else {
        deck_order = false;
    }
    int max_points = stoi(argv[3]);

    vector<Player*> players;
    Player* p1 = Player_factory(arg4, arg5);
    players.push_back(p1);
    Player* p2 = Player_factory(arg6, arg7);
    players.push_back(p2);
    Player* p3 = Player_factory(arg8, arg9);
    players.push_back(p3);
    Player* p4 = Player_factory(arg10, arg11);
    players.push_back(p4);


    ifstream fin;
    fin.open(fileIn);
    if(!fin.is_open()) {
        cout << "Error opening " << fileIn << endl;
    }

    Game game = Game(players, fin);
    game.play(deck_order, max_points);
}