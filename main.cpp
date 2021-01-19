// main.cpp

/* Compile project with e.g.
 * 
 * g++ -Wall *.cpp -o aco
 * */

#include <iostream>
#include <ctime> 
#include "aco.h"



int main(){
    srand((unsigned)time(0)); 
    std::cout.precision(4);
    ACO aco = ACO(20, 50, 0.7, "distances.txt");
    //aco.printDistances();
    aco.printPheromons();
    aco.makeTurnsACO();
    //aco.printPheromons();
    return 0;
}
