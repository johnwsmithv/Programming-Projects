/**
 * @file blackJack.cpp
 * @author John W. Smith V (jwsv61099@gmail.com)
 * @brief The point of this CPP file is to create as Black Jack Game
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <iterator>
#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include <limits>
#include "blackJack.hpp"

using namespace std;

void blackJack::playBlackJack(){  
    string tempPlayerHit;  
    bool playerWantHit = true;
    std::cout << "Welcome to Black Jack. What is your name?\n";
    std::cin >> playersName;
    std::cout<< "Hello " << playersName << "! The goal is to beat the dealer, me.\n" <<
    "If you score higher than I do, and have less than or equal to 21 then you win." << 
    "\nIf I have a higher card value then you, or I tie you then I win. Good luck!\n";

    // The start of the game where the dealer deals the cards to the player and him/herself
    dealCards();

    std::cout << "Here are your cards: ";
    for(string& x: playersCards) std::cout << ' ' << x;
    std::cout << "\n";
    // for(string& x: dealersCards) std::cout << ' ' << x;
    playerScore = calculateScore(playersCards, playerScore, true);
    dealerScore = calculateScore(dealersCards, dealerScore, false);

    std::cout << "Your current score is: " << playerScore << "\n";
    while(playerScore < 21 && playerWantHit){
        std::cout << "Do you want another card? Type Yes or No.\n";
        std::cin >> tempPlayerHit;
        while(tempPlayerHit != "Yes" && tempPlayerHit != "No"){
            std::cout << "This was your input: " << tempPlayerHit << "\n";
            std::cout << "That is not a valid input. Enter Yes or No.\n";
            std::cin >> tempPlayerHit;
        }
        tempPlayerHit == "Yes" ? playerWantHit = true : playerWantHit = false;
        if(playerWantHit){
            playersCards = dealCard(playersCards);
            playerScore = calculateScore(playersCards, playerScore, true);
            std::cout << "The cards you have are:\n";
            for(string& x: playersCards) std::cout << x << " ";
            std::cout << "\nYou currect score is: " << playerScore << "\n";
            if(playerScore > 21){
                std::cout << "You busted. The dealer wins. Good game!\n";
                exit(-1);
            }
        }
    }

    // Now the logic for the dealer to decide what it wants
    std::cout << "Here are the Dealers Cards: ";
    for(string& x: dealersCards) std::cout << ' ' << x;
    std::cout << "\n";
    std::cout << "The dealers score is: " << dealerScore << "\n";

    // If the dealer has 16 or less he needs to hit. Else he needs to stay.
    while(dealerScore < 17){
        dealersCards = dealCard(dealersCards);
        std::cout << "The dealer now has: ";
        for(string& x: dealersCards) std::cout << ' ' << x;
        std::cout << "\n";
        dealerScore = calculateScore(dealersCards, dealerScore, false);
        std::cout << "The dealers score is: " << dealerScore << "\n";
        if(dealerScore > 21){
            std::cout << "The dealer busted. You win! Good game!\n";
            exit(-1);
        }
    }

    if(playerScore > dealerScore){
        std::cout << "Your final score was " << playerScore <<". The dealer had " << dealerScore << ". You win! Good game!\n";
        exit(-1);
    } else if (playerScore == dealerScore) {
        std::cout << "You and the dealer tied. The dealer wins. Good game!\n";
        exit(-1);
    } else {
        std::cout << "Your final score was " << playerScore <<". The dealer had " << dealerScore << ". The dealer wins! Good game!\n";
        exit(-1);
    }
    
}

vector<string> blackJack::dealCards(){
    std::cout << "The dealer is shuffling the cards....\n";
    // Here is how we are shuffling the cards; this is from the cpp library and used as the example
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deckOfCards.begin(), deckOfCards.end(), std::default_random_engine(seed));

    // Now we need to give out the cards
    while(playersCards.size() != 2){
        playersCards.push_back(deckOfCards[0]);
        deckOfCards.erase(deckOfCards.begin());

        dealersCards.push_back(deckOfCards[0]);
        deckOfCards.erase(deckOfCards.begin());
    }
    return deckOfCards;
}

/**
 * @brief Deal a card to whoevers deck of cards was passed as the vector
 * 
 * @param cards The vector of cards of either the player or the dealer
 * @return vector<string> 
 */
vector<string> blackJack::dealCard(vector<string> cards){
    cards.push_back(deckOfCards[0]);
    deckOfCards.erase(deckOfCards.begin());
    return cards;
}

/**
 * @brief This function calculates the score of the player whose cards were passed
 * 
 * @param cards A Vector which contains the string representations of the cards the user has
 * @param currentScore The persons current score
 * @param isPlayer A bool saying if this is the player or not
 * @return int 
 */
int blackJack::calculateScore(vector<string> cards, int currentScore, bool isPlayer){
    int aceValue = 0;
    int i;
    isPlayer == true ? i = numPlayersCards : i = numDealersCards;
    for(i; i < cards.size(); i++){
        if(cards[i][0] == 'A'){
            if(isPlayer){
                std::cout << "You have an Ace. Do want it be a one or eleven? Type 1 or 11.\n";
                std::cin >> aceValue;
                while(std::cin.fail() || (aceValue != 1 && aceValue != 11)){
                        std::cin.clear();
                        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        std::cout << "You cannot enter a string. Enter 1 or 11.\n";
                        std::cin >> aceValue;
                }
            } 
            else {
                if(currentScore <= 10){
                    aceValue = 11;    
                } else {
                    aceValue = 1;
                }
            }
            currentScore += aceValue;
        }
        else if(cards[i][0] == 'J' || cards[i][0] == 'Q' || cards[i][0] == 'K'){
            currentScore += 10;
        }
        else{
            // This was the easiest way to say that the card that they got is a 10 since the character length is 3. 
            if(cards[i].length() == 3){
                currentScore += 10;
            }
            else{
                // Since the values are coming in as chars and we are converting it to an int, they are coming in as ASCII values;
                // so we need to get the value 2-9 and subtracting 0's ASCII Value which will give us the corresponding numeric value
                currentScore += ((int)cards[i][0] - (int)'0');
            }
        }
        isPlayer == true ? numPlayersCards++ : numDealersCards++;
    }
    return currentScore;
}

int main(){
    blackJack jack;
    jack.playBlackJack();
}