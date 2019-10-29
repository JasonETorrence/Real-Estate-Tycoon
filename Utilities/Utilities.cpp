//
// Created by sarge on 10/23/2019.
//

#include <string>
#include <iostream>
#include "Utilities.h"

using namespace std;

int getUserInputAsInt(int upperBound, int lowerBound){
    string userInput;
    bool userInputIsInvalid = true;
    int userInputAsInt = 0;
    while(userInputIsInvalid){
        getline(cin, userInput);
        userInputAsInt = stoi(userInput);
        if(userInputAsInt < lowerBound || userInputAsInt > upperBound){
            cout << "Please enter a value between" << lowerBound << " and " << upperBound << endl;
        }else{
            userInputIsInvalid = false;
        }
    }
    return userInputAsInt;
}

double getUserInputAsDouble(double upperBound, double lowerBound){
    string userInput;
    bool userInputIsInvalid = true;
    double userInputAsDouble = 0;
    while(userInputIsInvalid){
        getline(cin, userInput);
        userInputAsDouble = stod(userInput);
        if(userInputAsDouble < lowerBound || userInputAsDouble > upperBound){
            cout << "Please enter a value between" << lowerBound << " and " << upperBound << endl;
        }else{
            userInputIsInvalid = false;
        }
    }
    return userInputAsDouble;

}