#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

class blackJack{
    public:
        blackJack(){};
        ~blackJack(){};
        void playBlackJack();
    private:
        int playerScore = 0;
        int dealerScore = 0;
        int numPlayersCards = 0;
        int numDealersCards = 0;
        int calculateScore(vector<string> cards, int currentScore, bool isPlayer);
        string playersName;
        vector<string> playersCards;
        vector<string> dealersCards;
        // We are going to order the deck of Cards like this: Spades, Clubs, Hearts, Diamonds; they are going to be randomized in the code
        vector<string> deckOfCards = {"2S", "3S", "4S", "5S", "6S", "2S", "7S", "8S", "9S", "10S", "JS", "QS", "KS", "AS",
                                      "2C", "3C", "4C", "5C", "6C", "2C", "7C", "8C", "9C", "10C", "JC", "QC", "KC", "AC",
                                      "2H", "3H", "4H", "5H", "6H", "2H", "7H", "8H", "9H", "10H", "JH", "QH", "KH", "AH",
                                      "2D", "3D", "4D", "5D", "6D", "2D", "7D", "8D", "9D", "10D", "JD", "QD", "KD", "AD"};
        // Function for the dealing of cards
        vector<string> dealCards();
        // When the dealer is done, and the dealer asks if the player wants anther card; if so, then the dealer gives them another
        vector<string> dealCard(vector<string> cards);
        
};