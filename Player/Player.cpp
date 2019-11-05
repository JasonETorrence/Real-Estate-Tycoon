//
// Created by Jason Torrence on 10/23/2019.
//


#include <iostream>
#include "Player.h"

/**
 * Player: the player constructor
 */
Player::Player(){
    bank = 500000;
    properties = new TotallyNotAVector<Property*>();
}

/**
 * ~Player: the player deconstructor.
 */
Player::~Player(){
    properties->clear();
    delete properties;
    delete &properties;
};

/**
 * updateBank: updates the players bank by adding the passed value to the bank value.
 *
 * @param change : the amount to add
 */
void Player::updateBank(double change){
    bank += change;
}

/**
 * getBank: returns the players bank
 * @return the player's bank value
 */
double Player::getBank(){
    return bank;
}

/**
 * getProperties: returns the pointer to the player's properties
 * @return the pointer to the player's properties
 */
TotallyNotAVector<Property*>* Player::getProperties(){
    return properties;
}

/**
 * printPropertiesToSTDOut: calls toString() on all the player's properties and prints
 * the result to std output
 */
void Player::printPropertiesToSTDOut(){
    std::cout << "You own the following properties:" << std::endl;
    for(int i = 0; i < properties->length(); i++){
        std::cout << "(" << i+1 << ") "<< properties->get(i)->toString();
        std::cout << " You still owe the bank $"<< properties->get(i)->getMortgageLeft() << " on this property.";
        std::cout << std::endl;
    }
}
