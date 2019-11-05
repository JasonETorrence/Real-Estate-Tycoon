//
// Created by Jason Torrence on 10/24/2019.
//

#include <cstdlib>
#include <iostream>
#include "../Property.h"
#include "BusinessComplex.h"
#include "../../Utilities/Utilities.h"

/**
 * BusinessComplex constructor
 */
BusinessComplex::BusinessComplex(){
    value = (rand() % 200000) + 400000;
    mortgage = (value * 0.001) + (rand() % 5000);
    maxRent = 10000;
    if(mortgage > 5000){
        mortgage = 5000;
    }
    numOfHomes = (rand() % 4) + 2;
    numOfTenants = numOfHomes;
    smallRent = (mortgage/numOfHomes) * 0.5;
    mediumRent = mortgage/numOfHomes;
    largeRent = (mortgage/numOfHomes) * 1.5;
    mortgageLeft = value;
    assignRandomBusinesses();
}

/**
 * BusinessComplex deconstructor
 */
void BusinessComplex::assignRandomBusinesses(){
    for(int i = 0; i < numOfHomes; i++){
        tenants->append(new Business());
    }
}

/**
 * changeRent: change what the rent on this complex is via user input
 */
void BusinessComplex::changeRent() {
    std::cout << "Change rent for what size of BusinessComplex? Type '0' to return." << std::endl;
    std::cout << "(1) Small ($" << std::to_string(smallRent) << ")" << std::endl;
    std::cout << "(2) Medium ($" << std::to_string(mediumRent) << ")" << std::endl;
    std::cout << "(3) Large ($" << std::to_string(largeRent) << ")" << std::endl;
    int selection = getUserInputAsInt(3, 0);
    if(selection == 1){
        std::cout << "Rent for small spaces in this complex is currently: $" << smallRent << std::endl;
        std::cout << "What do you want to change rent to?" << std::endl;
        smallRent = getUserInputAsDouble(10000, 0);
    }else if(selection == 2){
        std::cout << "Rent for medium spaces in this complex is currently: $" << mediumRent << std::endl;
        std::cout << "What do you want to change rent to?" << std::endl;
        mediumRent = getUserInputAsDouble(10000, 0);
    }else if(selection == 3){
        std::cout << "Rent for large spaces in this complex is currently: $" << largeRent << std::endl;
        std::cout << "What do you want to change rent to?" << std::endl;
        largeRent = getUserInputAsDouble(10000, 0);
    }
}

/**
 * removeTenant: removes a specific tenant
 *
 * @param location the location of the tenant
 */
void BusinessComplex::removeTenant(int location) {
    tenants->remove(location);
}

/**
 * toString: returns a string representing the information associated with this complex
 * @return a string representing the information associated with this complex
 */
std::string BusinessComplex::toString(){
    std::string locationAsString = location;
    return "A BUSINESS COMPLEX located in the " + locationAsString + " having a value of $" +
           std::to_string(value) + " with a mortgage of $" + std::to_string(mortgage) +
           " and a property tax of " + std::to_string(propertyTax * 100) + "%. The rent for small spaces is "
            "set at $" + std::to_string(smallRent) + ". The rent for medium spaces is set at $" +
            std::to_string(mediumRent) + ". The rent for large spaces is set at $" + std::to_string(largeRent);
}

/**
 * haveAllTenantsPayRent: attempts to have the complex's tenants pay
 * @return the amount paid by the tenants
 */
double BusinessComplex::haveAllTenantsPayRent(){
    double total = 0;
    for(int i = 0; i < tenants->length(); i++){
        double businessRent = getRentAccordingToSize(((Business*)tenants->get(i))->getSize());
        if(tenants->get(i)->getBudget() > businessRent){
            std::cout << "A business paid rent and increased the value of the property by 1%!"<< std::endl;
            total += businessRent;
            value *= 1.01;
        }else{
            if(tenants->get(i)->getAgreeability() > 2){
                std::cout << "A tenant in the BUSINESS COMPLEX of value: $" << value << " and rent $" << rent
                          << " couldn't afford to pay rent and moved out." << std::endl;
                removeTenant(i);
                total += 0;
            } else {
                std::cout << "A tenant in the BUSINESS COMPLEX of value: $" << value << " and rent $" << rent
                          << " refused to pay rent." << std::endl;
                total += 0;
            }
        }
    }
    return total;
}

/**
 * getRentAccordingToSize: returns the rent value of specific room sizes
 *
 * @param size : the size of the room
 * @return the rent of that size of room
 */
double BusinessComplex::getRentAccordingToSize(int size){
    switch(size){
        case 0:
            return smallRent;
        case 1:
            return mediumRent;
        case 2:
            return largeRent;
        default:
            return 0;
    }
}