//
// Created by Jason Torrence on 10/23/2019.
//

#include <cstdlib>
#include <iostream>
#include "Tenant.h"

Tenant::Tenant() {
    agreeability = rand() % 6;
}

Tenant::~Tenant() = default;

Tenant::Tenant(Tenant *pTenant) {

}

double Tenant::payRent(){
    if(rentedLocation->getMortgage() > budget){
        if(agreeability > 2){
            moveOut();
        }else{
            refuseToPay();
        }
    }else{
        pay();
    }
}

double Tenant::pay(){
 return rentedLocation->getMortgage();
}

void Tenant::moveOut(){
    delete(this);
}

void Tenant::refuseToPay(){
    std::cout << "The tenant in " + rentedLocation->toString() + " refuses to pay" +
    " their rent.";
}



void Tenant::haveAllTenantsPayRent(Property* properties){

}