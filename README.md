# ACO

This program uses an ant colony optimization (ACO) algorithm to solve the traveling salesman problem. 
For the algorithm of the edge selection ( https://en.wikipedia.org/wiki/Ant_colony_optimization_algorithms#Edge_selection ), the simplest approach is used with the following equation for deriving the probabilities p_ij for a path from i to j from the pheromon concentrations tau_ij on that path:

p_ij = tau_ij / sum_allowed_ij tau_ij .

## Compilation and Execution

Copy all files to the same folder. Then compile and execute project with:

```
make all
./aco
```

## Included files:

* main.cpp:       Contains main method.
* aco.cpp/h:      Contains ACO class.
* ant.cpp/h:      Contains ant class.
* distances.txt:  Example file with distance matrix.
* makefile:       Makefile to build project.
