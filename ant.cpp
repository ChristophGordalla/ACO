// ant.cpp
#include <iostream>
#include <cstdlib> 
#include "ant.h"


Ant::Ant(uint16_t _nLocations) : nLocations(_nLocations) {
    hasBeenVisited.resize(nLocations, false);
    positions.resize(nLocations);
    // set ant to a random position
    position = (rand()%nLocations); 
    // the following line is not included into the code 
    // so that the ant will make a closed turn
    //hasBeenVisited[position] = true;
    positions[0] = position;
}


void Ant::makeTurnAnt(const std::vector<std::vector<double>> &pheromons) {
    std::vector<double> pheromonsNextLoc;
    pheromonsNextLoc.resize(nLocations, -1);
    uint16_t posNext;
    for (uint16_t i=0; i<nLocations; ++i) {
        pheromonsNextLoc = pheromons[position];
        posNext = getNextPosition(pheromonsNextLoc);
        hasBeenVisited[posNext] = true;
        position = posNext;
        positions[i] = position;
    }
}


uint16_t Ant::getNextPosition(const std::vector<double> &pheromonsNextLoc) {
    uint16_t Npossible = 0, count = 0, pos;
    double sumProb = 0., sumRand = 0., myRand;
    std::vector<double> probabilities;
    
    // only take the probabilities of those places into account 
    // that have not yet been visited
    for (uint16_t i=0; i<nLocations; ++i) {
        if (!hasBeenVisited[i]) {
            Npossible++;
        }
    }
    probabilities.resize(Npossible, 0.0);
    for (uint16_t i=0; i<nLocations; ++i) {
        if (!hasBeenVisited[i]) {
            probabilities[count] = pheromonsNextLoc[i];
            sumProb += probabilities[count];
            count++;
        }
    }
    myRand = (double) rand()/RAND_MAX*sumProb;
    pos = 0;
    for (uint16_t i=0; i<nLocations; ++i) {
        if (i == position || hasBeenVisited[i])    continue;
        sumRand += probabilities[pos];
        if (myRand < sumRand){
            pos = i;
            break;
        }
        pos++;
    }
    return pos;
}


void Ant::printPositions() {
    for (uint16_t i=0; i<nLocations; ++i) {
        std::cout << positions[i] << " ";
    }
    std::cout << std::endl;
}

