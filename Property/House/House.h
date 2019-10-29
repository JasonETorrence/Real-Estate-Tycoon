//
// Created by Jason Torrence on 10/24/2019.
//

#ifndef REAL_ESTATE_TYCOON_HOUSE_H
#define REAL_ESTATE_TYCOON_HOUSE_H


#include "../Property.h"
#include "../../Tenant/Civilian/Civilian.h"

class House : public Property{

public:
    Civilian tenant;

    House();
    ~House();

    void assignRandomCivilian();
    void removeTenant();
};


#endif //REAL_ESTATE_TYCOON_HOUSE_H
