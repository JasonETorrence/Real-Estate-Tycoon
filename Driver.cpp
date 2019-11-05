//
// Created by Jason Torrence on 10/29/2019.
//
// A game created to show the use of polymorphism, virtual functions, and what is required
// to call them.
//

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "Player/Player.h"
#include "Property/House/House.h"
#include "Property/ApartmentComplex/ApartmentComplex.h"
#include "Property/BusinessComplex/BusinessComplex.h"
#include "Utilities/Utilities.h"

#define UserQuits 0
#define UserWaits 1

using namespace std;

//prototyping!
TotallyNotAVector<Property*>* getUniqueRandomProperties(TotallyNotAVector<Property*>* properties);
int collectUserInput(Player &player, TotallyNotAVector<Property*> * randProperties);
bool userDoesThings(Player &player, TotallyNotAVector<Property*> * randProperties);
void giveOptionsAsToWhatToDo(Player &player);
void GenerateRandProperties(TotallyNotAVector<Property*> * gameProperties);
int buyProperty(TotallyNotAVector<Property*> * randProperties, Player &player);
void checkForNotEnoughProperties(TotallyNotAVector<Property*> * gameProperties);
int sellProperty(Player &player);
double attemptPropertySale(double salePrice, double remainingMortgage);
int changePropertyRent(Player &player);
void checkForRandom(Player &player);
void doRandomEvent(int event, const string& randomLocation, Player &player);
void disasterOccurs(string location, Player &player);
void stockMarketCrashes(Player &player);
void gentrificationOccurs(string location, Player &player);
string chooseRandomLocation();
void payMortgageAndGetRent(Player &player);
void payPropertyTax(Player &player);
bool playerWinsOrLoses(Player &player);
void printAllInformationFromVectors(TotallyNotAVector<Property*> * gameProperties,
                                    TotallyNotAVector<Property*> * playerProperties,
                                    TotallyNotAVector<Property*> * randomProperties);

/**
 * Driver: Sets up the classes for function calls and then calls the functions and
 * methods in the order they're supposed to be called in.
 */
void driver(){
    Player player;
    auto * gameProperties = new TotallyNotAVector<Property*>;
    GenerateRandProperties(gameProperties);
    int turn = 1;
    while(true){
        checkForNotEnoughProperties(gameProperties);
        auto * randProperties = getUniqueRandomProperties(gameProperties);
        printAllInformationFromVectors(gameProperties, player.getProperties(), randProperties);
        bool checkIfUserQuits = userDoesThings(player, randProperties);
        if(checkIfUserQuits) break;
        checkForRandom(player);
        payMortgageAndGetRent(player);
        if(turn % 12 == 0)
            payPropertyTax(player);
        turn++;
        if(playerWinsOrLoses(player)) break;
        delete randProperties;
    }
    delete gameProperties;
}

/**
 * getUniqueRandomProperties: pulls unique random values out of the properties list.
 *
 * @param properties : the properties to pull out of.
 * @return TotallyNotAVector<Property*>* : a list of random properties
 */
TotallyNotAVector<Property*>* getUniqueRandomProperties(TotallyNotAVector<Property*>* properties) {
    int* indices;
    int numProperties = properties->length();
    auto* uniqueRandomValues = new TotallyNotAVector<int>(fillAndShuffleIntPointer(indices, numProperties), numProperties);
    auto* randomProperties = new TotallyNotAVector<Property*>();
    for(int i = 0; i < 3; i++){
        randomProperties->append(properties->remove(uniqueRandomValues->remove()));
        uniqueRandomValues->clear();
        numProperties = properties->length();
        uniqueRandomValues = new TotallyNotAVector<int>(fillAndShuffleIntPointer(indices, numProperties), numProperties);
    }
    return randomProperties;
}

/**
 * useDoesThings: Asks the user what they want to do, and calls functions according to what
 * they want to do.
 *
 * @param player : the players information to use later on
 * @param randProperties : the random properties to use during this turn
 * @return a boolean to tell the caller whether the user quit or not
 */
