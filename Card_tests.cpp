// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here

TEST(test_getrank_getsuit_basic) {
    Card card("Ace", "Spades");

    ASSERT_EQUAL(card.get_rank(), "Ace");
    ASSERT_EQUAL(card.get_suit(), "Spades");
}

TEST(test_getrank_trump) {
    Card rbower("Jack", "Spades");
    Card lbower("Jack", "Clubs");
    Card control("Ace", "Diamonds");

    ASSERT_EQUAL(rbower.get_suit("Spades"), "Spades");
    ASSERT_EQUAL(lbower.get_suit("Spades"), "Spades");
    ASSERT_EQUAL(control.get_suit("Spades"), "Diamonds");
}

TEST(test_is_face_or_ace) {
    Card ace("Ace", "Spades");
    Card king("King", "Clubs");
    Card queen("Queen", "Hearts");
    Card jack("Jack", "Diamonds");
    Card control("Seven", "Diamonds");

    ASSERT_TRUE(ace.is_face_or_ace());
    ASSERT_TRUE(king.is_face_or_ace());
    ASSERT_TRUE(queen.is_face_or_ace());
    ASSERT_TRUE(jack.is_face_or_ace());
    ASSERT_FALSE(control.is_face_or_ace());
}

TEST(test_is_right_bower) {
    Card rbower("Jack", "Hearts");
    Card lbower("Jack", "Diamonds");
    Card control("Ten", "Hearts");

    ASSERT_TRUE(rbower.is_right_bower("Hearts"));
    ASSERT_FALSE(lbower.is_right_bower("Hearts"));
    ASSERT_FALSE(control.is_right_bower("Hearts"));
}

TEST(test_is_left_bower) {
    Card rbower("Jack", "Hearts");
    Card lbower("Jack", "Diamonds");
    Card control("Ten", "Hearts");

    ASSERT_FALSE(rbower.is_left_bower("Hearts"));
    ASSERT_TRUE(lbower.is_left_bower("Hearts"));
    ASSERT_FALSE(control.is_left_bower("Hearts"));
}

TEST(test_istrump) {
    Card rbower("Jack", "Hearts");
    Card lbower("Jack", "Diamonds");
    Card ten("Ten", "Hearts");
    Card control("Ten", "Spades");

    ASSERT_TRUE(rbower.is_trump("Hearts"));
    ASSERT_TRUE(lbower.is_trump("Hearts"));
    ASSERT_TRUE(ten.is_trump("Hearts"));
    ASSERT_FALSE(control.is_trump("Hearts"));
}

TEST(test_operator_less_than_ranks) {
    Card nine_spades("Nine", "Spades");
    Card jack_hearts("Jack", "Hearts");
    Card ace_clubs("Ace", "Clubs");

    ASSERT_TRUE(operator<(nine_spades, ace_clubs));
    ASSERT_FALSE(operator<(ace_clubs, jack_hearts));
    ASSERT_FALSE(operator<(nine_spades, nine_spades));
}

TEST(test_operator_less_than_suits) {
    Card queen_spades("Queen", "Spades");
    Card queen_hearts("Queen", "Hearts");
    Card queen_clubs("Queen", "Clubs");
    Card queen_diamonds("Queen", "Diamonds");

    ASSERT_TRUE(operator<(queen_spades, queen_hearts));
    ASSERT_TRUE(operator<(queen_hearts, queen_clubs));
    ASSERT_TRUE(operator<(queen_clubs, queen_diamonds));
    ASSERT_FALSE(operator<(queen_diamonds, queen_hearts));
    ASSERT_FALSE(operator<(queen_spades, queen_spades));
}

TEST(test_operator_less_than_equal_ranks) {
    Card nine_spades("Nine", "Spades");
    Card jack_hearts("Jack", "Hearts");
    Card ace_clubs("Ace", "Clubs");

    ASSERT_TRUE(operator<=(nine_spades, ace_clubs));
    ASSERT_FALSE(operator<=(ace_clubs, jack_hearts));
    ASSERT_TRUE(operator<=(nine_spades, nine_spades));
}

TEST(test_operator_less_than_equal_suits) {
    Card queen_spades("Queen", "Spades");
    Card queen_hearts("Queen", "Hearts");
    Card queen_clubs("Queen", "Clubs");
    Card queen_diamonds("Queen", "Diamonds");

    ASSERT_TRUE(operator<=(queen_spades, queen_hearts));
    ASSERT_TRUE(operator<=(queen_hearts, queen_clubs));
    ASSERT_TRUE(operator<=(queen_clubs, queen_diamonds));
    ASSERT_FALSE(operator<=(queen_diamonds, queen_hearts));
    ASSERT_TRUE(operator<=(queen_spades, queen_spades));
}

TEST(test_operator_greater_than_ranks) {
    Card nine_spades("Nine", "Spades");
    Card jack_hearts("Jack", "Hearts");
    Card ace_clubs("Ace", "Clubs");

    ASSERT_FALSE(operator>(nine_spades, ace_clubs));
    ASSERT_TRUE(operator>(ace_clubs, jack_hearts));
    ASSERT_FALSE(operator>(nine_spades, nine_spades));
}

