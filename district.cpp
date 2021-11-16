#include "district.h"
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;


int main(){
    
    vector<District> districts;
    int choice;
    string name;
    int totalVoters; 
    int partiesCount; 
    bool exit = false;

    do{
        printMenuOptions();
        cin >> choice;
        switch(choice){
            case 1: {
                cout << "Enter district Name: " <<endl;
                cin >> name;
                cout << "Enter the number of voters in the district: " <<endl;
                totalVoters = getValidNumber();
                cout << "Enter the number of parties in the district: " <<endl;
                partiesCount = getValidNumber();
                District d1(name, totalVoters, partiesCount);
                d1.writePartiesNames();
                d1.writeVotesForAllParties();
                d1.calculateWinner();
                districts.push_back(d1);
                // vector.erase( vector.begin() + 3 );
                break;
            };
            case 2: {
                printPercentagesInAllDistricts(&districts);
                break;
            };
            case 3: {
                printWinnersInAllDistricts(&districts);
                break;
            };
            case 4: {
                // printPercentagesInAllDistricts(&districts);
                break;
            };
            case 5: {
                saveDistrictsToFile(&districts);
                break;
            };
            case 6: {
                saveDistrictsWithNoWinnersToFile(&districts);
                break;
            };
            case 7: {
                readDistrictsFromFile();
                break;
            };
            case 8: {
                printMenuOptions();
                break;
            };
            case 0: {
                exit = true;
                break;  
            }
            default: break;
        }
    }while(!exit);   
    return 0;
}

// Constructors and destructor
// difference between the 2 constructocs is how the name value is passed
// (by value or by reference)
District::District(){}

District::District(string districtName, int totalVoters, int partiesCount){
    setName(&districtName);
    setDistrictName(districtName);
    setTotalVoters(totalVoters);
    setPartiesCount(partiesCount);
    setArrayOFVoteLength(0);

}

District::District(string* name, int totalVoters, int partiesCount){
    setName(name);
    setDistrictName(*name);
    setTotalVoters(totalVoters);
    setPartiesCount(partiesCount);
    setArrayOFVoteLength(0);
        PartyVotes* votesForParties;
        string* partiesNames;
}

District::~District(){
        // PartyVotes* votesForParties;
        // string* partiesNames;
        //delete[]votesForParties;
        this->votesForParties = NULL;
        //delete[]partiesNames;
        this->partiesNames = NULL;
}

// Getters and setters for name of the district
// again for how name is passed(by value or by reference)  
string District::getDistrictName(){
    return this->districtName;
}

void District::setDistrictName(string districtName){
    this->districtName = districtName;
}

string* District::getName(){
    return this->name;
}

void District::setName(string* name){
    this->name = name;
}

// Getters and setters for the number of people
// in the district, who can vote
int District::getTotalVoters(){
     return this->totalVoters;
}

void District::setTotalVoters(int voters){
    this->totalVoters = voters;
}

// Getters and setters for the number of parties
int District::getPartiesCount(){
    return this->partiesCount;
}

void District::setPartiesCount(int count){
    this->partiesCount = count;
}

// Getters and setters for the name of the winning party
string District::getWinnerName(){
    return this->winnerName;
}

void District::setWinnerName(string name){
    this->winnerName = name;
}

// Getters and setters for bool variable
// that shows it the district have winning party
bool District::getHaveWinner(){
    return this->haveWinner;
}

void District::setHaveWinner(bool haveWinner){
    this->haveWinner = haveWinner;
}

// Getters and setters for length of votes array
int District::getArrayOFVoteLength(){
    return votesForPartiesLength;
}

void District::setArrayOFVoteLength(int length = 0){
    this->votesForPartiesLength = length;
}

// Getter for the array, containing all votes and created from the struct PartyVotes, 
// used to map number of votes with name of one party
PartyVotes* District::getVotesForAllParties(){
    return this->votesForParties;
}

