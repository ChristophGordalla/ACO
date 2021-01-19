// ant.h
#include <vector>

#ifndef ANT_H
#define ANT_H



class Ant {
    uint16_t nLocations;
    uint16_t position;
    std::vector<uint16_t> positions;
    std::vector<bool> hasBeenVisited;
    
    public:
        /**
         * Default constructor. Needed in aco.cpp for ants.resize(..) 
         * to work properly.
         * */
        Ant() : nLocations(0) {};
        
        /**
         * Creates an Ant object with that will travel to nLocations locations.
         * 
         * @param nLocations:     number of locations to travel to
         * */
        Ant(uint16_t nLocations);
        
        /**
         * Returns the current position of the ant.
         * 
         * @return position:    current position of the ant
         * */
        const std::vector<uint16_t>& getPositions() { return positions; }; 
        
        /**
         * Makes the ant visit all locations.
         * 
         * @param pheromons:    pheromon map, Comes from the ACO object
         * */
        void makeTurnAnt(const std::vector<std::vector<double>> &pheromons);
    
    private:
        /**
         * Computes the next position that the ant can travel to.
         * 
         * @param pheromonsNextLoc:   pheromons on the paths 
         *                            to the next possible locations
         * */
        uint16_t getNextPosition(const std::vector<double> &pheromonsNextLoc);
        
        
        /**
         * Prints the positions of an ant (for debugging).
         * */
        void printPositions();
};

#endif /* ANT_H */