TEST(test_operator_greater_than_suits) {
    Card queen_spades("Queen", "Spades");
    Card queen_hearts("Queen", "Hearts");
    Card queen_clubs("Queen", "Clubs");
    Card queen_diamonds("Queen", "Diamonds");

    ASSERT_FALSE(operator>(queen_spades, queen_hearts));
    ASSERT_FALSE(operator>(queen_hearts, queen_clubs));
    ASSERT_FALSE(operator>(queen_clubs, queen_diamonds));
    ASSERT_TRUE(operator>(queen_diamonds, queen_hearts));
    ASSERT_FALSE(operator>(queen_spades, queen_spades));
}

TEST(test_operator_greater_than_equal_ranks) {
    Card nine_spades("Nine", "Spades");
    Card jack_hearts("Jack", "Hearts");
    Card ace_clubs("Ace", "Clubs");

    ASSERT_FALSE(operator>=(nine_spades, ace_clubs));
    ASSERT_TRUE(operator>=(ace_clubs, jack_hearts));
    ASSERT_TRUE(operator>=(nine_spades, nine_spades));
}

TEST(test_operator_greater_than_equal_suits) {
    Card queen_spades("Queen", "Spades");
    Card queen_hearts("Queen", "Hearts");
    Card queen_clubs("Queen", "Clubs");
    Card queen_diamonds("Queen", "Diamonds");

    ASSERT_FALSE(operator>=(queen_spades, queen_hearts));
    ASSERT_FALSE(operator>=(queen_hearts, queen_clubs));
    ASSERT_FALSE(operator>=(queen_clubs, queen_diamonds));
    ASSERT_TRUE(operator>=(queen_diamonds, queen_hearts));
    ASSERT_TRUE(operator>=(queen_spades, queen_spades));
}

TEST(test_operator_equal) {
    Card ace_spades("Ace", "Spades");
    Card jack_spades("Jack", "Spades");
    Card ace_hearts("Ace", "Hearts");

    ASSERT_TRUE(operator==(ace_spades, ace_spades));
    ASSERT_FALSE(operator==(ace_spades, jack_spades));
    ASSERT_FALSE(operator==(ace_spades, ace_hearts));
}

TEST(test_operator_not_equal) {
    Card ace_spades("Ace", "Spades");
    Card jack_spades("Jack", "Spades");
    Card ace_hearts("Ace", "Hearts");

    ASSERT_FALSE(operator!=(ace_spades, ace_spades));
    ASSERT_TRUE(operator!=(ace_spades, jack_spades));
    ASSERT_TRUE(operator!=(ace_spades, ace_hearts));
}

TEST(test_suit_next) {
    ASSERT_EQUAL(Suit_next("Spades"), "Clubs");
    ASSERT_EQUAL(Suit_next("Clubs"), "Spades");
    ASSERT_EQUAL(Suit_next("Hearts"), "Diamonds");
    ASSERT_EQUAL(Suit_next("Diamonds"), "Hearts");
}

TEST(test_print_to_stream) {
    Card card("Ace", "Spades");
    ostringstream os;
    string correct = "Ace of Spades";
    operator<<(os, card);
    string output = os.str();

    ASSERT_EQUAL(output, correct);
}

TEST(test_card_less_trump) {
    Card rbower("Jack", "Spades");
    Card lbower("Jack", "Clubs");
    Card jack_hearts("Jack", "Hearts");
    Card ace_spades("Ace", "Spades");
    Card ace_diamonds("Ace", "Diamonds");

    ASSERT_TRUE(Card_less(lbower, rbower, "Spades"));
    ASSERT_TRUE(Card_less(ace_spades, lbower, "Spades"));
    ASSERT_TRUE(Card_less(ace_diamonds, ace_spades, "Spades"));
    ASSERT_TRUE(Card_less(jack_hearts, lbower, "Spades"));
    ASSERT_TRUE(Card_less(jack_hearts, ace_diamonds, "Spades"));
}

TEST(test_card_less_led) {
    Card rbower("Jack", "Spades");
    Card lbower("Jack", "Clubs");
    Card jack_hearts("Jack", "Hearts");
    Card ace_spades("Ace", "Spades");
    Card ace_hearts("Ace", "Hearts");
    Card ace_diamonds("Ace", "Diamonds");

    ASSERT_TRUE(Card_less(lbower, rbower, ace_hearts, "Spades"));
    ASSERT_TRUE(Card_less(ace_spades, lbower, ace_hearts, "Spades"));
    ASSERT_TRUE(Card_less(ace_diamonds, ace_spades, ace_hearts, "Spades"));
    ASSERT_TRUE(Card_less(jack_hearts, lbower, ace_hearts, "Spades"));
    ASSERT_FALSE(Card_less(jack_hearts, ace_diamonds, ace_hearts, "Spades"));
    ASSERT_TRUE(Card_less(jack_hearts, ace_hearts, ace_hearts, "Spades"));
}

TEST_MAIN()
