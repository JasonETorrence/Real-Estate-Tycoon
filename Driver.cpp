//
// Created by Jason Torrence on 10/29/2019.
//

#include "Driver.h"
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <cstring>
#include "Player/Player.h"
#include "Property/House/House.h"
#include "Property/Apartment Complex/ApartmentComplex.h"
#include "Property/Business Complex/BusinessComplex.h"
#include "Utilities/Utilities.h"

#define UserQuits false
#define UserWaits true

using namespace std;

bool collectUserInput(Player &player, Property* properties, int* randProperties);
void GenerateRandProperties(Property* properties);
bool buyProperty(Property* properties, const int* selections, Player &player);
void generateRandomSelections(int* selections, int numSelections, int bound);
bool sellProperty(Player &player);
bool changePropertyRent(Player &player);
void checkForRandom(Player &player);
void doRandomEvent(int event, const string& randomLocation, Player &player);
string chooseRandomLocation();

void driver(){
    Player player;
    bool gameIsBeingPlayed = true;
    Property* properties = nullptr;
    GenerateRandProperties(properties);
    int* randomPropertiesForThisTurn = nullptr;
    while(gameIsBeingPlayed){
        generateRandomSelections(randomPropertiesForThisTurn, 3, 20);
        cout << "What do you want to do?" << endl;
        cout << "Options:" << endl;
        giveOptionsAsToWhatToDo();
        gameIsBeingPlayed = collectUserInput(player, properties, randomPropertiesForThisTurn);
        checkForRandom(player);






    }
}

void giveOptionsAsToWhatToDo(){
    cout << "(B)uy a property." << endl;
    cout << "(S)ell a propertty." << endl;
    cout << "(C)hange rent on a property." << endl;
    cout << "(W)ait a turn." << endl;
    cout << "(Q)uit." << endl;
}

bool collectUserInput(Player &player, Property* properties, int* randProperties){
    string userInput;
    bool userInputIsInvalid = true;
    while(userInputIsInvalid){
        getline(cin, userInput);
        if(userInput.substr(0,1) == "B"){
            return buyProperty(properties, randProperties, player);
        }else if(userInput.substr(0,1) == "S"){
            return sellProperty(player);
        }else if(userInput.substr(0,1) == "C"){
            return changePropertyRent(player);
        }else if(userInput.substr(0,1) == "W"){
            return UserWaits;
        }else if(userInput.substr(0,1) == "Q"){
            return UserQuits;
        }else{
            cout << "invalid input, please enter:" << endl;
            giveOptionsAsToWhatToDo();
        }
    }
}

void GenerateRandProperties(Property* properties){
    properties = new Property[20];
    std::minstd_rand generator((int)time(nullptr));
    for(int i = 0; i < 20; i++) {
        unsigned int random = generator() % 3;
        if(random == 0){
            properties[i] = new House();
        }else if(random == 1){
            properties[i] = new ApartmentComplex();
        }else{
            properties[i] = new BusinessComplex();
        }
    }
}

bool buyProperty(Property* properties, const int* selections, Player &player){
    cout << "Possible properties to buy:" << endl;
    for(int i = 3; i < 3; i++){
        cout << "(" << i + 1 << ") " << properties[selections[i]].toString() << endl;
    }
    cout << "Enter the number of the property you wish to purchase." << endl;
    int selectedProperty = getUserInputAsInt(3,1);
    if(properties[selections[selectedProperty]].getMortgage() > player.getBank()){
        cout << "The bank turns you down, you lack the funds to get this property!" << endl;
    }else{
        player.buyProperty(&properties[selections[selectedProperty]]);
    }
    return true;
}

void generateRandomSelections(int* selections, int numSelections, int bound){
    std::minstd_rand generator((int)time(nullptr));
    for(int i = 0; i < numSelections; i++){
        selections[i] = generator() % bound;
    }
}

bool sellProperty(Player &player){
    cout << "Which property do you wish to sell?" << endl;
    cout << "Owned Properties:" << endl;
    for(int i = 0; i < player.numOfProperties; i++){
        cout << "(" << i+1 << ") " << player.properties[i].toString() << endl;
    }
    int selection = getUserInputAsInt(1, player.numOfProperties);
    player.updateBank(player.properties[selection].getValue());
    Property::remove(player.properties, selection, player.numOfProperties);
    return true;
}

bool changePropertyRent(Player &player){
    cout << "Which property do you want to change your rent on?" << endl;
    player.printPropertiesToSTDOut();
    int selection = getUserInputAsInt(player.numOfProperties, 1);
    cout << "How much do you want to change rent by?" << endl;
    double maxUp = player.properties[selection].maxRent -  player.properties[selection].rent;
    double amount = getUserInputAsDouble(maxUp, 0);
    player.properties[selection].changeRent(amount);
}

void checkForRandom(Player &player){
    for(int i = 0; i < 3; i++) {
        if ((rand() % 100) <= 5) {
            string randomLocation = chooseRandomLocation();
            doRandomEvent(i, randomLocation, player);
        }
    }
}

void doRandomEvent(int event, const string& randomLocation, Player &player) {
    if(event == 0) {
        for (int i = 0; i < player.numOfProperties; i++) {
            if (player.properties[i].location == randomLocation) {
                player.properties[i].reducePriceViaDisaster();
            }
        }
    }else if(event == 1) {
        for (int i = 0; i < player.numOfProperties; i++) {
            if (player.properties[i].location == randomLocation) {
                player.properties[i].reducePriceViaSMC();
            }
        }
    }else{
        for(int i = 0; i < player.numOfProperties; i++){
            if(player.properties[i].location == randomLocation){
                player.properties[i].increasePriceViaGentrification();
            }
        }
    }
}

string chooseRandomLocation(){
    string randomLocation;
    int random = (rand() % 4);
    if(random == 0){
        randomLocation = "SW";
    }else if(random == 1){
        randomLocation = "MW";
    }else if(random == 2){
        randomLocation = "NW";
    }else if(random == 3){
        randomLocation = "SE";
    }
    return randomLocation;
}

void haveAllTenantsPayRent(){

}