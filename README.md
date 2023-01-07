This project is a simulation of a Condorcet voting system written in C++.
# What is it?
The way it works is that the voters classify the different candidates starting with the one they prefer the most to the one they prefer the least\
Afterwards, the results are evaluated with each possible duel between the candidates\
If a candidate is classed higher than another in a vote, they win against said other candidate in that vote, the one who wins the most votes wins the duel\
For example:\
We have candidates A, B and C\
We have 3 voters\
Voter 1 votes A < B < C\
Voter 2 C < A < B\
Voter 3 B < C < A\
For the duel between A and B, A wins the duel in vote 3 and B wins in votes 1 and 2 -> B wins their duel with A\
Then for the duel between A and C, A wins in vote 2 and C wins in votes 1 and 3 -> C wins their duel with A\
Then for the duel between B and C, C wins in votes 1 and 3 and B wins in vote 2 -> C wins their duel with B\
A wins 0 duels, B wins 1 duel and C wins 2 duels -> C is the winner of the vote\
In some cases, candidates may end up with the same score, this is called a Condorcet Paradox\
There are multiple ways to solve it. The simplest one is called "Randomized Condorcet Method"
and simply randomly picks one between those that were ex aequo\
Here will be implemented the Black's Method\
This method mixes Borda method with Condorcet method\
The Borda method is a voting system where voters classify the candidates based on their preference\
Then each candidate receives a certain amount of point based on their place in each vote\
The winner of a Borda vote is the one with the highest score\
Black's method consists of using Condorcet method but if some are ex aequo, the winner is the one with the highest Borda score\
You can find more information about it here: https://en.wikipedia.org/wiki/Condorcet_method

Example files are included to show what format the program accepts\
By default the program assumes those are .txt files, so you don't need to specify the extension if that's the case\
The program only works when executed through the terminal for some reasons, the exe doesn't work when launched directly\
You first need to input a text file that is a list of candidate then put some vote files\
You can input multiple ones by separating their name with commas like this "vote1,vote2"\