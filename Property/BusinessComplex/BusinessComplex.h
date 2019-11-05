//
// Created by Jason Torrence on 10/24/2019.
//

#ifndef REAL_ESTATE_TYCOON_BUSINESSCOMPLEX_H
#define REAL_ESTATE_TYCOON_BUSINESSCOMPLEX_H


#include "../../Tenant/Business/Business.h"

class BusinessComplex : public Property{
protected:
    double smallRent;
    double mediumRent;
    double largeRent;
public:
    BusinessComplex();
    void assignRandomBusinesses();
    void removeTenant(int location);

    std::string toString() override;

    void changeRent() override;
    double haveAllTenantsPayRent() override;
    double getRentAccordingToSize(int size);
};


#endif //REAL_ESTATE_TYCOON_BUSINESSCOMPLEX_H
