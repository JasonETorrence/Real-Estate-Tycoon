//
// Created by Jason Torrence on 10/23/2019.
//

#include <cstdlib>
#include <string>
#include <iostream>
#include "Property.h"
#include "../Utilities/TotallyNotAVector.h"


using namespace std;

Property::Property(){
    bool S = rand() %2;
    bool W = rand() %2;
    if(S && W){
        location = "SW";
    }else if(S) {
        location= "SE";
    }else if(W) {
        location= "NW";
    }else{
        location= "MW";
    }
    propertyTax = 0.015;
    mortgage = 0.0;
    mortgageLeft = 0.0;
    numOfTenants = 0;
    value = 0;
    numOfHomes = 0;
    tenants = new TotallyNotAVector<Tenant>();
    maxRent = 0;
    rent = 0;
}

Property::Property(Property *pProperty) {
    propertyTax = pProperty->getPropertyTax();
    value = pProperty->getValue();
    mortgage = pProperty->getMortgage();
    location = pProperty->getLocation();
    tenants = pProperty->tenants;
    numOfTenants = pProperty->numOfTenants;
    value = pProperty->value;
    numOfHomes = pProperty->numOfHomes;
    maxRent = pProperty->maxRent;
    rent = pProperty->rent;
}

Property & Property::operator=(const Property &right){
    if (&right == this) {
        return (*this);
    }
    propertyTax = right.getPropertyTax();
    value = right.getValue();
    mortgage = right.getMortgage();
    location = right.getLocation();

    return (*this);
}

Property::~Property() = default;

double Property::getValue() const{
    return value;
}
 string Property::getLocation() const{
    return this->location;
}

double Property::getMortgage() const{
    return this->mortgage;
}

double Property::getPropertyTax() const{
    return this->propertyTax;
}

double Property::getMortgageLeft() const{
    return this->mortgageLeft;
}
void Property::reducePriceViaDisaster(){
    std::cout << "A property of value: $" << std::to_string(value);
    if(location == "SE"){
        value *= 0.5;
    }else if(location == "MW"){
        value *= 0.7;
    }else if(location == "NW"){
        value *= 0.9;
    }else{
        value *= 0.75;
    }
    std::cout << " was reduced to: $" << std::to_string(value) << std::endl;
}

void Property::reducePriceViaSMC(){
    std::cout << "A property of value: $" << std::to_string(value);
    value *= 0.7;
    std::cout << " was reduced to: $" << std::to_string(value) << std::endl;
}

void Property::increasePriceViaGentrification(){
    std::cout << "A property of value: $" << std::to_string(value);
    value *= 1.3;
    std::cout << " was increased to: $" << std::to_string(value) << std::endl;
}

string Property::toString(){
    string locationAsString = location;
    return "A property located in the " + locationAsString + " having a value of $" +
        std::to_string(value) + " with a mortgage of $" + std::to_string(mortgage) +
        " and a property tax of " + std::to_string(propertyTax * 100) + "%.";
}

void Property::changeRent(double amount){
    rent += amount;
}


double Property::haveAllTenantsPayRent(TotallyNotAVector<Property> * gameProperties){
    double total = 0;
    for(int i = 0; i < gameProperties->length(); i++){
        for(int j = 0; j < gameProperties->get(i).numOfTenants; j++) {
            total += gameProperties->getReference(i)->tenants->getReference(j)->payRent(gameProperties->getReference(i)->rent);
        }
    }
    return total;
}

double Property::findAndUpdateTotalMortgage(TotallyNotAVector<Property> * gameProperties){
    double total = 0;
    for(int i = 0; i < gameProperties->length(); i++){
        total += gameProperties->get(i).mortgage;
        gameProperties->getReference(i)->updateTotalMortgage(gameProperties->get(i).mortgage);
    }
    return total;
}

double Property::findTotalPropertyTax(TotallyNotAVector<Property>* properties, int numOfProperties){
    double total = 0;
    for(int i = 0; i < numOfProperties; i++){
        total += properties->get(i).value * properties->get(i).propertyTax;
    }
    return total;
}

void Property::updateTotalMortgage(double amount){
    mortgageLeft -= amount;
}