//
// Created by Jason Torrence on 10/24/2019.
//

#include <cstdlib>
#include <iostream>
#include "House.h"
#include "../../Utilities/Utilities.h"

/**
 * House constructor
 */
House::House(){
    value = (rand() % 500000) + 100000;
    mortgage = (value * 0.01) + ((rand() % 5000) - (value * 0.01));
    maxRent = 5000;
    rent = mortgage;
    mortgageLeft = value;
    if(mortgage > 5000){
        mortgage = 5000;
    }
    numOfHomes = 1;
    numOfTenants = 1;
    tenants = new TotallyNotAVector<Tenant*>();
    assignRandomCivilian();
}

/**
 * house deconstructor
 */
House::~House(){
    delete tenants;
    delete &tenants;
}

/**
 * assignRandomCivilian: assigns a random civilian to the house.
 */
void House::assignRandomCivilian(){
    auto * civilian = new Civilian();
    tenants->append(civilian);
}

/**
 * removeTenant: removes a speicific tenant from the house
 * @param location
 */
void House::removeTenant(int location){
    tenants->remove(location);
}

/**
 * toString: returns a string representing the information associated with this house
 * @return a string representing the information associated with this house
 */
std::string House::toString() {
    std::string locationAsString = location;
    return "A HOUSE located in the " + locationAsString + " having a value of $" +
           std::to_string(value) + " with a mortgage of $" + std::to_string(mortgage) +
           " and a property tax of " + std::to_string(propertyTax * 100) + "%. The rent is set at $" +
           std::to_string(getRent()) + ".";
}

/**
 * haveAllTenantsPayRent: attempts to have the house's tenant pay
 * @return the amount paid by the tenant
 */
double House::haveAllTenantsPayRent(){
    if(tenants->length() > 0) {
        if (tenants->get(0)->getBudget() >= rent) {
            return rent;
        } else {
            if (tenants->get(0)->getAgreeability() > 2) {
                std::cout << "The tenant in the HOUSE of value: $" << value << " and rent $" << rent
                          << " couldn't afford";
                std::cout << " to pay rent and moved out." << std::endl;
                removeTenant(0);
                return 0;
            } else {
                std::cout << "The tenant in the HOUSE of value: $" << value << " and rent $" << rent
                          << " refused to pay";
                std::cout << " rent." << std::endl;
                return 0;
            }
        }
    }else{
        return 0;
    }
}

/**
 * changeRent: change what the rent on this house is via user input
 */
void House::changeRent() {
    std::cout << "What do you want to change rent to?" << std::endl;
    rent = getUserInputAsDouble(maxRent, 0);
}
