//
// Created by Jason Torrence on 10/23/2019.
//

#ifndef REAL_ESTATE_TYCOON_TENANT_H
#define REAL_ESTATE_TYCOON_TENANT_H

class Tenant {
protected:
    double budget;
    int agreeability;
public:
    Tenant();
    ~Tenant();

    Tenant(const Tenant &aTenant) noexcept;

    double getBudget();
    int getAgreeability();
};


#endif //REAL_ESTATE_TYCOON_TENANT_H
