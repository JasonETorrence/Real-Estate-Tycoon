//
// Created by Jason Torrence on 10/24/2019.
//

#include <cstdlib>
#include "House.h"

House::House(){
    value = (rand() % 500000) + 100000;
    mortgage = (value * 0.01) + ((rand() % 5000) - (value * 0.01));
    maxRent = 5000;
    rent = mortgage;
    mortgageLeft = mortgage;
    if(mortgage > 5000){
        mortgage = 5000;
    }
    numOfHomes = 1;
    numOfTenants = 1;
    assignRandomCivilian();
}

House::~House(){}

void House::assignRandomCivilian(){
    auto * civilian = new Civilian();
    tenants->append(*civilian);
}

void House::removeTenant(int location){
    tenants->remove(location);
}