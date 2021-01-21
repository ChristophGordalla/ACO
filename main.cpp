// main.cpp

/* Compile project with 'make all'.
 * Run project with './aco'.
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
