//
// Created by Jason Torrence on 10/23/2019.
//

#ifndef REAL_ESTATE_TYCOON_PROPERTY_H
#define REAL_ESTATE_TYCOON_PROPERTY_H


#include "../Tenant/Tenant.h"

class Property {


public:
    double value;
    char* location;
    double mortgage;
    double propertyTax;
    int numOfTenants;
    Tenant* Tenants;

    Property();

    explicit Property(Property *pProperty);

    ~Property();

    Property & operator=(Property right);

    double getValue();
    char* getLocation();
    double getMortgage();
    double getPropertyTax();

    static void deleteArrayOfProperties(Property **properties, int size);
    void reducePriceViaDisaster();
    void reducePriceViaSMC();
    void increasePriceViaGentrification();
    static Property* remove(Property **properties, int index, int size);
    static Property *append(Property **properties, Property* newProp, int size);
    std::string toString();

};


#endif //REAL_ESTATE_TYCOON_PROPERTY_H
