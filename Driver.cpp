//
// Created by Jason Torrence on 10/29/2019.
//

#include "Driver.h"
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "Player/Player.h"
#include "Property/House/House.h"
#include "Property/Apartment Complex/ApartmentComplex.h"
#include "Property/Business Complex/BusinessComplex.h"
#include "Utilities/Utilities.h"

#define UserQuits 0
#define UserWaits 1

using namespace std;

//prototyping!
int collectUserInput(Player &player, TotallyNotAVector<Property> * gameProperties,
        TotallyNotAVector<int>* randProperties);
bool userDoesThings(Player &player, TotallyNotAVector<Property> * gameProperties,
        TotallyNotAVector<int>* randProperties);
void GenerateRandProperties(TotallyNotAVector<Property> * gameProperties);
int buyProperty(TotallyNotAVector<Property> * gameProperties, TotallyNotAVector<int>*, Player &player);
int sellProperty(Player &player);
int changePropertyRent(Player &player);
void checkForRandom(Player &player);
void doRandomEvent(int event, const string& randomLocation, Player &player);
string chooseRandomLocation();
void payMortgageAndGetRent(Player &player);
void payPropertyTax(Player &player);
bool playerWinsOrLoses(Player &player);
void printAllInformationFromVectors(TotallyNotAVector<Property> * gameProperties,
                                    TotallyNotAVector<Property> * playerProperties,
                                    TotallyNotAVector<int> * locations);

void driver(){
    Player player;
    auto * gameProperties = new TotallyNotAVector<Property>;
    GenerateRandProperties(gameProperties);
    int* indices;
    auto * randomPropertiesForThisTurn = new TotallyNotAVector<int>(fillAndShuffleIntPointer(indices, 20), 20);
    int turn = 1;
    while(true){
        bool checkIfUserQuits = userDoesThings(player, gameProperties, randomPropertiesForThisTurn);
        if(checkIfUserQuits)
            break;
        checkForRandom(player);
        payMortgageAndGetRent(player);
        if(turn % 12 == 0){
            payPropertyTax(player);
        }
        turn++;
        if(playerWinsOrLoses(player))
            break;
    }
}

bool userDoesThings(Player &player, TotallyNotAVector<Property> * gameProperties,
        TotallyNotAVector<int>* randProperties){
    while(true){
        cout << "What do you want to do?" << endl;
        cout << "Options:" << endl;
        giveOptionsAsToWhatToDo();
        int whatTheUserDid = collectUserInput(player, gameProperties, randProperties);
        //printAllInformationFromVectors(player.properties, gameProperties, randProperties);
        if(whatTheUserDid == UserQuits){
            return true;
        }else if(whatTheUserDid == UserWaits){
            return false;
        }
    }
}

void giveOptionsAsToWhatToDo(){
    cout << "(B)uy a property." << endl;
    cout << "(S)ell a propertty." << endl;
    cout << "(C)hange rent on a property." << endl;
    cout << "(W)ait a turn." << endl;
    cout << "(Q)uit." << endl;
}

int collectUserInput(Player &player, TotallyNotAVector<Property> * gameProperties, TotallyNotAVector<int>* randProperties){
    string userInput;
    while(true){
        getline(cin, userInput);
        if(userInput.substr(0,1) == "B"){
            return buyProperty(gameProperties, randProperties, player);
        }else if(userInput.substr(0,1) == "S"){
            return sellProperty(player);
        }else if(userInput.substr(0,1) == "C"){
            return changePropertyRent(player);
        }else if(userInput.substr(0,1) == "W"){
            return UserWaits;
        }else if(userInput.substr(0,1) == "Q"){
            return UserQuits;
        }else {
            cout << "invalid input, please enter:" << endl;
            giveOptionsAsToWhatToDo();
        }
    }
}

void GenerateRandProperties(TotallyNotAVector<Property> * gameProperties){
    std::minstd_rand generator((int)time(nullptr));
    if(gameProperties->length() > 0){
        gameProperties->clear();
    }
    for(int i = 0; i < 20; i++) {
        unsigned int random = generator() % 3;
        if(random == 0){
            gameProperties->append(new House());
        }else if(random == 1){
            gameProperties->append(new ApartmentComplex());
        }else{
            gameProperties->append(new BusinessComplex());
        }
    }
}

