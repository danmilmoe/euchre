// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_player_get_name_diff_case) {
    Player * alice = Player_factory("alice", "Simple");
    ASSERT_NOT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_simple_player_make_trump1) {
  //Three high trump cards, round 1, is dealer
    Player * bob = Player_factory("Bob", "Simple");

    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

    Card nine_hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    string trump;
    bool orderup = bob->make_trump(
        nine_hearts,    // Upcard
        true,           // Bob is also the dealer
        1,              // First round
        trump           // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_HEARTS);

    delete bob;
}

TEST(test_simple_player_make_trump2) {
  //Two high trump cards, round 1, is dealer
    Player * bob = Player_factory("Bob", "Simple");

    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));

    Card king_clubs(Card::RANK_KING, Card::SUIT_CLUBS);
    string trump;
    bool orderup = bob->make_trump(
        king_clubs,    // Upcard
        true,           // Bob is also the dealer
        1,              // First round
        trump           // Suit ordered up (if any)
    );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

  delete bob;
}

TEST(test_simple_player_make_trump3) {
  //No high trump cards, round 1, is dealer
    Player * bob = Player_factory("Bob", "Simple");

    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));

    Card king_spades(Card::RANK_KING, Card::SUIT_SPADES);
    string trump;
    bool orderup = bob->make_trump(
        king_spades,    // Upcard
        true,           // Bob is also the dealer
        1,              // First round
        trump           // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_FALSE(orderup);

    delete bob;
}

TEST(test_simple_player_make_trump4) {
  //Two high trump cards with bower test, round 1, is dealer
    Player * bob = Player_factory("Bob", "Simple");

    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));

    Card king_spades(Card::RANK_KING, Card::SUIT_SPADES);
    string trump;
    bool orderup = bob->make_trump(
        king_spades,    // Upcard
        true,           // Bob is also the dealer
        1,              // First round
        trump           // Suit ordered up (if any)
    );

  // Verify Bob's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);
    delete bob;
}

TEST(test_simple_player_make_trump5) {
  //One high trump, round 1, is not dealer
    Player * bob = Player_factory("Bob", "Simple");

    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));

    Card queen_spades(Card::RANK_QUEEN, Card::SUIT_SPADES);
    string trump;
    bool orderup = bob->make_trump(
        queen_spades,    // Upcard
        false,           // Bob is also the dealer
        1,              // Second round
        trump           // Suit ordered up (if any)
    );

  // Verify Bob's order up and trump suit
    ASSERT_FALSE(orderup);
    delete bob;
}

TEST(test_simple_player_make_trump6) {
  //One high trump, round 2, is not dealer
    Player * bob = Player_factory("Bob", "Simple");

    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));

    Card queen_spades(Card::RANK_QUEEN, Card::SUIT_SPADES);
    string trump;
    bool orderup = bob->make_trump(
        queen_spades,    // Upcard
        false,           // Bob is also the dealer
        2,              // Second round
        trump           // Suit ordered up (if any)
    );

  // Verify Bob's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);
    delete bob;
}

TEST(test_simple_player_add_and_discard1) {
    Player * alice = Player_factory("Alice", "Simple");
    Card ace_spades = Card("Ace", "Spades");
    Card king_clubs = Card("King", "Clubs");
    Card queen_hearts = Card("Queen", "Hearts");
    Card jack_diamonds = Card("Jack", "Diamonds");
    Card ten_spades = Card("Ten", "Spades");
    Card nine_spades = Card("Nine", "Spades");
    Card led_card = Card("Ace", "Clubs");

    alice->add_card(ace_spades);
    alice->add_card(king_clubs);
    alice->add_card(queen_hearts);
    alice->add_card(jack_diamonds);
    alice->add_card(ten_spades);

    alice->add_and_discard(nine_spades);
    ASSERT_EQUAL(alice->play_card(led_card, "Spades"), king_clubs);
    ASSERT_EQUAL(alice->play_card(led_card, "Spades"), queen_hearts);
    ASSERT_EQUAL(alice->play_card(led_card, "Spades"), nine_spades);
    ASSERT_EQUAL(alice->play_card(led_card, "Spades"), ten_spades);
    ASSERT_EQUAL(alice->play_card(led_card, "Spades"), ace_spades);

    delete alice;
}

