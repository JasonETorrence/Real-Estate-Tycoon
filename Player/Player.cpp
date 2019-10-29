//
// Created by Jason Torrence on 10/23/2019.
//


#include <iostream>
#include "Player.h"

Player::Player(){
    bank = 500000;
    numOfProperties = 0;
}

Player::~Player(){};

void Player::updateBank(double change){
    bank += change;
}

bool Player::buyProperty(Property * aProperty){
    if(bank >= aProperty->getValue()){
        Property::append(properties, aProperty, numOfProperties);
    }else{
        std::cout << "You lack the money to buy that property." << std::endl;
    }
}

double Player::getBank(){
    return bank;
}

void Player::printPropertiesToSTDOut(){
    std::cout << "You own the following properties:" << std::endl;
    for(int i = 0; i < numOfProperties; i++){
        std::cout << "(" << i+1 << ") "<< properties[i].toString() << std::endl;
    }
}
