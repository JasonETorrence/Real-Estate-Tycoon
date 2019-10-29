//
// Created by Jason Torrence on 10/24/2019.
//

#include <cstdlib>
#include "Business.h"

Business::Business() {
    budget = (rand() % 8001) + 2000;
}

Business::~Business() = default;