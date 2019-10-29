//
// Created by Jason Torrence on 10/23/2019.
//

#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>
#include "Property.h"


using namespace std;

Property::Property(){
    bool S = rand() %2;
    bool W = rand() %2;
    location = new char[3];
    if(S && W){
        strcpy(location, "SW");
    }else if(S) {
        strcpy(location, "SE");
    }else if(W) {
        strcpy(location, "NW");
    }else{
        strcpy(location, "MW");
    }
    propertyTax = 0.015;
    mortgage = 0.0;
    numOfTenants = 0;
    value = 0;
    numOfHomes = 0;
    tenants = nullptr;
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

Property::~Property(){
    delete(location);
}

double Property::getValue() const{
    return value;
}

char* Property::getLocation() const{
    return this->location;
}

double Property::getMortgage() const{
    return this->mortgage;
}

double Property::getPropertyTax() const{
    return this->propertyTax;
}


void Property::deleteArrayOfProperties(Property** properties, int size){
    for(int i = 0; i < size; i++){
        delete(properties[i]->location);
        delete(properties[i]);
    }
    delete(properties);
}

void Property::reducePriceViaDisaster(){
    std::cout << "A property of value: $" << std::to_string(value);
    if(strcmp(location, "SE") != 0){
        value *= 0.5;
    }else if(strcmp(location, "MW") != 0){
        value *= 0.7;
    }else if(strcmp(location, "NW") != 0){
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


Property Property::remove(Property * properties, int index, int size){
    Property newGroup[size];
    int j = 0;
    for(int i = 0; i < size; i++, j++){
        if(j != index){
            newGroup[i] = properties[j];
        }else{
            j++;
        }
    }
    properties = newGroup;
    return properties[index];
}

Property* Property::append(Property * properties, Property* newProp, int size){
    Property newProperties[size + 1];
    for(int i = 0; i < size; i++) {
        newProperties[i] = properties[i];
    }
    newProperties[size] = *newProp;
}

string Property::toString(){
    string locationAsString = location;
    return "A property located in the " + locationAsString + " having a value of $" +
        std::to_string(value) + " with a mortgage of $" + std::to_string(mortgage) +
        " and a property tax of " + std::to_string(value * 100) + "%.";
}

void Property::changeRent(double amount){
    rent += amount;
}

