/*
 * This program simulates a Condorcet voting system based on files given via user inputs
 * But what is Condorcet voting system you may ask?
 * The way it works is that the voters classify the different candidates starting with the one they prefer the most to the one they prefer the least
 * Afterwards, the results are evaluated with each possible duel between the candidates
 * If a candidate is classed higher than another in a vote, they win against said other candidate in that vote, the one who wins the most votes wins the duel
 * For example:
 * We have candidates A, B and C
 * We have 3 voters
 * Voter 1 votes A < B < C
 * Voter 2 C < A < B
 * Voter 3 B < C < A
 * For the duel between A and B, A wins the duel in vote 3 and B wins in votes 1 and 2 -> B wins their duel with A
 * Then for the duel between A and C, A wins in vote 2 and C wins in votes 1 and 3 -> C wins their duel with A
 * Then for the duel between B and C, C wins in votes 1 and 3 and B wins in vote 2 -> C wins their duel with B
 * A wins 0 duels, B wins 1 duel and C wins 2 duels -> C is the winner of the vote
 * In some cases, candidates may end up with the same score, this is called a Condorcet Paradox
 * There are multiple ways to solve it. The simplest one is called "Randomized Condorcet Method"
 * and simply randomly picks one between those that were ex aequo
 * Here will be implemented the Black's Method
 * This method mixes Borda method with Condorcet method
 * The Borda method is a voting system where voters classify the candidates based on their preference
 * Then each candidate receives a certain amount of point based on their place in each vote
 * The winner of a Borda vote is the one with the highest score
 * Black's method consists of using Condorcet method but if some are ex aequo, the winner is the one with the highest Borda score
 * You can find more information about it here: https://en.wikipedia.org/wiki/Condorcet_method
 */
#include <iostream>
#include <random>
#include <string>
#include "Candidate.h"

/*
 * Purpose: break a string with a given delimiter
 * @param str: string to break
 * @param delim: delimiter to break the string
 * @return: a vector containing the different substrings/tokens
 */
std::vector<std::string> tokenize(const std::string& str, const char delim){
    std::vector<std::string> tokens;

    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        tokens.push_back(token);
    }

    return tokens;
}

int randNum(int min, int max){
    std::random_device seed;
    std::mt19937 gen{seed()};
    std::uniform_int_distribution<> dist{min, max};
    int num = dist(gen);
    return num;
}

/*void printVec(std::vector<int> &vec){
    for(int i = 0; i < vec.size();i++){
        std::cout << vec[i] << std::endl;
    }
}*/

/*
 * Purpose: compares all the different candidates
 * @param candidates: vector containing all the different Candidate objects
 */
void compareAll(std::vector<Candidate> &candidates){
    for(int i = 0; i < candidates.size(); i++){
        for(int i2 = 0; i2 < candidates.size(); i2++){
            if(i2 == i) continue;
            if(candidates[i].duelDone(i2) || candidates[i2].duelDone(i)) continue;
            candidates[i].duelWith(candidates[i2]);
        }
    }
}

/*
 * Purpose: converts a given file to a string
 * @param fileName: name of the file to convert
 * @return: file converted to a std::string
 */
std::string fileToStr(std::string &fileName){
    std::string fileStr,tmp;
    std::fstream file;
    file.open(fileName, std::ios::in);
    if(!file){
        std::cout << "Error: file doesn't exist" << std::endl;
        return "Error";
    }
    std::cout << "File opened successfully" << std::endl;
    while(std::getline(file,tmp)){
        fileStr += tmp + '\n';
    }
    file.close();
    return fileStr;
}

/*
 * Purpose: returns the index of a given element in a vector
 * @param v: vector
 * @param K: element to find in said vector
 * @return: index of the element, -1 if the element wasn't found
 */
int getIndex(std::vector<std::string> v, std::string &K)
{
    auto it = find(v.begin(), v.end(), K);
    if (it != v.end())
    {
        int index = it - v.begin();
        return index;
    }
    else {
        return -1;
    }
}

/*
 * Purpose: validate a vote that was given
 * @param candidatesList: vector of Candidate objects used as reference
 * @param vote: vector of string to compare with
 * @return: true if both vectors have the same size and elements, false if not
 */
bool validateVote(std::vector<Candidate> &candidatesList, std::vector<std::string> &vote){
    if(vote.size() != candidatesList.size()) return false;
    for (auto & i : candidatesList) {
        if (std::find(vote.begin(), vote.end(), i.getName()) == vote.end()) {
            return false;
        }
    }
    return true;
}

