//
// Created by Jason Torrence on 10/23/2019.
//

#ifndef REAL_ESTATE_TYCOON_PLAYER_H
#define REAL_ESTATE_TYCOON_PLAYER_H


#include "../Property/Property.h"
#include "../Utilities/TotallyNotAVector.h"

class Player {

public:
    double bank;
    TotallyNotAVector<Property> * properties;

    Player();
    ~Player();

    void updateBank(double change);
    double getBank();
    void printPropertiesToSTDOut();
    void clearAllData();
};


#endif //REAL_ESTATE_TYCOON_PLAYER_H
