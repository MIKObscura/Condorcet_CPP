
#ifndef CONDORCET_CANDIDATE_H
#define CONDORCET_CANDIDATE_H
#include "string"
#include <bits/stdc++.h>

class Candidate {
private:
    std::string m_sName;
    int m_iWins;
    int m_iBordaScore;
    std::vector<bool> m_vbDuels;
    std::vector<int> m_viRanks;
public:
    explicit Candidate(std::string &name);
    ~Candidate();
    void duelWith(Candidate &adversary);
    void setRanks(std::vector<int> &votes);
    void addRank(int vote);
    bool returnDuelResult(int index);
    void duelsWon();
    bool duelDone(int index);
    int getWins() const;
    int getBordaScore() const;
    void calculateBordaScore(int maxScore);
    std::string getName();
};


#endif //CONDORCET_CANDIDATE_H
