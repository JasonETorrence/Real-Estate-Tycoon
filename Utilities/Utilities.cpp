//
// Created by Jason Torrence on 10/23/2019.
//

#include <string>
#include <iostream>

using namespace std;

/**
 * getUserInputAsInt: gets the user input between certain bounds and returns that value
 *
 * @param upperBound the upperbound
 * @param lowerBound the lowerbound
 * @return the userinputed value
 */
int getUserInputAsInt(int upperBound, int lowerBound){
    string userInput;
    bool userInputIsInvalid = true;
    int userInputAsInt = 0;
    while(userInputIsInvalid){
        getline(cin, userInput);
        if(userInput.find_first_not_of("0123456789") != string::npos){
            cout << "Please enter a value between " << lowerBound << " and " << upperBound << endl;
            continue;
        }
        userInputAsInt = stoi(userInput);
        if(userInputAsInt < lowerBound || userInputAsInt > upperBound){
            cout << "Please enter a value between " << lowerBound << " and " << upperBound << endl;
        }else{
            userInputIsInvalid = false;
        }
    }
    return userInputAsInt;
}

/**
 * getUserInputAsInt: gets the user input between certain bounds and returns that value
 *
 * @param upperBound the upperbound
 * @param lowerBound the lowerbound
 * @return the userinputed value
 */
double getUserInputAsDouble(double upperBound, double lowerBound){
    string userInput;
    bool userInputIsInvalid = true;
    double userInputAsDouble = 0;
    while(userInputIsInvalid){
        getline(cin, userInput);
        if(userInput.find_first_not_of("0123456789.") != string::npos){
            cout << "Please enter a value between " << lowerBound << " and " << upperBound << endl;
            continue;
        }
        userInputAsDouble = stod(userInput);
        if(userInputAsDouble < lowerBound || userInputAsDouble > upperBound){
            cout << "Please enter a value between " << lowerBound << " and " << upperBound << endl;
        }else{
            userInputIsInvalid = false;
        }
    }
    return userInputAsDouble;

}

/**
 * fillAndShuffleIntPointer: takes an int array, fills it, and shuffles it.
 *
 * @param array : an array to fill
 * @param length : the number of ints to fill it with
 * @return the new int pointer
 */
int* fillAndShuffleIntPointer(int* array, int length){
    array = new int[length];
    for(int i = 0; i < length; i++){
        array[i] = i;
    }
    for(int i = 0; i < length; i++){
        int randomLocation = rand() % length;
        int placeholder = array[i];
        array[i] = array[randomLocation];
        array[randomLocation] = placeholder;
    }
    return array;
}

