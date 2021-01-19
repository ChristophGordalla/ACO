// aco.cpp
#include <iostream>
#include <cstdlib> 
#include <cassert>
#include <fstream>
#include <limits>
#include "aco.h"



ACO::ACO(const uint32_t _nAnts, uint32_t _nTurns, const double vaporization, const std::string& filename) : nAnts(_nAnts), nTurns(_nTurns) { 
    setVaporization(vaporization);
    assert (isReadFile(filename)); 
    initPheromons();
    minimumPositions.resize(nLocations);
    minimumDistance = std::numeric_limits<int>::max();
    ants.resize(nAnts);
}


void ACO::makeTurnsACO(){
    for (uint32_t i=0; i<nTurns; ++i) {
        // TODO: write output to text file
        std::cout << "Turn: " << i << std::endl;
        makeTurnACO();
        std::cout << "The minimum distance is: " << minimumDistance;
        std::cout << std::endl;
        std::cout << "The positions are: " << std::endl;
        for (uint32_t i=0; i<nLocations; ++i) {
            std::cout << minimumPositions[i] << " ";
        }
        std::cout << std::endl;
        //printPheromons();
    }
}


void ACO::printDistances() {
    for (uint16_t i=0; i<nLocations; ++i) {
        for (uint16_t j=0; j<nLocations; ++j) {
            std::cout << distances[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}


void ACO::printPheromons() {
    for (uint16_t i=0; i<nLocations; ++i) {
        for (uint16_t j=0; j<nLocations; ++j) {
            std::cout << pheromons[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}


void ACO::setVaporization(const double& vaporization){
    if (vaporization > 0 && vaporization < 1) {
        this -> vaporization = vaporization;
    } else {
        this -> vaporization = 0.5;
        std::cout << "WARNING: Invalid vaporization value specified.";
        std::cout << std::endl;
        std::cout << "Vaporization must be between 0 and 1.";
        std::cout << "Using default value of 0.5." << std::endl;
    }
}


bool ACO::isReadFileSub(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line, temp;
        // first loop for only counting lines
        while (getline(file, line))    ++nLocations;
        distances.resize(nLocations); 
        for (uint16_t i=0; i<nLocations; ++i) {
            distances[i].resize(nLocations, 0);
        }
        // start from the beginning again
        file.clear();
        file.seekg (0, file.beg);
        
        uint16_t i=0, j=0, number;
        while (i<nLocations && !file.eof()) {
            file >> temp;
            try{
                number = stoi(temp);
                distances[i][j] = number; 
            } catch(std::exception& e) {
                number = 0;
            }
            ++j;
            if (j==nLocations){
                j = 0;
                ++i;
            }
        }
        file.close();
        for (uint16_t i=0; i<nLocations; ++i) {
            for (uint16_t j=0; j<nLocations; ++j) {
                if (distances[i][j] == 0 && i!=j) return false;
            }
        }
        return true;
    }
    return false;
}


bool ACO::isReadFile(const std::string& filename) {
    bool isReadSuccessfully = isReadFileSub(filename);
    if (!isReadSuccessfully) {
        std::cerr << "ERROR: File could not be read or contains invalid values.";
        std::cerr << filename << std::endl;
    }
    return isReadSuccessfully;  
}


void ACO::initPheromons() {
    pheromons.resize(nLocations); 
        for (uint16_t i=0; i<nLocations; ++i) {
            pheromons[i].resize(nLocations, -1);
        }
    for (uint16_t i=0; i<nLocations; ++i) {
        for (uint16_t j=0; j<nLocations; ++j) {
            if (i == j) {
                pheromons[i][j] = 0.;
            } else {
                // TODO: better define what is 'small'
                pheromons[i][j] = 0.001;
            }
        }
    }
}


void ACO::updatePheromonsAnt(const std::vector<uint16_t>& positions) {
    uint32_t totalDistance = 0;
    for (uint16_t i=1; i<nLocations; ++i) {
        uint16_t pos_now = positions[i];
        uint16_t pos_prev = positions[i-1];
        totalDistance += distances[pos_now][pos_prev]; 
    }
    totalDistance += distances[nLocations-1][0];
    for (uint16_t i=1; i<nLocations; ++i) {
        uint16_t pos_now = positions[i];
        uint16_t pos_prev = positions[i-1];
        pheromons[pos_now][pos_prev] += 1./totalDistance; 
        pheromons[pos_prev][pos_now] += 1./totalDistance; 
    }
    if (totalDistance < minimumDistance) {
        minimumDistance = totalDistance;
        minimumPositions = positions; 
    }
}


void ACO::updatePheromonsVaporization() {
    for (uint16_t i=0; i<nLocations; ++i) {
        for (uint16_t j=0; j<nLocations; ++j) {
            pheromons[i][j] *= 1 - vaporization;
        }
    }
}


void ACO::makeTurnACO() {
    // create fresh ants
    for (uint32_t i=0; i<nAnts; ++i) {
        ants[i] = Ant(nLocations);
    }
    for (uint32_t i=0; i<nAnts; ++i) {
        ants[i].makeTurnAnt(pheromons);
        //ants[i].printPositions();
    }
    updatePheromonsVaporization();
    for (uint32_t i=0; i<nAnts; ++i) {
        updatePheromonsAnt(ants[i].getPositions());
    }
}
