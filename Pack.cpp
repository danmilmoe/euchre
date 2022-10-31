// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Pack.h"
#include <cassert>

Pack::Pack() {
    Card c1 = Card("Nine", "Spades");
    Card c2 = Card("Ten", "Spades");
    Card c3 = Card("Jack", "Spades");
    Card c4 = Card("Queen", "Spades");
    Card c5 = Card("King", "Spades");
    Card c6 = Card("Ace", "Spades");
    Card c7 = Card("Nine", "Hearts");
    Card c8 = Card("Ten", "Hearts");
    Card c9 = Card("Jack", "Hearts");
    Card c10 = Card("Queen", "Hearts");
    Card c11 = Card("King", "Hearts");
    Card c12 = Card("Ace", "Hearts");
    Card c13 = Card("Nine", "Clubs");
    Card c14 = Card("Ten", "Clubs");
    Card c15 = Card("Jack", "Clubs");
    Card c16 = Card("Queen", "Clubs");
    Card c17 = Card("King", "Clubs");
    Card c18 = Card("Ace", "Clubs");
    Card c19 = Card("Nine", "Diamonds");
    Card c20 = Card("Ten", "Diamonds");
    Card c21 = Card("Jack", "Diamonds");
    Card c22 = Card("Queen", "Diamonds");
    Card c23 = Card("King", "Diamonds");
    Card c24 = Card("Ace", "Diamonds");
    cards = {c1, c2, c3, c4, c5, c6, c7, c8, c9,
                c10, c11, c12, c13, c14, c15, c16,
                c17, c18, c19, c20, c21, c22, c23, c24};
    next = 0;
}

Pack::Pack(std::istream& pack_input) {
    std::string rank;
    std::string suit;
    std::string dummy;
    int index = 0;
    while(pack_input >> rank >> dummy >> suit) {
        Card c = Card(rank, suit);
        cards[index] = c;
        ++index;
    }
    next = 0;
}

Card Pack::deal_one() {
    ++next;
    return cards[next - 1];
}

void Pack::reset() {
    next = 0;
}

void Pack::shuffle() {
    Card shuffled[PACK_SIZE];
    for(int i=0; i<7; ++i) {
        for(int i=0; i<PACK_SIZE; ++i) {
            if(i < 12) {
                shuffled[2*i+1] = cards[i];
            }
            else {
                shuffled[2*i - 24] = cards[i];
            }
        }
        for(int i=0; i<PACK_SIZE; ++i) {
        cards[i] = shuffled[i];
        }
    }
    next = 0;
}

bool Pack::empty() const {
    return (next==24);
}