#ifndef District_H
#define District_H

#include <iostream>
#include <string>
#include <array>
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
        int getVotesForParty(string name);
        void setVotesForForParty(string name, int votes);

        string* getPartiesNames();
        void printPartiesNames();
        void setPartiesNames(string names[], int namesLength);
        void writePartiesNames();

        int getArrayOFVoteLength();
        void setArrayOFVoteLength(int length);

        void printPercentages();
        void printWinner();  

    private:
        string districtName;
        string* name;
        int totalVoters; 
        int partiesCount;
        PartyVotes* votesForParties;
        int votesForPartiesLength;
        string* partiesNames;
        bool haveWinner;
    
};


#endif