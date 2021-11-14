#include "district.h"
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <cstdio>
// #include <conio>


using namespace std;

// #include <vector>
// #include <map>
// int main(int argc, char* argv[])
// {
//    std::vector<std::map<int,int>> vecOfMaps;
//    std::vector<std::map<int,int>*> vecOfMaps2;
//    return 0;
// }
// map <int, string> * myArray = new map<int, string>[10];

District::District(){
    cout << "empty" << endl;
}

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

int District::getTotalVoters(){
     return this->totalVoters;
}

void District::setTotalVoters(int voters){
    this->totalVoters = voters;
}

int District::getPartiesCount(){
    return this->partiesCount;
}

void District::setPartiesCount(int count){
    this->partiesCount = count;
}

string District::getWinnerName(){
    return this->winnerName;
}

void District::setWinnerName(string name){
    this->winnerName = name;
}

bool District::getHaveWinner(){
    return this->haveWinner;
}

void District::setHaveWinner(bool haveWinner){
    this->haveWinner = haveWinner;
}

int District::getArrayOFVoteLength(){
    return votesForPartiesLength;
}

void District::setArrayOFVoteLength(int length = 0){
    this->votesForPartiesLength = length;
}

PartyVotes* District::getVotesForAllParties(){
    return this->votesForParties;
}

void District::setVotesForAllParties(PartyVotes votes[], int votesLength){
    if(votesLength > this->partiesCount) {
        cout << "cannot have votes for more parties" << endl;
        return;
    }

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

    this->votesForParties = new PartyVotes[votesLength];
    setArrayOFVoteLength(votesLength);

    for(int i = 0; i < votesLength; i++){
        this->votesForParties[i] = votes[i];
        cout << "party[" << i << "]: " << this->votesForParties[i].partyName << " have " << this->votesForParties[i].votes << endl;
    }
}

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

void District::setVotesForForParty(string name, int votes){
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

    for(int i = 0; i < this->votesForPartiesLength; i++){
        if(this->votesForParties[i].partyName == name){
            this->votesForParties[i].votes = votes;
            cout << "party[" << i << "]: " << this->votesForParties[i].partyName << " have " << this->votesForParties[i].votes << endl;
            return;
        }
    }
}

string* District::getPartiesNames(){
    return this->partiesNames;
}

void District::setPartiesNames(string names[], int namesLength){
    
    if(namesLength != this->partiesCount) {
        cout << "not equal" << endl;
        return;
    }
    cout << "equal" << endl;
    this->partiesNames = new string[namesLength];

    for(int i = 0; i < namesLength; i++){
        this->partiesNames[i] = names[i];
        cout << "partiesNames[" << i << "]: " << names[i] << " " << this->partiesNames[i] << endl;
    }
}

void District::printPartiesNames(){
    
    for(int i = 0; i < this->partiesCount; i++){
        cout << "Party " << i+1 << ": " << this->partiesNames[i] << endl;
  
    }
}

void District::writePartiesNames(){
    if(this->partiesCount <= 0) return; 
    this->partiesNames = new string[this->partiesCount];
    string name;

    for(int i = 0; i < this->partiesCount; i++){
        cout << "Enter party "<< i+1 <<" name: " << endl;
        cin >> name;
        this->partiesNames[i] = name;
    }
    this->printPartiesNames();
}

void saveDistrictsToFile(vector<District>* districts){
    ofstream file;
    file.open("data.txt", ios::out);
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
    }
    
    file.close();
    cout << "Data saved to file." << endl;
    // ifstream file_obj;

    // file_obj.open("data.txt", ios::in);
    // District d1;
    // file_obj.read((char*)&d1, sizeof(d1));
    // cout << "Data" << endl;
    // cout << d1.getTotalVoters() << endl;

}

