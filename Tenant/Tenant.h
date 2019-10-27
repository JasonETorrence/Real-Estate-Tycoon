//
// Created by Jason Torrence on 10/23/2019.
//

#ifndef REAL_ESTATE_TYCOON_TENANT_H
#define REAL_ESTATE_TYCOON_TENANT_H


#include "../Property/Property.h"

class Tenant {


public:
    double budget;
    int agreeability;
    Property * rentedLocation;

    Tenant();
    ~Tenant();
    Tenant(Tenant *pTenant);

    double payRent();
    double pay();
    void moveOut();
    void refuseToPay();
    void haveAllTenantsPayRent(Property *properties);
};


#endif //REAL_ESTATE_TYCOON_TENANT_H
