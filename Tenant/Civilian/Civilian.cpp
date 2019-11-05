//
// Created by Jason Torrence on 10/24/2019.
//

#include <cstdlib>
#include "Civilian.h"

/**
 * Civilian constructor
 */
Civilian::Civilian() {
    budget = (rand() % 4501) + 500;
}

/**
 * Civilian deconstructor
 */
Civilian::~Civilian() = default;
