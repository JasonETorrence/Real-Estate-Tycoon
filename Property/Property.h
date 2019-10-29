//
// Created by Jason Torrence on 10/23/2019.
//

#ifndef REAL_ESTATE_TYCOON_PROPERTY_H
#define REAL_ESTATE_TYCOON_PROPERTY_H

#include "../Tenant/Tenant.h"
#include <string>

class Property {

public:
    double value;
    char* location;
    double mortgage;
    double propertyTax;
    double maxRent;
    double rent;
    int numOfTenants;
    int numOfHomes;
    Tenant* tenants;

    Property();
    ~Property();
    Property(Property *pProperty);

    Property & operator=(const Property &right);

    double getValue() const;
    char* getLocation() const;
    double getMortgage() const;
    double getPropertyTax() const;

    static void deleteArrayOfProperties(Property **properties, int size);
    void reducePriceViaDisaster();
    void reducePriceViaSMC();
    void increasePriceViaGentrification();
    static Property remove(Property *properties, int index, int size);
    static Property *append(Property *properties, Property* newProp, int size);
    std::string toString();
    void changeRent(double amount);
};


#endif //REAL_ESTATE_TYCOON_PROPERTY_H
