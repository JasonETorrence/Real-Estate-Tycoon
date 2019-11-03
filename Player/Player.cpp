//
// Created by Jason Torrence on 10/23/2019.
//


#include <iostream>
#include "Player.h"

Player::Player(){
    bank = 500000;
    properties = new TotallyNotAVector<Property>();
}

Player::~Player() = default;

void Player::updateBank(double change){
    bank += change;
}

double Player::getBank(){
    return bank;
}

void Player::printPropertiesToSTDOut(){
    std::cout << "You own the following properties:" << std::endl;
    for(int i = 0; i < properties->length(); i++){
        std::cout << "(" << i+1 << ") "<< properties->get(i).toString() << std::endl;
    }
}

void Player::clearAllData(){
    delete properties;
    delete &properties;
}
