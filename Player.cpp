// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>

class SimplePlayer : public Player {
    private:
    std::string const name;
    std::vector<Card> hand;

    public:  
    //Ctor
    SimplePlayer(std::string name) : Player(), name(name) {}

    const std::string & get_name() const {
        return this->name;
    }

    void add_card(const Card &c) {
        assert(this->hand.size() <= MAX_HAND_SIZE);
        this->hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                            int round, std::string &order_up_suit) const {
        int itr = 0;
        if(round == 1) {
            for(size_t i=0; i<hand.size(); ++i) {
                if(this->hand[i].is_face_or_ace() && 
                this->hand[i].is_trump(upcard.get_suit())) {
                    ++itr;
                }
            }
            if(itr > 1) {
                order_up_suit = upcard.get_suit();
                return true;
            }
        }
        else if(round == 2){
            for(size_t i=0; i<hand.size(); ++i) {
                if(this->hand[i].is_face_or_ace() &&
                this->hand[i].is_trump(Suit_next(upcard.get_suit()))) {
                    ++itr;
                }
            }
            if(itr > 0 || is_dealer) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            else {
                return false;
            }
        }
        return false;
    }

    void add_and_discard(const Card &upcard) {
        Card lowest_card = upcard;
        int lowest_index = 5;
        this->hand.push_back(upcard);
        for(int i=0; i<6; ++i) {
            if(Card_less(this->hand[i], lowest_card, upcard.get_suit())) {
                lowest_card = this->hand[i];
                lowest_index=i;
            }
        }
        this->hand.erase(this->hand.begin() + lowest_index);
    }

    Card lead_card(const std::string &trump) {
        bool has_non_trump = false;
        Card high_card;
        int high_card_ind = 0;
        Card high_trump_card;
        int high_trump_card_ind = 0;
        for(size_t i=0; i<this->hand.size(); ++i) {
            if(!(this->hand[i].is_trump(trump))) {
                has_non_trump = true;
                if(Card_less(high_card, this->hand[i], trump) ||
                    high_card == Card()) {
                    high_card = this->hand[i];
                    high_card_ind = i;
                }
            }
            else {
                if(Card_less(high_trump_card, this->hand[i], trump) ||
                    high_trump_card == Card()) {
                    high_trump_card = this->hand[i];
                    high_trump_card_ind = i;
                }
            }
        }
        if(has_non_trump) {
            Card copy = high_card;
            this->hand.erase(this->hand.begin() + high_card_ind);
            return copy;
        }
        else {
            Card copy = high_trump_card;
            this->hand.erase(this->hand.begin() + high_trump_card_ind);
            return copy;
        }
    }

    Card play_card(const Card &led_card, const std::string &trump) {
        bool can_follow = false;
        Card high_card;
        int high_card_ind = 0;
        Card low_card;
        int low_card_ind = 0;
        for(size_t i=0; i<this->hand.size(); ++i) {
            if((led_card.is_trump(trump) && !this->hand[i].is_trump(trump)) ||
            (this->hand[i].is_trump(trump) && !led_card.is_trump(trump))) {
                if(Card_less(this->hand[i], low_card, led_card, trump) ||
                    low_card == Card()) {
                    low_card = this->hand[i];
                    low_card_ind = i;
                }
            }
            else if((led_card.is_trump(trump) && this->hand[i].is_trump(trump)) || 
            ((this->hand[i].get_suit() == led_card.get_suit()))) {
                can_follow = true;
                if(Card_less(high_card, this->hand[i], led_card, trump) ||
                    high_card == Card()) {
                    high_card = this->hand[i];
                    high_card_ind = i;
                }
            }
            else {
                if(Card_less(this->hand[i], low_card, led_card, trump) ||
                    low_card == Card()) {
                    low_card = this->hand[i];
                    low_card_ind = i;
                }
            }
        }
        if(can_follow) {
            Card copy = high_card;
            this->hand.erase(this->hand.begin() + high_card_ind);
            return copy;
        }
        else {
            Card copy = low_card;
            this->hand.erase(this->hand.begin() + low_card_ind);
            return copy;
        }
    }

    virtual ~SimplePlayer() {}
};

class HumanPlayer : public Player {
    private:

    std::string name;
    std::vector<Card> hand;

    void print_hand() const {
        std::vector<Card> copy = hand;
        std::sort(copy.begin(), copy.end());
        for (size_t i=0; i < copy.size(); ++i) {
            std::cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << copy[i] << "\n";
        }
    }

    public:
    //ctor
    HumanPlayer(std::string name) : Player(), name(name) {}

    const std::string & get_name() const {
        return this->name;
    }

    void add_card(const Card &c) {
        assert(this->hand.size() <= MAX_HAND_SIZE);
        this->hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                            int round, std::string &order_up_suit) const {
        print_hand();
        std::cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
        std::string choice;
        std::cin >> choice;
        if(choice == "pass") {
            return false;
        }
        else if(choice == "Spades" || choice == "Clubs" ||
                choice == "Hearts" || choice == "Diamonds") {
            order_up_suit = choice;
            return true;
        }
        assert(false);
    }

    void add_and_discard(const Card &upcard) {
        int choice;
        std::vector<Card> sort_hand = hand;
        std::sort(sort_hand.begin(), sort_hand.end());

        print_hand();
        std::cout << "Discard upcard: [-1]\n";
        std::cout << "Human player " << name << ", please select a card to discard:\n";
        std::cin >> choice;

        if (choice >= 0 && choice < sort_hand.size()) {
            Card copy = sort_hand[choice];
            for (int i = 0; i < sort_hand.size(); i++) {
                if (copy == hand[i]) {
                    hand.erase(hand.begin() + i);
                    hand.push_back(upcard);
                    return;
                }
            }
        }
    }

    Card lead_card(const std::string &trump) {
        int choice;
        std::vector<Card> sort_hand = hand;
        std::sort(sort_hand.begin(), sort_hand.end());
        print_hand();
        std::cout << "Human player " << name << ", please select a card:\n";
        std::cin >> choice;
        if(choice >= 0 && choice < sort_hand.size()) {
            Card copy = sort_hand[choice];
            for (int i = 0; i < sort_hand.size(); i++) {
                if (copy == hand[i]) {
                    hand.erase(hand.begin() + i);
                }
            }
            return copy;
        }
        assert(false);
    }

    Card play_card(const Card &led_card, const std::string &trump) {
        return lead_card(trump);
        assert(false);
    }

    virtual ~HumanPlayer() {}
};

Player * Player_factory(const std::string &name, const std::string &strategy) {
    if(strategy == "Simple") {
        return new SimplePlayer(name);
    }
    if(strategy == "Human") {
        return new HumanPlayer(name);
    }
    assert(false);
    return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}