// Setter for the the array, containing all votes and created from the struct PartyVotes, 
// used to map number of votes with name of one party
void District::setVotesForAllParties(PartyVotes votes[], int votesLength){

    // check if Length of the array is bigger than number of parties
    // it can be smaller, if there are parties with no votes
    if(votesLength > this->partiesCount) {
        cout << "cannot have votes for more parties" << endl;
        return;
    }

    // this for loop check if all names of the parties are persent in
    // partiesNames[] array in this district
    for(int i = 0; i < votesLength; i++){
        bool match = false;
        string name = votes[i].partyName;
        int numberOfParties = this->partiesCount;
        string* partiesNames = this->partiesNames;
        
        for(int j = 0; j < numberOfParties; j++){
            if((partiesNames[j]) == name) match = true;
        }

        if(match == false) {
            cout << "no such party: " << name << endl;
            return;
        }
    }

    // if everything is ok, then initialize and set the array 
    this->votesForParties = new PartyVotes[votesLength];
    setArrayOFVoteLength(votesLength);

    for(int i = 0; i < votesLength; i++){
        this->votesForParties[i] = votes[i];
        cout << "party[" << i << "]: " << this->votesForParties[i].partyName << " have " << this->votesForParties[i].votes << endl;
    }
}

// Get number of votes for single party by given name
int District::getVotesForParty(string name){
    for(int i = 0; i < this->votesForPartiesLength; i++){
        if(this->votesForParties[i].partyName == name){
            cout << "party[" << i << "]: " << this->votesForParties[i].partyName << " have " << this->votesForParties[i].votes << endl;
            return this->votesForParties[i].votes;
        }
    }
    cout << "no such party: " << name << endl; 
    return 0;
}

// Set number of votes for single party by given name, and number of votes
void District::setVotesForForParty(string name, int votes){

    // check if the number of votes is valid
    // again, party can have 0 votes in theory
    if(votes < 0) return;

    // checking if the party with that name exists
     for(int i = 0; i < this->partiesCount; i++){
        bool match = false;
        string* partiesNames = this->partiesNames;
        
        for(int j = 0; j < this->partiesCount; j++){
            if((partiesNames[j]) == name) {
                match = true;
            }
        }

        if(match == false) {
            cout << "no such party: " << name << endl;
            return;
        }
    }

    // if there is party with given name, then set the votes
    for(int i = 0; i < this->votesForPartiesLength; i++){
        if(this->votesForParties[i].partyName == name){
            this->votesForParties[i].votes = votes;
            cout << "party[" << i << "]: " << this->votesForParties[i].partyName << " have " << this->votesForParties[i].votes << endl;
            return;
        }
    }
}

// Getter for all parties' names
string* District::getPartiesNames(){
    return this->partiesNames;
}

// Setter for all parties' names
void District::setPartiesNames(string names[], int namesLength){
    
    // Check if partiesCount is equal to the length of given names
    if(namesLength != this->partiesCount) {
        cout << "not equal" << endl;
        return;
    }

    // if everything is ok, then initialize and set the array 
    this->partiesNames = new string[namesLength];

    for(int i = 0; i < namesLength; i++){
        this->partiesNames[i] = names[i];
        cout << "partiesNames[" << i << "]: " << names[i] << " " << this->partiesNames[i] << endl;
    }
}

// function to print all parties' names
void District::printPartiesNames(){
    
    for(int i = 0; i < this->partiesCount; i++){
        cout << "Party " << i+1 << ": " << this->partiesNames[i] << endl;
  
    }
}

// function for manualy entering the names from the console 
void District::writePartiesNames(){

    // Check if partiesCount is valid
    if(this->partiesCount <= 0) return; 
    this->partiesNames = new string[this->partiesCount];
    string name;

    for(int i = 0; i < this->partiesCount; i++){
        cout << "Enter party "<< i+1 <<" name: " << endl;
        cin >> name;
        this->partiesNames[i] = name;
    }
    // print all names entered before finish
    this->printPartiesNames();
}