int buyProperty(TotallyNotAVector<Property> * gameProperties, TotallyNotAVector<int>* selections, Player &player){
    cout << "Possible properties to buy:" << endl;
    if(gameProperties->length() < 3){
        delete selections;
        GenerateRandProperties(gameProperties);
        int* indices;
        selections = new TotallyNotAVector<int>(fillAndShuffleIntPointer(indices, 20), 20);
    }
    for(int i = 0; i < 3; i++){
        cout << "(" << i + 1 << ") " << gameProperties->get(selections->get(i)).toString() << endl;
    }
    cout << "Enter the number of the property you wish to purchase." << endl;
    int selectedProperty = getUserInputAsInt(3,1) - 1;
    if(gameProperties->get(selections->get(selectedProperty)).getMortgage() > player.getBank()){
        cout << "The bank turns you down, you lack the funds to get this property!" << endl;
    }else{
        player.properties->append(gameProperties->remove(selections->remove(selectedProperty)));
    }
    return 2;
}

int sellProperty(Player &player){
    cout << "Which property do you wish to sell?" << endl;
    cout << "Owned Properties:" << endl;
    for(int i = 0; i < player.properties->length(); i++){
        cout << "(" << i+1 << ") " << player.properties->get(i).toString() << endl;
    }
    int selection = getUserInputAsInt(1, player.properties->length());
    player.updateBank(player.properties->get(selection).getValue() - player.properties->get(selection).getMortgage() );
    player.properties->remove(selection);
    return 2;
}

int changePropertyRent(Player &player){
    cout << "You have $" << player.bank << endl;
    cout << "Which property do you want to change your rent on?" << endl;
    player.printPropertiesToSTDOut();
    int selection = getUserInputAsInt(player.properties->length(), 1);
    cout << "How much do you want to change rent by?" << endl;
    double maxUp = player.properties->get(selection).maxRent -  player.properties->get(selection).rent;
    double amount = getUserInputAsDouble(maxUp, 0);
    player.properties->get(selection).changeRent(amount);
    return 2;
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
        for (int i = 0; i < player.properties->length(); i++) {
            if (player.properties->get(i).location == randomLocation) {
                player.properties->get(i).reducePriceViaDisaster();
            }
        }
    }else if(event == 1) {
        for (int i = 0; i < player.properties->length(); i++) {
            if (player.properties->get(i).location == randomLocation) {
                player.properties->get(i).reducePriceViaSMC();
            }
        }
    }else{
        for(int i = 0; i < player.properties->length(); i++){
            if(player.properties->get(i).location == randomLocation){
                player.properties->get(i).increasePriceViaGentrification();
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

void payMortgageAndGetRent(Player &player){
    double rentTotal = Property::haveAllTenantsPayRent(player.properties);
    double mortgageTotal = Property::findAndUpdateTotalMortgage(player.properties);
    double difference = rentTotal - mortgageTotal;
    cout << "Total amount made from rent: $" << rentTotal << endl;
    cout << "Total amount paid for mortgage: $" << mortgageTotal << endl;
    cout << "Difference: $" << difference << endl;
    player.updateBank(difference);
    cout << "Your bank is now at $" << player.bank << endl;
}

void payPropertyTax(Player &player){
    double totalPropertyTax = Property::findTotalPropertyTax(player.properties, player.properties->length());
    cout << "A year has passed and you owe property tax on your properties!" << endl;
    cout << "You are charged: $" << totalPropertyTax << endl;
    player.updateBank(-totalPropertyTax);
}

bool playerWinsOrLoses(Player &player){
    if(player.bank >= 1000000){
        cout << "You broke $1000000, and you won!" << endl;
        return true;
    }else if(player.bank <= 0){
        cout << "You went bankrupt! Loser, go fuck yourself." << endl;
        return true;
    }else{
        return false;
    }
}

void printAllInformationFromVectors(TotallyNotAVector<Property> * gameProperties,
        TotallyNotAVector<Property> * playerProperties,
        TotallyNotAVector<int> * locations){

    for(int i = 0; i < gameProperties->length(); i++){
        cout << i << ": " << gameProperties->get(i).toString() << endl;
    }
    for(int i = 0; i < playerProperties->length(); i++){
        cout << i << ": " << playerProperties->get(i).toString() << endl;
    }
    for(int i = 0; i < locations->length(); i++){
        cout << i << ": " << locations->get(i) << endl;
    }
}