void readDistrictsFromFile(){
    ofstream file;
    file.open("data.txt", ios::out);

    // file.write((char*)&districts, sizeof(districts));
 
        // string districtName;
        // string* name;
        // int totalVoters; 
        // int partiesCount;
        // PartyVotes* votesForParties;
        // int votesForPartiesLength;
        // string* partiesNames;

    // ifstream file_obj;

    // file_obj.open("data.txt", ios::in);
    // District d1;
    // file_obj.read((char*)&d1, sizeof(d1));
    // cout << "Data" << endl;
    // cout << d1.getTotalVoters() << endl;

}

void District::printPercentages(){
    int totalVoters = this->getTotalVoters();
    string* partiesNames = this->getPartiesNames(); 
    PartyVotes* votesArray = this->getVotesForAllParties();

    bool voted = false;
    for(int i = 0; i < this->getPartiesCount(); i++){
        for(int j = 0; j < this->getArrayOFVoteLength(); j++){
            // cout << partiesNames[i] << " * " << votesArray[j].partyName << " * " << endl;
            if(partiesNames[i] == votesArray[j].partyName){
                voted = true;
                double p = ((double)votesArray[j].votes/totalVoters)*100;
                cout << "Party: " << partiesNames[i] << " have " << votesArray[j].votes << " votes = " << p << "%." << endl;
            }
        }

        if(voted == false){
            cout << "Party: " << partiesNames[i] << " have no votes - 0%." << endl;
        } else {
            voted = false;
        } 
    }
}

void District::calculateWinner(){
    int totalVoters = this->getTotalVoters();
    string* partiesNames = this->getPartiesNames(); 
    PartyVotes* votesArray = this->getVotesForAllParties();

    bool haveWinner = false; string winnerName;
    int highestVoteCount = -1;
    
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

void District::writeVotesForAllParties(){
    int totalVoters = this->getTotalVoters();
    string* partiesNames = this->getPartiesNames();
    int numberOfParties = this->getPartiesCount();
    PartyVotes* votesArray = new PartyVotes[numberOfParties];;
    int votes, sum = 0;

    for(int i = 0; i < numberOfParties; i++){
        cout << "Enter votes for party " << partiesNames[i] << ": " << endl;
        cin >> votes;

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

bool nameCompare(string a, string b){
	//returns 1 if string a is alphabetically less than string b
	return a<b;
}

void printPercentagesInAllDistricts(vector<District>* districts){
    vector<string> districtNames;
     for(vector<District>::iterator district = districts->begin(); district != districts->end(); ++district){
        districtNames.push_back(district->getDistrictName()); 
    }

	//mycomp function is the defined function which 
	//sorts the strings in alphabatical order
	sort(districtNames.begin(), districtNames.end(), nameCompare);

    
    for(int i = 0; i < districtNames.size(); i++){
        for(vector<District>::iterator district = districts->begin(); district != districts->end(); ++district){
            if(districtNames[i] ==  district->getDistrictName()){
                cout << "District: " << districtNames[i] << endl;
                district->printPercentages();
            }
        }
    }
}

void printWinnersInAllDistricts(vector<District>* districts){
    vector<string> districtNames;
     for(vector<District>::iterator district = districts->begin(); district != districts->end(); ++district){
        districtNames.push_back(district->getDistrictName()); 
    }
	sort(districtNames.begin(), districtNames.end(), nameCompare);

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

void saveDistrictsWithNoWinnersToFile(vector<District>* districts){

    ofstream file;
    file.open("withoutWinners.txt", ios::out);
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
                
                double percent = ((double)sumVotes/district->getTotalVoters())*100;
                file << "Persentage of people, who didn't vote: " << percent << endl;
                file << "\n";
            }
        }
    }
    
    file.close();
    cout << "Data saved to file." << endl;
}

void printMenuOptions(){
    cout << "1. Add new District." << endl;     
    cout << "2. Print parties' percentages." << endl;
    cout << "3. Print district winners." << endl;         
    cout << "4. Print districts with no winners." << endl;
    cout << "5. Save all districts to file." << endl;
    cout << "6. Save districts with no winners to file." << endl;
    cout << "7. Print options." << endl;
    cout << "0. Exit." << endl;            
}


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