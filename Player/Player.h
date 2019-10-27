//
// Created by Jason Torrence on 10/23/2019.
//

#ifndef REAL_ESTATE_TYCOON_PLAYER_H
#define REAL_ESTATE_TYCOON_PLAYER_H


#include "../Property/Property.h"

class Player {

public:
    double bank;
    Property * properties;
    int numOfProperties;

    Player();
    ~Player();

    void updateBank(double change);
    bool buyProperty(Property *aProperty);
    double getBank();
    void printPropertiesToSTDOut();

};


#endif //REAL_ESTATE_TYCOON_PLAYER_H