bool userDoesThings(Player &player, TotallyNotAVector<Property*> * randProperties){
    while(true){
        cout << "What do you want to do?" << endl;
        cout << "Options:" << endl;
        giveOptionsAsToWhatToDo(player);
        int whatTheUserDid = collectUserInput(player, randProperties);
        if(whatTheUserDid == UserQuits){
            return true;
        }else if(whatTheUserDid == UserWaits){
            return false;
        }
    }
}

/**
 * giveOptionsAsToWhatToDo: Prints the options as to what the user can do to the screen
 *
 * @param player : the player to pull information from
 */
void giveOptionsAsToWhatToDo(Player &player){
    double totalMortage = Property::findTotalMortgage(player.getProperties());
    cout << "(B)uy a property." << endl;
    cout << "(S)ell a property." << endl;
    cout << "(C)hange rent on a property." << endl;
    cout << "(W)ait a turn." << endl;
    cout << "(Q)uit." << endl;
    cout << "You currently have $" << player.getBank() << " and will owe $" << totalMortage << " at the end of this turn."
        << endl;
}

/**
 * collectUserInput: collects user input and either continues asking the user what to do
 * or allows another turn to occur or has the caller return a boolean suggesting that the
 * user quit. All of this is based on user input.
 *
 * @param player : the player to push/pull information from/to.
 * @param randProperties : the random purchasable properties for this turn.
 * @return : an int to tell the caller whether the user quit, continued, or waited.
 */
int collectUserInput(Player &player, TotallyNotAVector<Property*> * randProperties){
    string userInput;
    while(true){
        getline(cin, userInput);
        if(userInput.substr(0,1) == "B" or userInput.substr(0,1) == "b"){
            return buyProperty(randProperties, player);
        }else if(userInput.substr(0,1) == "S" or userInput.substr(0,1) == "s"){
            return sellProperty(player);
        }else if(userInput.substr(0,1) == "C" or userInput.substr(0,1) == "c"){
            return changePropertyRent(player);
        }else if(userInput.substr(0,1) == "W" or userInput.substr(0,1) == "w"){
            return UserWaits;
        }else if(userInput.substr(0,1) == "Q" or userInput.substr(0,1) == "q"){
            return UserQuits;
        }else {
            cout << "invalid input, please enter:" << endl;
            giveOptionsAsToWhatToDo(player);
        }
    }
}

/**
 * generateRandProperties: fills the TotallyNotAVector object sent to it with properties.
 *
 * @param gameProperties : the TotallyNotAVector object to fill
 */
