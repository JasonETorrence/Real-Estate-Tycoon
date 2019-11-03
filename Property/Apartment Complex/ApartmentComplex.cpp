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
    rent = mortgage / numOfHomes;
    mortgageLeft = mortgage;
    assignRandomCivilians();
}

void ApartmentComplex::assignRandomCivilians(){
    for(int i = 0; i < numOfHomes; i++){
        auto * aCivilian = new Civilian();
        tenants->append(*aCivilian);
    }
}

void ApartmentComplex::removeTenant(int location){
    tenants->remove(location);
}