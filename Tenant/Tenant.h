//
// Created by Jason Torrence on 10/23/2019.
//

#ifndef REAL_ESTATE_TYCOON_TENANT_H
#define REAL_ESTATE_TYCOON_TENANT_H

class Tenant {

public:
    double budget;
    int agreeability;

    Tenant();
    ~Tenant();

    Tenant(const Tenant &aTenant) noexcept;

    double payRent(double rent);
    void moveOut();

};


#endif //REAL_ESTATE_TYCOON_TENANT_H
