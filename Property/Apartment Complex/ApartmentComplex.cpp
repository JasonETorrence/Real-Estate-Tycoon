//
// Created by Jason Torrence on 10/24/2019.
//

#include "ApartmentComplex.h"

ApartmentComplex::ApartmentComplex(){
    value = (rand() % 300001) + 300000;
    mortgage = (value * 0.001) + (rand() % 5000);
    maxRent = 5000;
    if(mortgage > 5000){
        mortgage = 5000;
    }
    numOfHomes = (rand() % 6) + 5;
    numOfTenants = numOfHomes;
    assignRandomCivilians();
    rent = mortgage / numOfHomes;
}

void ApartmentComplex::assignRandomCivilians(){
    tenants = new Tenant[numOfHomes];
    for(int i = 0; i < numOfHomes; i++){
        tenants[i] = Civilian();
    }
}

void ApartmentComplex::removeTenant(int location){
    delete &(tenants[location]);
    tenants[location] = Civilian();
}