/*
 * Purpose: add a vote to candidates
 * @param file: vote file converted to a string
 * @param candidatesList: vector of Candidate objects to put the vote in
 */
void addVote(std::string &file, std::vector<Candidate> &candidatesList){
    std::vector<std::string> vote = tokenize(file,'\n');
    if(!validateVote(candidatesList,vote)){
        std::cout << "Invalid vote" << std::endl;
        return;
    }
    for(auto & i : candidatesList){
        std::string name = i.getName();
        int index = getIndex(vote,name) + 1;
        i.addRank(index);
    }
}

/*
 * Purpose: take user's input to register votes
 * @param candidatesList: vector of Candidate objects used for adding votes
 */
void registerVotes(std::vector<Candidate> &candidatesList){
    std::cout << "Add a vote, type stop to exit:" << std::endl;
    while(true){
        std::string input,fileName;
        std::cin >> input;
        if(input == "stop") break;
        if(input.find(',',0) != -1){
            std::vector<std::string> files = tokenize(input,',');
            for(auto & fileStr : files){
                if(fileStr.find('.',0) == -1) fileStr += ".txt";
                std::string fileInput = fileToStr(fileStr);
                addVote(fileInput,candidatesList);
            }
            continue;
        }
        if(input.find('.',0) == -1) input += ".txt";
        fileName = fileToStr(input);
        if(fileName == "Error") continue;
        addVote(fileName,candidatesList);
    }
}

/*
 * Purpose: count how many candidates are ex-aequo
 * @param candidateList: vector of Candidate object
 * @return: number of winner-1, 0 if only one winner
 */
int numberOfExAequo(std::vector<Candidate> &candidateList){
    int counter = 0;
    int winningNum = candidateList[0].getWins();
    for(int i = 1; i < candidateList.size(); i++){
        if(candidateList[i].getWins() == winningNum){
            counter++;
        }
    }
    return counter;
}

/*
 * Purpose: function to sort an array of Candidate object based on the amount of duels won
 */
bool compareFuncCond(const Candidate& i, const Candidate& j){
    return i.getWins() > j.getWins();
}

/*
 * Purpose: function to sort an array of Candidate object based on their Borda score
 */
bool compareFuncBorda(const Candidate& a, const Candidate& b){
    return a.getBordaScore() > b.getBordaScore();
}

/*
 * Purpose: picks a winner, if multiple candidates have the same score, randomly pick one between them
 * @param candidatesList: vector of Candidate objects
 * @return Candidate who won the vote
 */
Candidate pickWinner(std::vector<Candidate> &candidatesList){
    sort(candidatesList.begin(),candidatesList.end(), compareFuncCond);
    int winners = numberOfExAequo(candidatesList);
    if(!winners) return candidatesList[0];
    std::vector<Candidate> winnersList(candidatesList.begin(), candidatesList.begin() + (winners + 1));
    for(auto & i : winnersList){
        i.calculateBordaScore((int)candidatesList.size());
        //std::cout << i.getName() << " " << i.getBordaScore() << std::endl;
    }
    sort(winnersList.begin(), winnersList.end(), compareFuncBorda);
    return winnersList[0];
}

/*
 * Example files are included to show what format the program accepts
 * By default the program assumes those are .txt files, so you don't need to specify the extension if that's the case
 * The program only works when executed through the terminal for some reasons, the exe doesn't work when launched directly
 * You first need to input a text file that is a list of candidate then put some vote files
 * You can input multiple ones by separating their name with commas like this "vote1,vote2"
 */
int main() {
    std::cout << "Input a file:" << std::endl;
    std::string input_file;
    std::cin >> input_file;
    if(input_file.find('.',0) == -1) input_file += ".txt";
    if(input_file == "Error") return 0;
    const std::string candidates_list = fileToStr(input_file);
    if(candidates_list == "Error") return 0;
    std::vector<std::string> tokens = tokenize(candidates_list,'\n');
    std::vector<Candidate> candidates;
    candidates.reserve(tokens.size());
    for(auto & token : tokens){
        candidates.emplace_back(Candidate(token));
    }
    registerVotes(candidates);
    compareAll(candidates);
    for(auto & candidate : candidates){
        candidate.duelsWon();
        std::cout << "Candidate " << candidate.getName() << ": " <<  candidate.getWins() << std::endl;
    }
    auto winner = pickWinner(candidates);
    std::cout << "The winner of the vote is: " << winner.getName() << std::endl;
    return 0;
}


