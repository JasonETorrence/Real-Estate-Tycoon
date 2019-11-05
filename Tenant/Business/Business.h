//
// Created by Jason Torrence on 10/24/2019.
//

#ifndef REAL_ESTATE_TYCOON_BUSINESS_H
#define REAL_ESTATE_TYCOON_BUSINESS_H


#include "../Tenant.h"

class Business : public Tenant{
protected:
    int size;
public:
    Business();
    ~Business();

    int getSize();
};


#endif //REAL_ESTATE_TYCOON_BUSINESS_H
