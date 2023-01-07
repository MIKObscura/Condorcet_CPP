
#include "Candidate.h"
//constructor
Candidate::Candidate(std::string &name) {
    m_sName = name;
}

//destructor
Candidate::~Candidate() = default;

/*
 * Purpose: sets the result of a duel between 2 candidates
 * @param adversary: candidate to compete with
 */
void Candidate::duelWith(Candidate &adversary) {
    int scoreSelf = 0, scoreAdv = 0;
    for(int i = 0;i < m_viRanks.size();i++){
        if(adversary.m_viRanks[i] > m_viRanks[i]){
            scoreSelf++;
        }
        else if(adversary.m_viRanks[i] == m_viRanks[i]) continue;
        else{
            scoreAdv++;
        }
    }
    m_vbDuels.push_back(scoreSelf > scoreAdv);
    adversary.m_vbDuels.push_back(scoreAdv > scoreSelf);
}

/*
 * Purpose: assign a vector to the rank value, was mostly used during testing and isn't used anymore
 * @param votes: vector containing the votes to add
 */
void Candidate::setRanks(std::vector<int> &votes){
    m_viRanks = votes;
}

/*
 * Purpose: adds a vote to the ranks list
 * @param vote: number to add
 */
void Candidate::addRank(int vote) {
    m_viRanks.push_back(vote);
}

/*
 * Purpose: calculate the amount of duels won
 */
void Candidate::duelsWon() {
    int wins = 0;
    for(auto && m_vbDuel : m_vbDuels){
        if(m_vbDuel){
            wins++;
        }
    }
    m_iWins = wins; //this is done because the duel with itself is also evaluated and is always true so doing -1 gives the exact result
}

/*
 * Purpose: returns the result of a duel
 * @param index: index of the duel in the m_vbDuels attribute
 */
bool Candidate::returnDuelResult(int index) {
    return m_vbDuels[index];
}

/*
 * Purpose: check if a duel was already done
 * @param index: index in the m_vbDuels attribute to check
 * @return: true if the duel was already done, false if not
 */
bool Candidate::duelDone(int index) {
    try
    {
        return m_vbDuels.at(index) == 0 || m_vbDuels.at(index) == 1;
    }
    catch (const std::out_of_range& oor) {
        return false;
    }
}

/*
 * Purpose: return the name of the candidate
 */
std::string Candidate::getName() {
    return m_sName;
}

/*
 * Purpose: return the number of duels won by the candidate
 */
int Candidate::getWins() const {
    return m_iWins;
}

/*
 * Purpose: return the Borda score of the candidate
 */
int Candidate::getBordaScore() const{
    return m_iBordaScore;
}

/*
 * Purpose: calculate this candidate's Borda score
 * @param: amount of candidates which represents the max score
 */
void Candidate::calculateBordaScore(int maxScore) {
    int score = 0;
    auto size = m_viRanks.size();
    for(int i = 0; i < size; i++){
        score += maxScore - (m_viRanks[i] - 1);
    }
    m_iBordaScore = score;
}