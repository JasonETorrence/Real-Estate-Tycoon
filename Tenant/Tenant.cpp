//
// Created by Jason Torrence on 10/23/2019.
//

#include <cstdlib>
#include "Tenant.h"

/**
 * Tenant constructor
 */
Tenant::Tenant(){
    budget = 0;
    agreeability = (rand() % 5) + 1;
}

/**
 * Tenant deconstructor
 */
Tenant::~Tenant() = default;

/**
 * Tenant copy constructor
 *
 * @param aTenant : the tenant to copy
 */
Tenant::Tenant(const Tenant &aTenant) noexcept{
    budget = aTenant.budget;
    agreeability = aTenant.agreeability;
}

/**
 * getBudget: returns the tenant's budget value
 * @return the tenant's budget value
 */
double Tenant::getBudget(){
    return budget;
}

/**
 * getAgreeability: returns the tenant's agreeability value
 * @return the tenant's agreeability value
 */
int Tenant::getAgreeability(){
    return agreeability;
}