void GenerateRandProperties(TotallyNotAVector<Property*> * gameProperties){
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

/**
 * buyProperty: sets up everything for allowing a user to buy properties and ensures
 * they can acutally buy properties. Buying is done by passing values between the
 * TotallyNotAVector object for the game, and the TotallyNotAVector object for the user.
 *
 * @param randProperties : the random properties that are purchasable for this turn.
 * @param player : the player to pass properties to
 * @return int suggesting that the user may want to do more during this turn.
 */
int buyProperty(TotallyNotAVector<Property*> * randProperties, Player &player) {
    cout << "Possible properties to buy:" << endl;
    if(randProperties->length() == 0) {
        cout << "There are no more properties available for purchase right now." << endl;
        return 2;
    }
    for(int i = 0; i < randProperties->length(); i++){
        cout << "(" << i + 1 << ") " << randProperties->get(i)->toString() << endl;
    }
    cout << "Enter the number of the property you wish to purchase or type '0' to return" << endl;
    int selectedProperty = getUserInputAsInt(randProperties->length(),0) - 1;
    if(selectedProperty == -1)
        return 2;
    if(randProperties->get(selectedProperty)->getMortgage() > player.getBank()){
        cout << "The bank turns you down, you lack the funds to get tis property!" << endl;
    }else {
        player.getProperties()->append(randProperties->remove(selectedProperty));
    }
        return 2;
}

/**
 * checkForNotEnoughProperties: makes sure there are enough properties for this turn
 *
 * @param gameProperties : the properties to check
 */
void checkForNotEnoughProperties(TotallyNotAVector<Property*> * gameProperties){
    if(gameProperties->length() < 3){
        GenerateRandProperties(gameProperties);
    }
}

int sellProperty(Player &player){
    if(player.getProperties()->length() > 0){
        cout << "Which property do you wish to sell?" << endl;
        cout << "Owned Properties:" << endl;
        player.printPropertiesToSTDOut();
        int selection = getUserInputAsInt(player.getProperties()->length(), 0) - 1;
        if(selection == -1)
            return 2;
        double value = player.getProperties()->get(selection)->getValue();
        double remainingMortgage = player.getProperties()->get(selection)->getMortgageLeft();
        player.updateBank(attemptPropertySale(value, remainingMortgage));
        player.getProperties()->remove(selection);
    }else{
        cout << "You don't own any properties that you can sell right now." << endl;
    }
    return 2;
}

/**
 * attemptPropertySale: attempts to allow users to sell a property
 *
 * @param salePrice : the value of the property
 * @param remainingMortgage : the amount of mortgage left on the property
 * @return double: the amount the property sold for
 */
double attemptPropertySale(double salePrice, double remainingMortgage){
    cout << "How much do you want to sell this property for?" << endl;
    double askingPrice = getUserInputAsDouble(salePrice*1.25, 0);
    int chance = rand() % 3;
    double sale = 0;
    if(chance == 0){
        cout << "You got your asking price for the property!" << endl;
        sale = askingPrice - remainingMortgage;
    }else if(chance == 1){
        cout << "You got the value of the property back in its sale." << endl;
        sale = salePrice - remainingMortgage;
    }else{
        cout << "You could only manage to sell the property for 90% of it's price." << endl;
        sale = (salePrice * 0.90) - remainingMortgage;
    }
    return sale;
}

/**
 * changePropertyRent: changes a properties rent according to a user's input.
 *
 * @param player : the player object containing the user's properties (to change rent on)
 * @return and int suggesting the user may still want to do things on this turn.
 */
int changePropertyRent(Player &player){
    cout << "You have $" << player.getBank() << endl;
    cout << "Which property do you want to change your rent on? Type '0' to return." << endl;
    player.printPropertiesToSTDOut();
    int selection = getUserInputAsInt(player.getProperties()->length(), 0) - 1;
    if(selection == -1)
        return 2;
    player.getProperties()->get(selection)->changeRent();
    return 2;
}

/**
 * checkForRandom: randomly chooses if an area has a random occurence happen or not
 *
 * @param player : the properties to effect by random events
 */
void checkForRandom(Player &player){
    for(int i = 0; i < 3; i++) {
        if ((rand() % 100) <= 5) {
            string randomLocation = chooseRandomLocation();
            doRandomEvent(i, randomLocation, player);
        }
    }
}

/**
 * doRandomEvent: has a random event occur based on what was passed to it
 *
 * @param event : the event to occur
 * @param randomLocation : a string representing where the event is occuring
 * @param player : the properties to effect by random events
 */
void doRandomEvent(int event, const string& randomLocation, Player &player) {
    if(event == 0) {
        cout << "A disaster is occurring in the " << randomLocation << "!" << endl;
        disasterOccurs(randomLocation, player);
    }else if(event == 1) {
        cout << "The stock market has crashed!" << endl;
        stockMarketCrashes(player);
    }else{
        cout << "A big company moving into the " << randomLocation << "!" << endl;
        gentrificationOccurs(randomLocation, player);
    }
}

/**
 * disasterOccurs: has a disaster occur in a specific area based on what was passed to it
 *
 * @param location : the location to have the disaster occur at
 * @param player : the properties to effect by random events
 */
void disasterOccurs(string location, Player &player){
    for (int i = 0; i < player.getProperties()->length(); i++) {
        if (player.getProperties()->get(i)->getLocation() == location) {
            player.getProperties()->get(i)->reducePriceViaDisaster();
        }
    }
}

/**
 * stockMarketCrashes: has a stock market crash occur for all player properties
 *
 * @param player : the properties to effect by random events
 */
void stockMarketCrashes(Player &player){
    for (int i = 0; i < player.getProperties()->length(); i++) {
        player.getProperties()->get(i)->reducePriceViaSMC();
    }
}

/**
 * gentrificationOccurs: has gentrification occur in a random area on the players properties
 *
 * @param location : the location to change the values of the properties on
 * @param player : the properties to change the value of
 */
void gentrificationOccurs(string location, Player &player){
    for(int i = 0; i < player.getProperties()->length(); i++){
        if(player.getProperties()->get(i)->getLocation() == location){
            player.getProperties()->get(i)->increasePriceViaGentrification();
        }
    }
}

/**
 * chooseRandomLocation: chooses a random location to have a random event occur on.
 *
 * @return the location to have the random event occur in.
 */
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

/**
 * payMortgageAndGetRent: has all tenants in all player-owned properties pay rent and then
 * pay off the mortgage on those properties.
 *
 * @param player : the player in which to have tenants pay rent to and pay the mortgage on
 */
void payMortgageAndGetRent(Player &player){
    double rentTotal = 0;
    for(int i = 0; i < player.getProperties()->length(); i++){
        rentTotal += player.getProperties()->get(i)->haveAllTenantsPayRent();
    }
    double mortgageTotal = Property::findAndUpdateTotalMortgage(player.getProperties());
    double difference = rentTotal - mortgageTotal;
    cout << "Total amount made from rent: $" << rentTotal << endl;
    cout << "Total amount paid for mortgage: $" << mortgageTotal << endl;
    cout << "Difference: $" << difference << endl;
    player.updateBank(difference);
    cout << "Your bank is now at $" << player.getBank() << endl;
}

/**
 * payPropertyTax: finds the value of all properties and has the player pay 1.5% of that
 * amount.
 *
 * @param player the properties to pull the values from and the bank to pull that from
 */
void payPropertyTax(Player &player){
    double totalPropertyTax = Property::findTotalPropertyTax(player.getProperties(), player.getProperties()->length());
    cout << "A year has passed and you owe property tax on your properties!" << endl;
    cout << "You are charged: $" << totalPropertyTax << endl;
    player.updateBank(-totalPropertyTax);
}

/**
 * playerWinsOrLoses: returns true if the player wins or loses and prints a message telling
 * the player which one occured.
 *
 * @param player : the player to dictate if won or not
 * @return a boolean suggesting if the player won, lost, or neither
 */
bool playerWinsOrLoses(Player &player){
    if(player.getBank() >= 1000000){
        cout << "You broke $1000000, and you won!" << endl;
        return true;
    }else if(player.getBank() <= 0){
        cout << "You went bankrupt!" << endl;
        return true;
    }else{
        return false;
    }
}

/**
 * printALlInformationFromVectors: prints the information of the properties to std output
 * used in debugging and currently not implemented.
 *
 * @param gameProperties : the properties of the game
 * @param playerProperties : the properties of the player
 * @param randomProperties : random properties pulled from the game properties
 */
void printAllInformationFromVectors(TotallyNotAVector<Property*> * gameProperties,
                                    TotallyNotAVector<Property*> * playerProperties,
                                    TotallyNotAVector<Property*> * randomProperties){
    cout << endl << "Game properties:" << endl << endl;
    for(int i = 0; i < gameProperties->length(); i++){
        cout << i << ": " << gameProperties->get(i)->toString() << endl;
    }
    cout << endl << "Random properties:" << endl << endl;
    for(int i = 0; i < randomProperties->length(); i++){
        cout << i << ": " << randomProperties->get(i)->toString() << endl;
    }
    cout << endl << "Your properties:" << endl << endl;
    for(int i = 0; i < playerProperties->length(); i++){
        cout << i << ": " << playerProperties->get(i)->toString() << endl;
    }
}