// function to save to file multiple District objects
void saveDistrictsToFile(vector<District>* districts){
    
    // Check it there are any districts
    if(districts.size() == 0) {
        cout << "Please enter districts first" << endl;
        return 0;
    }
    
    ofstream file;
    file.open("data.txt", ios::out);

    //check if file opened, then iterate through the objects and write to the file
    if(file.is_open()){
        for(vector<District>::iterator district = districts->begin(); district != districts->end(); ++district){
            // file.write((char*)&districts, sizeof(districts));
            file << "District: " << district->getDistrictName() << "\n";
            file << "Total voters: " << district->getTotalVoters() << "\n";
            file << "Number of parties: " << district->getPartiesCount() << "\n";
            
            string* partiesNames = district->getPartiesNames();
            for(int j = 0; j < district->getPartiesCount(); j++){
               
               if(j == district->getPartiesCount()-1){
                   file << partiesNames[j] << "\n";
               }
               else file << partiesNames[j] << ", "; 
            }

            file << district->getArrayOFVoteLength() << "\n";
            
            PartyVotes* votesArray = district->getVotesForAllParties();
            for(int k = 0; k < district->getArrayOFVoteLength(); k++){
                file << votesArray[k].partyName << " - " << votesArray[k].votes << endl; 
            }
            file << "\n";
        }
    } else cout << "Unable to open file" << endl;
    
    file.close();
    cout << "Data saved to file." << endl;
}

// function to print saved districts from file
void readDistrictsFromFile(){

	ifstream file;
	file.open("data.txt", ios::in);

    string line;

    //check if file opened, then print the objects from the file
    if(file.is_open()){
        while(getline(file, line)){
            cout << line << endl;
        }
    } else cout << "Unable to open file" << endl;
    
    file.close();
}

// prints the persentage of vote for each party in one district
void District::printPercentages(){
    int totalVoters = this->getTotalVoters();
    string* partiesNames = this->getPartiesNames(); 
    PartyVotes* votesArray = this->getVotesForAllParties();

    // loop through the names of the parties and check
    // if there are votes for each one
    bool voted = false;
    for(int i = 0; i < this->getPartiesCount(); i++){
        for(int j = 0; j < this->getArrayOFVoteLength(); j++){
            
            // if there are votes for the party calculate the parsenatage
            if(partiesNames[i] == votesArray[j].partyName && votesArray[j].votes > 0){
                voted = true;
                double p = ((double)votesArray[j].votes/totalVoters)*100;
                cout << "Party: " << partiesNames[i] << " have " << votesArray[j].votes << " votes = " << p << "%." << endl;
            }
        }

        // if there are no votes - print it, or reset voted variable
        if(voted == false){
            cout << "Party: " << partiesNames[i] << " have no votes - 0%." << endl;
        } else {
            voted = false;
        } 
    }
}

// function to calculate the winning party and 
// setHaveWinner and setWinnerName for the district
void District::calculateWinner(){
    int totalVoters = this->getTotalVoters();
    string* partiesNames = this->getPartiesNames(); 
    PartyVotes* votesArray = this->getVotesForAllParties();

    bool haveWinner = false; string winnerName;
    int highestVoteCount = -1;
    
    // loop through the names of the parties and check
    // if there are votes for each one, and get the party with most votes
    for(int i = 0; i < this->getPartiesCount(); i++){
        for(int j = 0; j < this->getArrayOFVoteLength(); j++){
            if(partiesNames[i] == votesArray[j].partyName){

                if(highestVoteCount <  votesArray[j].votes){
                    highestVoteCount = votesArray[j].votes;
                    winnerName = votesArray[j].partyName;
                    haveWinner = true;
                } else if(highestVoteCount == votesArray[j].votes) {
                    winnerName = winnerName + " tied " + votesArray[j].partyName;
                    haveWinner = false;
                }
            }
        }
    }

    setHaveWinner(haveWinner);
    setWinnerName(winnerName);
}

// function for manualy entering the votes for each party from the console 
void District::writeVotesForAllParties(){
    int totalVoters = this->getTotalVoters();
    string* partiesNames = this->getPartiesNames();
    int numberOfParties = this->getPartiesCount();
    PartyVotes* votesArray = new PartyVotes[numberOfParties];;
    int votes, sum = 0;

    for(int i = 0; i < numberOfParties; i++){
        cout << "Enter votes for party " << partiesNames[i] << ": " << endl;
        cin >> votes;

        // check if sum of the votes is bigger than number of voters in the district
        // and repeat until number is valid, and set the votes      
        sum += votes;
        if(sum > totalVoters || sum < 0 || votes < 0) {
            cout << "invalid number of votes" << endl;
            sum -= votes;
            i--;
        } else {
            votesArray[i] = { partiesNames[i], votes };
        }

    }
    this->setVotesForAllParties(votesArray, numberOfParties);

}

