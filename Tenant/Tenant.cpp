//
// Created by Jason Torrence on 10/23/2019.
//

#include <cstdlib>
#include <iostream>
#include "Tenant.h"

Tenant::Tenant(){
    budget = (rand() % 4501) + 500;
    agreeability = (rand() % 5) + 1;
}

Tenant::~Tenant() = default;

Tenant::Tenant(const Tenant &aTenant) noexcept{
    budget = aTenant.budget;
    agreeability = aTenant.agreeability;
}

double Tenant::payRent(double rent){
    if(rent > budget){
        if(agreeability > 2){
            std::cout << "A tenant moves out due to rent being too high." << std::endl;
            moveOut();
        }else{
            std::cout << "A tenant resfuses to pay." << std::endl;
            return 0;
        }
    }else{
        std::cout << "A tenant pays: $" << rent << std::endl;
        return rent;
    }
}

void Tenant::moveOut(){
    delete(this);
}
