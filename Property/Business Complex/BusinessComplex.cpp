//
// Created by Jason Torrence on 10/24/2019.
//

#include <cstdlib>
#include "../Property.h"
#include "BusinessComplex.h"

BusinessComplex::BusinessComplex(){
    value = (rand() % 200000) + 400000;
    mortgage = (value * 0.001) + (rand() % 5000);
    maxRent = 10000;
    if(mortgage > 5000){
        mortgage = 5000;
    }
    numOfHomes = (rand() % 4) + 2;
    numOfTenants = numOfHomes;
    rent = mortgage/numOfHomes;
    mortgageLeft = mortgage;
    assignRandomBusinesses();
}

void BusinessComplex::assignRandomBusinesses(){
    for(int i = 0; i < numOfHomes; i++){
        tenants->append( Business());
    }
}

void BusinessComplex::removeTenant(int location) {
    tenants->remove(location);
}
