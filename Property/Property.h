//
// Created by Jason Torrence on 10/23/2019.
//

#ifndef REAL_ESTATE_TYCOON_PROPERTY_H
#define REAL_ESTATE_TYCOON_PROPERTY_H

#include "../Tenant/Tenant.h"
#include "../Utilities/TotallyNotAVector.h"
#include <string>

class Property {

protected:
    double value;
    std::string location;
    double mortgage;
    double propertyTax;
    double maxRent;
    double rent;
    double mortgageLeft;
    int numOfTenants;
    int numOfHomes;
    TotallyNotAVector<Tenant*> * tenants;

public:
    Property();
    ~Property();
    Property(Property *pProperty);

    Property & operator=(const Property &right);
    double getValue() const;
    std::string getLocation() const;
    double getMortgage() const;
    double getPropertyTax() const;
    double getMortgageLeft() const;
    double getMaxRent() const;
    double getRent() const;
    int getNumOfTenants() const;
    int getNumOfHomes() const;
    TotallyNotAVector<Tenant*>* getTenants() const;
    void reducePriceViaDisaster();
    void reducePriceViaSMC();
    void increasePriceViaGentrification();

    virtual std::string toString();
    virtual void changeRent();
    virtual double haveAllTenantsPayRent();

    static double findAndUpdateTotalMortgage(TotallyNotAVector<Property*> * gameProperties);
    static double findTotalPropertyTax(TotallyNotAVector<Property*>* properties, int numOfProperties);
    void updateTotalMortgage(double amount);
    static double findTotalMortgage(TotallyNotAVector<Property*> *gameProperties);
};


#endif //REAL_ESTATE_TYCOON_PROPERTY_H
