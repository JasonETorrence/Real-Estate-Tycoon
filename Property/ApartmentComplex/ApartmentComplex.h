//
// Created by Jason Torrence on 10/24/2019.
//

#ifndef REAL_ESTATE_TYCOON_APARTMENTCOMPLEX_H
#define REAL_ESTATE_TYCOON_APARTMENTCOMPLEX_H


#include "../Property.h"
#include "../../Tenant/Civilian/Civilian.h"

class ApartmentComplex : public Property{
public:
    ApartmentComplex();
    void assignRandomCivilians();
    void removeTenant(int location);

    std::string toString() override;
    void changeRent() override;
    double haveAllTenantsPayRent() override;
};


#endif //REAL_ESTATE_TYCOON_APARTMENTCOMPLEX_H
