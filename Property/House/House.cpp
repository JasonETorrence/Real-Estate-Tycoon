//
// Created by Jason Torrence on 10/24/2019.
//

#include <cstdlib>
#include "House.h"

House::House(){
    value = (rand() % 500000) + 100000;
    mortgage = (value * 0.01) + ((rand() % 5000) - (value * 0.01));
    if(mortgage > 5000){
        mortgage = 5000;
    }
}

House::~House(){
    delete location;
    delete this;
}

void House::assignRandomCivilian(){
    tenant = Civilian();
}

void House::removeTenant(){
    delete &(tenant);
}