//helper function to check if string is alphabetically less than other
bool nameCompare(string a, string b){
	return a<b;
}

// function that outputs the persentage of vote for each party
// in multiple Districts
void printPercentagesInAllDistricts(vector<District>* districts){
	
    // Check it there are any districts
    if(districts.size() == 0) {
        cout << "Please enter districts first" << endl;
        return 0;
    }

    //used for sorting the names in alphabatical order
    vector<string> districtNames;
     for(vector<District>::iterator district = districts->begin(); district != districts->end(); ++district){
        districtNames.push_back(district->getDistrictName()); 
    }
	sort(districtNames.begin(), districtNames.end(), nameCompare);

    // loop through the sorted names and print percentages
    // for the district with the same name
    for(int i = 0; i < districtNames.size(); i++){
        for(vector<District>::iterator district = districts->begin(); district != districts->end(); ++district){
            if(districtNames[i] ==  district->getDistrictName()){
                cout << "District: " << districtNames[i] << endl;
                district->printPercentages();
            }
        }
    }
}

// function that prints the winning party in multiple Districts
void printWinnersInAllDistricts(vector<District>* districts){

    // Check it there are any districts
    if(districts.size() == 0) {
        cout << "Please enter districts first" << endl;
        return 0;
    }

    //used for sorting the names in alphabatical order
    vector<string> districtNames;
     for(vector<District>::iterator district = districts->begin(); district != districts->end(); ++district){
        districtNames.push_back(district->getDistrictName()); 
    }
	sort(districtNames.begin(), districtNames.end(), nameCompare);

    // loop through the sorted names and print the winner if there is one
    // for the district with the same name
    for(int i = 0; i < districtNames.size(); i++){
        for(vector<District>::iterator district = districts->begin(); district != districts->end(); ++district){
            if(districtNames[i] ==  district->getDistrictName()){
                cout << "In district: " << districtNames[i] << " ";
                if(district->getHaveWinner()){
                    cout << "the winner is: " << district->getWinnerName() << endl;
                } else {
                    cout << "there is no winner ( " << district->getWinnerName() <<" )." << endl;
                }
            }
        }
    }
}

// function to save to file multiple District objects
// that didn't have winning party
void saveDistrictsWithNoWinnersToFile(vector<District>* districts){

    // Check it there are any districts
    if(districts.size() == 0) {
        cout << "Please enter districts first" << endl;
        return 0;
    }

    ofstream file;
    file.open("withoutWinners.txt", ios::out);
    //check if file opened, then iterate through the objects and write to the file
    if(file.is_open()){
        for(vector<District>::iterator district = districts->begin(); district != districts->end(); ++district){
            if(!district->getHaveWinner()){
                file << "District: " << district->getDistrictName() << "\n";
                file << "Total voters: " << district->getTotalVoters() << "\n";
                
                PartyVotes* votesArray = district->getVotesForAllParties();
                int sumVotes = 0;

                for(int k = 0; k < district->getArrayOFVoteLength(); k++){
                    sumVotes += votesArray[k].votes; 
                }
                
                // calculate the persentage of people, who didn't voted
                double percent = ((double)sumVotes/district->getTotalVoters())*100;
                file << "Persentage of people, who didn't vote: " << percent << endl;
                file << "\n";
            }
        }
    }
    
    file.close();
    cout << "Data saved to file." << endl;
}

// prints the menu options for the loop in main function
void printMenuOptions(){
    cout << "***** Menu Options *****" << endl;
    cout << "1. Add new District." << endl;     
    cout << "2. Print parties' percentages." << endl;
    cout << "3. Print district winners." << endl;         
    cout << "4. Print districts with no winners." << endl;
    cout << "5. Save all districts to file." << endl;
    cout << "6. Save districts with no winners to file." << endl;
    cout << "7. Print districts from file." << endl;
    cout << "8. Print options." << endl;
    cout << "0. Exit." << endl;            
}

// helper function for limiting the user input to be only positive numbers
int getValidNumber(){
    int n;
    cin >> n;
    while ((cin.fail() || n <=0)){
        cin.clear();
        cin.ignore();
        cout << "Not a valid number. Please enter new: ";
        cin >> n;
    }
    return n;
}