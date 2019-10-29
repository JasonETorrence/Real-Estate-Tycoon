//
// Created by Jason Torrence on 10/24/2019.
//

#include <cstdlib>
#include "Civilian.h"

Civilian::Civilian() {
    budget = (rand() % 4501) + 500;
}

Civilian::~Civilian() = default;
