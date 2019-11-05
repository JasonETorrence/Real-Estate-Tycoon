//
// Created by Jason Torrence on 10/24/2019.
//

#include <cstdlib>
#include "Business.h"

/**
 * Business constructor
 */
Business::Business() {
    budget = (rand() % 8001) + 2000;
    size = rand() % 3;
}

/**
 * Business deconstructor
 */
Business::~Business() = default;

/**
 * getSize: returns the business' size value
 * @return the business' size value
 */
int Business::getSize(){
    return size;
}

