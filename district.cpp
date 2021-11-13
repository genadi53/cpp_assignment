#include "district.h"
#include <iostream>
#include <fstream>
#include <string>
#include <array>

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
        cout << "Party name[" << i << "]: " << this->partiesNames[i] << endl;
  
    }
}

void District::writePartiesNames(){
    if(this->partiesCount <= 0) return; 
    this->partiesNames = new string[this->partiesCount];
    string name;

    for(int i = 0; i < this->partiesCount; i++){
        cout << "Enter party name: " << endl;
        cin >> name;
        this->partiesNames[i] = name;
    }
    this->printPartiesNames();
}

void saveDistrictsToFile(District districts[], int count){
    ofstream file;
    file.open("data.txt", ios::out);
 // string districtName;
        // string* name;
        // int totalVoters; 
        // int partiesCount;
        // PartyVotes* votesForParties;
        // int votesForPartiesLength;
        // string* partiesNames;
    if(file.is_open()){
        for(int i = 0; i < count; i++){
            // file.write((char*)&districts, sizeof(districts));
            file << districts[i].getDistrictName() << "\n";
            file << districts[i].getTotalVoters() << "\n";
            file << districts[i].getPartiesCount() << "\n";
            
            string* partiesNames = districts[i].getPartiesNames();
            for(int j = 0; j < districts[i].getPartiesCount(); j++){
               
               if(j == districts[i].getPartiesCount()-1){
                   file << partiesNames[j] << "\n";
               }
               else file << partiesNames[j] << ", "; 
            }

            file << districts[i].getArrayOFVoteLength() << "\n";
            
            PartyVotes* votesArray = districts[i].getVotesForAllParties();
            for(int k; k < districts[i].getArrayOFVoteLength(); k++){
                file << votesArray[k].partyName << " - " << votesArray[k].votes << endl; 
            }
        }
    }

  
 
       

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


int main(){
 
    string name;
    string * mypointer;
    mypointer = &name;
    *mypointer = "d123";

    District *d2;
    d2 = new District("name", 100, 5);
    string names[] = {"qwertyui", "p1", "pqww", "qwertr", "new"};
    District d1(mypointer, 100, sizeof(names)/sizeof(names[0]));

    // cout << "d1: "<< *d1.getName() << endl;
    // cout << "d2: "<< d2->getDistrictName() << endl;
    // cout << "d1: "<< d1.getDistrictName() << endl;
    // cout << "d2: "<< *d2->getName() << endl;

    // cout << "d1: "<< d1.getTotalVoters() << endl;
    // cout << "d2: "<< d2->getTotalVoters() << endl;

    // cout << "d1: "<< d1.getPartiesCount() << endl;
    // cout << "d2: "<< d2->getPartiesCount() << endl;

    // cout << "* " << sizeof(names)/sizeof(names[0]) << endl;

    d1.setPartiesNames(names, sizeof(names)/sizeof(names[0]));
    // // d2->writePartiesNames();
    d1.printPartiesNames();

    PartyVotes* arr = new PartyVotes[2];
    arr[0] = {"p1", 2};
    arr[1] = {"qwertyui", 3};
    // cout << arr[0].votes << endl;
    d1.setVotesForAllParties(arr, 2);

    // PartyVotes* votes = d1.getVotesForAllParties();
    // for(int i=0; i < 2; i++){
    //     cout << votes[i].partyName << " " << votes[i].votes << endl;
    // }

    // d1.setVotesForForParty("qwertyui", 5);
    // cout << d1.getVotesForParty("qwertyui") << endl;

    // // string* getnames = d1.getPartiesNames();
    // //     // *(getnames+i) << endl;
    // // for(int i = 0; i < d1.getPartiesCount(); i++){
    // //     cout << "p[" << i << "]: " << getnames[i]  <<endl;
    // // }
    District districts[1];
    districts[0] = d1;
    saveDistrictsToFile(districts, 1);


    return 0;
}