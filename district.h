#ifndef District_H
#define District_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
using namespace std;


struct PartyVotes{
    string partyName;
    int votes;
};

class District {
    public: 
        District();
        District(string districtName, int totalVoters, int partiesCount);
        District(string* name, int totalVoters, int partiesCount);
        ~District();

        string getDistrictName();
        void setDistrictName(string districtName);

        string* getName();
        void setName(string* name);

        int getTotalVoters();
        void setTotalVoters(int voters);

        int getPartiesCount();
        void setPartiesCount(int count);
        
        PartyVotes* getVotesForAllParties();
        void setVotesForAllParties(PartyVotes votes[], int votesLength);
        void writeVotesForAllParties();
        int getVotesForParty(string name);
        void setVotesForForParty(string name, int votes);

        string* getPartiesNames();
        void printPartiesNames();
        void setPartiesNames(string names[], int namesLength);
        void writePartiesNames();

        int getArrayOFVoteLength();
        void setArrayOFVoteLength(int length);

        void printPercentages();
        void calculateWinner();

        string getWinnerName();
        void setWinnerName(string name);  

        bool getHaveWinner();
        void setHaveWinner(bool haveWinner);

    private:
        string districtName;
        string* name;
        int totalVoters; 
        int partiesCount;
        PartyVotes* votesForParties;
        int votesForPartiesLength;
        string* partiesNames;
        bool haveWinner;
        string winnerName;
};

int getValidNumber(){
    int n;
    cin >> n;
    while ((cin.fail() || n <=0)){
        cin.clear();
        cin.ignore();
        cout << "Not a valid number. Please reenter: ";
        cin >> n;
    }
    return n;
}

void saveDistrictsToFile(vector<District>*  districts);
void readDistrictsFromFile();
void printPercentagesInAllDistricts(vector<District>* districts);
void printWinnersInAllDistricts(vector<District>* districts);
void saveDistrictsWithNoWinnersToFile(vector<District>* districts);
bool nameCompare(string a, string b);
void printMenuOptions();

#endif