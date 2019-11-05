//
// Created by Jason Torrence on 10/23/2019.
//

#include <cstdlib>
#include <string>
#include <iostream>
#include "Property.h"
#include "../Utilities/TotallyNotAVector.h"

using namespace std;

/**
 * Property constructor. Designed to largely be overwritten.
 */
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
    tenants = new TotallyNotAVector<Tenant*>();
    maxRent = 0;
    rent = 0;
}

/**
 * Property copy constructor
 * @param pProperty : the property to copy
 */
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

/**
 * equals opertator overwrite: copies elements to a new object
 * @param right : the property to copy
 * @return the copied property
 */
Property & Property::operator=(const Property &right){
    if (&right == this) {
        return (*this);
    }
    value = right.getValue();
    location = right.getLocation();
    mortgage = right.getMortgage();
    propertyTax = right.getPropertyTax();
    maxRent = right.getMaxRent();
    rent = right.getRent();
    mortgageLeft = right.getMortgageLeft();
    numOfTenants = right.getNumOfTenants();
    numOfHomes = right.getNumOfHomes();
    tenants = right.getTenants();
    return (*this);
}

/**
 * property deconstructor
 */
Property::~Property(){
    delete tenants;
    delete &tenants;
};

/**
 * getValue: returns the value of the property
 * @return the value of the property
 */
double Property::getValue() const{
    return value;
}

/**
 * getLocation: returns the location of the property
 * @return the location of the property
 */
 string Property::getLocation() const{
    return this->location;
}

/**
 * getMortgage: returns the mortgage value of this property
 * @return the mortgage value of this property
 */
double Property::getMortgage() const{
    return this->mortgage;
}

/**
 * getPropertyTax: returns the property tax value of the property
 * @return the property tax value of the property
 */
double Property::getPropertyTax() const{
    return this->propertyTax;
}

/**
 * getMaxRent: returns the maxRent value of the property
 * @return the maxRent value of the property
 */
double Property::getMaxRent() const{
    return this->maxRent;
}

/**
 * getRent: returns the rent value of the property
 * @return the rent value of the property
 */
double Property::getRent() const{
    return this->rent;
}

/**
 * getMortgageLeft: returns the mortgageLeft value of the property
 * @return the mortgageLeft value of the property
 */
double Property::getMortgageLeft() const{
    return this->mortgageLeft;
}

/**
 * getNumOfTenants: returns the number of tenants associated with this property
 * @return the number of tenants in this property
 */
int Property::getNumOfTenants() const{
    return this->numOfTenants;
}

/**
 * getNumOfHomes: returns the number of homes associated with this property
 * @return the number of homes associated with this property
 */
int Property::getNumOfHomes() const{
    return this->numOfHomes;
}

/**
 * getTenants: returns a TotallyNotAVector pointer associated with the tenants of this property
 * @return a TotallyNotAVector pointer associated with the tenants of this property
 */
TotallyNotAVector<Tenant*> * Property::getTenants() const{
    return this->tenants;
}

/**
 * reducePriceViaDisaster: reduces the prices of properties according to where they are
 */
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

/**
 * reducePriceViaSMC: reduces the prices of a property by 30%
 */
void Property::reducePriceViaSMC(){
    std::cout << "A property of value: $" << std::to_string(value);
    value *= 0.7;
    std::cout << " was reduced to: $" << std::to_string(value) << std::endl;
}

/**
 * increasePriceViaGentrification: increases the price of a property by 30%
 */
void Property::increasePriceViaGentrification(){
    std::cout << "A property of value: $" << std::to_string(value);
    value *= 1.3;
    std::cout << " was increased to: $" << std::to_string(value) << std::endl;
}

/**
 * change rent: a virtual function to be overwritten
 */
void Property::changeRent(){}

/**
 * haveAllTenantsPayRent: a virtual function to be overwritten
 * @return A value representing the amount of rent paid by tenants
 */
double Property::haveAllTenantsPayRent(){}

/**
 * findAndUpdateTotalMortgage: goes through all properties in a list and has their
 * tenants pay rent, then updates the mortgage values as well, returning the difference.
 *
 * @param gameProperties the properties to check for tenants/mortgage
 * @return the difference
 */
double Property::findAndUpdateTotalMortgage(TotallyNotAVector<Property*> * gameProperties){
    double total = 0;
    for(int i = 0; i < gameProperties->length(); i++){
        if(gameProperties->get(i)->mortgageLeft < gameProperties->get(i)->mortgage) {
            total += gameProperties->get(i)->mortgage;
            gameProperties->get(i)->updateTotalMortgage(gameProperties->get(i)->mortgageLeft);
            gameProperties->get(i)->mortgage = gameProperties->get(i)->mortgageLeft;
        }else {
            total += gameProperties->get(i)->mortgage;
            gameProperties->get(i)->updateTotalMortgage(gameProperties->get(i)->mortgage);
        }
    }
    return total;
}

/**
 * findTotalMortgage: finds the total mortgage of all player-owned properties
 *
 * @param gameProperties the properties to find the total mortgage of
 * @return the total mortgage of the properties
 */
double Property::findTotalMortgage(TotallyNotAVector<Property*> * gameProperties){
    double total = 0;
    for(int i = 0; i < gameProperties->length(); i++){
        if(gameProperties->get(i)->mortgageLeft < gameProperties->get(i)->mortgage) {
            total += gameProperties->get(i)->mortgageLeft;
            gameProperties->get(i)->mortgage = gameProperties->get(i)->mortgageLeft;
        }else{
            total += gameProperties->get(i)->mortgage;
        }
    }
    return total;
}

/**
 * findTotalPropertyTax: finds the total propertytax of all properties. This is done
 * by getting the value of all properties and then multiplying it by the property tax.
 *
 * @param properties : the properties to find the property tax of
 * @param numOfProperties : the number of properties to find the tax of
 * @return the total property tax
 */
double Property::findTotalPropertyTax(TotallyNotAVector<Property*>* properties, int numOfProperties){
    double total = 0;
    for(int i = 0; i < numOfProperties; i++){
        total += properties->get(i)->value * properties->get(i)->propertyTax;
    }
    return total;
}

/**
 * updateTotalMortgage: updates the total mortgage by the amount provided
 *
 * @param amount the amount to adjust the total mortgage by
 */
void Property::updateTotalMortgage(double amount){
    mortgageLeft -= amount;
}

/**
 * toString: a virtual function meant to be overwritten
 * @return a toString representing the information of a property.
 */
 std::string Property::toString() {
    return std::__cxx11::string();
}
