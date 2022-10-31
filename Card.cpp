// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
Card::Card() : rank("Two"), suit("Spades") {}

Card::Card(const std::string &rank_in, const std::string &suit_in) 
    : rank(rank_in), suit(suit_in) {}

std::string Card::get_rank() const {
    return this->rank;
}

std::string Card::get_suit() const {
    return this->suit;
}

std::string Card::get_suit(const std::string &trump) const {
    if(this->is_left_bower(trump)) {
        return trump;
    }
    else {
        return this->get_suit();
    }
}

bool Card::is_face_or_ace() const {
    std::string rank = this->get_rank();
    for(int i = 9; i < NUM_RANKS; ++i) {
        if(this->get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            return true;
        }
    }
    return false;
}

bool Card::is_right_bower(const std::string &trump) const {
    if(this->get_rank() == "Jack" && this->get_suit() == trump) {
        return true;
    }
    else {
        return false;
    }
}

bool Card::is_left_bower(const std::string &trump) const {
    if(this->get_rank() == "Jack" && this->get_suit() == Suit_next(trump)) {
        return true;
    }
    else {
        return false;
    }
}

bool Card::is_trump(const std::string &trump) const {
    if(this->get_suit() == trump || this->is_left_bower(trump)) {
        return true;
    }
    else {
        return false;
    }
}

bool operator<(const Card &lhs, const Card &rhs) {
    std::string lhs_rank = lhs.get_rank();
    std::string lhs_suit = lhs.get_suit();
    std::string rhs_rank = rhs.get_rank();
    std::string rhs_suit = rhs.get_suit();
    int lhs_rank_ind = 0;
    int lhs_suit_ind = 0;
    int rhs_rank_ind = 0;
    int rhs_suit_ind = 0;
    for(int i=0; i<NUM_RANKS; ++i) {
        if(lhs_rank == RANK_NAMES_BY_WEIGHT[i]) {
            lhs_rank_ind = i;
        }
        if(rhs_rank == RANK_NAMES_BY_WEIGHT[i]) {
            rhs_rank_ind = i;
        }
    }
    if(lhs_rank_ind < rhs_rank_ind) {
        return true;
    }
    else if(lhs_rank_ind > rhs_rank_ind) {
        return false;
    }
    else {
        for(int j=0; j<NUM_SUITS; ++j) {
            if(lhs_suit == SUIT_NAMES_BY_WEIGHT[j]) {
                lhs_suit_ind = j;
            }
            if(rhs_suit == SUIT_NAMES_BY_WEIGHT[j]) {
                rhs_suit_ind = j;
            }
        }
        if(lhs_suit_ind < rhs_suit_ind) {
            return true;
        }
        else {
            return false;
        }
    }
    assert(false);
}

bool operator<=(const Card &lhs, const Card &rhs) {
    if(lhs < rhs || lhs == rhs) {
        return true;
    }
    else {
        return false;
    }
    assert(false);
}

bool operator>(const Card &lhs, const Card &rhs) {
    if(!(lhs <= rhs)) {
        return true;
    }
    else {
        return false;
    }
    assert(false);
}

bool operator>=(const Card &lhs, const Card &rhs) {
    if(lhs > rhs || lhs == rhs) {
        return true;
    }
    else {
        return false;
    }
}

bool operator==(const Card &lhs, const Card &rhs) {
    if(lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()) {
        return true;
    }
    else {
        return false;
    }
    assert(false);
}

bool operator!=(const Card &lhs, const Card &rhs) {
    if(!(lhs == rhs)) {
        return true;
    }
    else {
        return false;
    }
    assert(false);
}

std::string Suit_next(const std::string &suit) {
    if(suit == "Spades") {
        return "Clubs";
    }
    else if(suit == "Clubs") {
        return "Spades";
    }
    else if(suit == "Hearts") {
        return "Diamonds";
    }
    else if(suit == "Diamonds") {
        return "Hearts";
    }
    else {
        assert(false);
    }
}

std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

void Card_less_helper(const Card &a, const Card &b, 
    const std::string &trump, int &check) {
    if(a.is_right_bower(trump)) {
        check = 0;
    }
    else if(b.is_right_bower(trump)) {
        check = 1;
    }
    else if(a.is_left_bower(trump)) {
        check = 0;
    }
    else if(b.is_left_bower(trump)) {
        check = 1;
    }
    else if(a.is_trump(trump) && !b.is_trump(trump)) {
        check = 0;
    }
    else if(b.is_trump(trump) && !a.is_trump(trump)) {
        check = 1;
    }
}

bool Card_less(const Card &a, const Card &b, const std::string &trump) {
    int check = 2;
    Card_less_helper(a, b, trump, check);
    if (check == 2) {
        return a < b;
    } else if (check == 1) {
        return true;
    } else if (check == 0) {
        return false;
    }
    assert(false);
}

bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    int check = 2;
    Card_less_helper(a, b, trump, check);
    if (check == 2) {
        if(led_card.is_left_bower(trump)) {
            return a < b;
        }
        else if(a.get_suit() == led_card.get_suit() && 
        b.get_suit() != led_card.get_suit()) {
            return false;
        }
        else if(a.get_suit() != led_card.get_suit() && 
        b.get_suit() == led_card.get_suit()) {
            return false;
        }
        else {
            return a < b;
        }
    } else if (check == 1){
        return true;
    } else if (check == 0) {
        return false;
    }
    assert(false);
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
