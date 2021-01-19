// aco.h
#include "ant.h"
#include <vector>

#ifndef ACO_H
#define ACO_H



class ACO {
    uint16_t nLocations = 0; 
    uint32_t nAnts, nTurns, minimumDistance; 
    double vaporization;
    std::vector<uint16_t> minimumPositions; 
    std::vector<std::vector<uint32_t>> distances; 
    std::vector<std::vector<double>> pheromons; 
    std::vector<Ant> ants;
        
    public:
        /**
         * @param nAnts:        number of ants in the colony
         * @param nTurns:       number of complete turns to all locations
         * @param vaporization: vaporization constant 
         *                      (must be between 0 and 1)
         * @param filename:     name of the file to read from
         * */
        ACO(const uint32_t _nAnts, const uint32_t _nTurns, const double vaporization, const std::string &filename); 
    
        /**
         * Makes all turns.
         * */
        void makeTurnsACO();
        
        /**
         * Print distances (for debugging).
         * */
        void printDistances();
        
        /**
         * Print pheromons.
         * */
        void printPheromons();
    
    private:
        /**
         * Set vaporization. If the given value is not between
         * 0 and 1, the default value of 0.5 is set.
         * 
         * @param vaporization:    vaporization to be set
         * */
        void setVaporization(const double &vaporization);
        
        /**
         * Sub method of ACO::isReadFile(const std::string& filename)
         * from below.
         * 
         * @param filename:    filename of file with distances
         * @return             true if read-in has been successfull, 
         *                     false otherwise
         * */
        bool isReadFileSub(const std::string& filename);
        
        /**
         * Read file with distances. The file must not contain any header.
         * Distances must be stored as integers.
         * 
         * @param filename:    filename of file with distances
         * @return            true if read-in has been successfull, 
         *                     false otherwise
         * */
        bool isReadFile(const std::string &filename);
        
        /**
         * Initialize the pheromon map. Set the pheromons to 0 
         * diagonal values of the matrix and to a small (but non-zero) 
         * value otherwise (for zero pheromons everywhere, 
         * probability calculation will later run into problems).
         * */
        void initPheromons();
        
        /**
         * Looks at the positions from an ant and performs the 
         * following operations:
         * - Calculates the total distance that it took the ant 
         *   to visit all locations.
         * - Updates the pheromon map by the contribution 
         *   that every ant added to the map.
         * - Compares the distance travelled by the ant to the 
         *   current minimum distance and updates the minimum distance 
         *   and the minimum positions if the a new minumum
         *   has been found.
         * 
         * @param positions:    positions that an ant has travelled to
         *                      (comes from the corresponding ant object).
         * */
        void updatePheromonsAnt(const std::vector<uint16_t> &positions);
        
        /**
         * Updates the pheromon map after vaporization.
         * */
        void updatePheromonsVaporization();
        
        /**
         * Makes a turn of all ants where each ant visits all locations.
         * */
        void makeTurnACO();
};

#endif /* ACO_H */
