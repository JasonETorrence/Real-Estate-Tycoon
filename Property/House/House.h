//
// Created by Jason Torrence on 10/24/2019.
//

#ifndef REAL_ESTATE_TYCOON_HOUSE_H
#define REAL_ESTATE_TYCOON_HOUSE_H


#include "../Property.h"
#include "../../Tenant/Civilian/Civilian.h"

class House : public Property{

public:

    House();
    ~House();

    void assignRandomCivilian();
    void removeTenant(int location);

    std::string toString() override;
    void changeRent() override;
    double haveAllTenantsPayRent() override;
};


#endif //REAL_ESTATE_TYCOON_HOUSE_H
