//
// Created by Jason Torrence on 10/24/2019.
//

#include <iostream>
#include "ApartmentComplex.h"
#include "../../Utilities/Utilities.h"

/**
 * ApartmentComplex constructor
 */
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
    mortgageLeft = value;
    assignRandomCivilians();
}

/**
 * assignRandomCivilian: assigns random civilians to the tenants pointer
 */
void ApartmentComplex::assignRandomCivilians(){
    for(int i = 0; i < numOfHomes; i++){
        auto * aCivilian = new Civilian();
        tenants->append(aCivilian);
    }
}

/**
 * removeTenant: removes a specific tenant
 *
 * @param location the location of the tenant
 */
void ApartmentComplex::removeTenant(int location){
    tenants->remove(location);
}

/**
 * toString: returns a string representing the information associated with this complex
 * @return a string representing the information associated with this complex
 */
std::string ApartmentComplex::toString(){
    std::string locationAsString = location;
    return "An APARTMENT COMPLEX located in the " + locationAsString + " having a value of $" +
           std::to_string(value) + " with a mortgage of $" + std::to_string(mortgage) +
           " and a property tax of " + std::to_string(propertyTax * 100) + "%. The rent is set at $" +
           std::to_string(getRent()) + ". There are " + std::to_string(tenants->length()) +
           " tenants in this complex.";
}

/**
 * haveAllTenantsPayRent: attempts to have the complex's tenants pay
 * @return the amount paid by the tenants
 */
double ApartmentComplex::haveAllTenantsPayRent() {
    double total = 0;
    for (int i = 0; i < tenants->length(); i++) {
        if (tenants->get(i)->getBudget() >= rent) {
            total += rent;
        } else {
            if (tenants->get(i)->getAgreeability() > 2) {
                std::cout << "A tenant in the APARTMENT COMPLEX of value: $" << value << " and rent $" << rent
                          << " couldn't afford to pay rent and moved out." << std::endl;
                removeTenant(i);
                total += 0;
            } else {
                std::cout << "A tenant in the APARTMENT COMPLEX of value: $" << value << " and rent $" << rent
                          << " refused to pay rent." << std::endl;
                total += 0;
            }
        }
    }
    return total;
}

/**
 * changeRent: change what the rent on this complex is via user input
 */
void ApartmentComplex::changeRent() {
    std::cout << "What do you want to change rent to?" << std::endl;
    rent = getUserInputAsDouble(maxRent, 0);
}
