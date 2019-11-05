//
// Created by Jason Torrence on 10/23/2019.
//

#include <ctime>
#include <cstdlib>
#include "Driver.h"

/**
 * main: it's main. seeds random and calls the driver.
 * @return possible error code
 */
int main() {
    srand(time(0));
    driver();
    return 0;
}

