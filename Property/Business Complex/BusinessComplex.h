//
// Created by Jason Torrence on 10/24/2019.
//

#ifndef REAL_ESTATE_TYCOON_BUSINESSCOMPLEX_H
#define REAL_ESTATE_TYCOON_BUSINESSCOMPLEX_H


#include "../../Tenant/Business/Business.h"

class BusinessComplex : public Property{

public:

    BusinessComplex();
    void assignRandomBusinesses();
    void removeTenant(int location);

};


#endif //REAL_ESTATE_TYCOON_BUSINESSCOMPLEX_H