TEST(test_simple_player_add_and_discard2) {
    Player * alice = Player_factory("Alice", "Simple");
    Card ace_spades = Card("Ace", "Spades");
    Card king_clubs = Card("King", "Clubs");
    Card queen_hearts = Card("Queen", "Hearts");
    Card jack_diamonds = Card("Jack", "Diamonds");
    Card ten_spades = Card("Ten", "Spades");
    Card jack_hearts = Card("Jack", "Hearts");
    Card led_card = Card("Ace", "Clubs");

    alice->add_card(ace_spades);
    alice->add_card(king_clubs);
    alice->add_card(queen_hearts);
    alice->add_card(jack_diamonds);
    alice->add_card(ten_spades);

    alice->add_and_discard(jack_hearts);
    ASSERT_EQUAL(alice->play_card(led_card, "Hearts"), king_clubs);
    ASSERT_EQUAL(alice->play_card(led_card, "Hearts"), ace_spades);
    ASSERT_EQUAL(alice->play_card(led_card, "Hearts"), queen_hearts);
    ASSERT_EQUAL(alice->play_card(led_card, "Hearts"), jack_diamonds);
    ASSERT_EQUAL(alice->play_card(led_card, "Hearts"), jack_hearts);
    delete alice;
}

TEST(test_simple_player_lead_card1) {
  //Has nontrump cards
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
    );

    // Bob leads
    Card card_led = bob->lead_card(Card::SUIT_HEARTS);

    // Verify the card Bob selected to lead
    Card king_spades(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, king_spades); //check led card

    delete bob;
}

TEST(test_simple_player_lead_card2) {
  //No nontrump cards, play left bower
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
    );

    // Bob leads
    Card card_led = bob->lead_card(Card::SUIT_HEARTS);

    // Verify the card Bob selected to lead
    Card jack_diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led, jack_diamonds); //check led card

    delete bob;
}

TEST(test_simple_player_lead_card3) {
  //No nontrump cards, play right bower
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_HEARTS) // upcard
    );

    // Bob leads
    Card card_led = bob->lead_card(Card::SUIT_HEARTS);

    // Verify the card Bob selected to lead
    Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(card_led, jack_hearts); //check led card

    delete bob;
}

TEST(test_simple_player_lead_card4) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(
    Card(Card::RANK_NINE, Card::SUIT_CLUBS) // upcard
    );

    // Bob leads
    Card card_led = bob->lead_card(Card::SUIT_CLUBS);

    // Verify the card Bob selected to lead
    Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led, ten_diamonds); //check led card

    delete bob;
}

TEST(test_simple_player_lead_card5) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(
    Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS) // upcard
    );

    // Bob leads
    Card card_led = bob->lead_card(Card::SUIT_HEARTS);

    // Verify the card Bob selected to lead
    Card queen_diamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(card_led, queen_diamonds); //check led card

    delete bob;
}

TEST(test_simple_player_lead_card6) {
  //One trump card(left bower
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));

    // Bob leads
    Card card_led = bob->lead_card(Card::SUIT_HEARTS);

    // Verify the card Bob selected to lead
    Card ten_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(card_led, ten_clubs); //check led card

    delete bob;
}

TEST(test_simple_player_play_card1) {
  //Can not follow, has no bowers
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_simple_player_play_card2) {
  //Can follow with one card
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    ten_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  delete bob;
}

TEST(test_simple_player_play_card3) {
  //Can not follow, has left bower
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));

  // Bob plays a card
  Card ten_spades(Card::RANK_TEN, Card::SUIT_SPADES);
  Card card_played = bob->play_card(
    ten_spades,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  delete bob;
}

TEST(test_simple_player_play_card4) {
  //Can not follow, has left bower
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
  Card card_played = bob->play_card(
    jack_hearts,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  delete bob;
}

TEST(test_simple_player_play_card5) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  // Bob plays a card
  Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
  Card card_played = bob->play_card(
    jack_clubs,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_simple_player_play_card6) {
  //Can follow with only left bower
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob plays a card
  Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
  Card card_played = bob->play_card(
    jack_clubs,  // Nine of Diamonds is led
    "Clubs"        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_SPADES));
  delete bob;
}

TEST(test_player_factory) {
  Player* bob = Player_factory("Bob", "Simple");
  ASSERT_TRUE(bob);
  delete bob;
}

TEST(test_player_print) {
  Player* bob = Player_factory("Bob", "Simple");
  ostringstream os;
  os << *bob;
  std::string correct = "Bob";
  std::string output = os.str();

  ASSERT_EQUAL(output, correct);

  delete bob;
}

TEST_MAIN()
