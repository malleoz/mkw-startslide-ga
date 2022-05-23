#ifndef RUN_GA_H
#define RUN_GA_H

#include <stdio.h>

/*
The main method used for optimizing startslides. 
Arguments: 
playerDat : a file pointer to a player.dat file which simply stores info about the character/vehicle combination used. 
goodControllerInputs: A file pointer to a set of inputs that should be used to seed the algorithm. This file should have three comma-separated integers per line. This represents A, stick, and D-Pad. The file should contain 240 rows. If this is NONE, then all startslides will be randomly seeded. 
outputFile: A file pointer to where the startslide logs will be written. This should of course have been opened for writing. 

popSize: The number of individuals in the population that will be evolved. Fewer individuals means faster generations but slower convergence. I find a happy value to be around 3,000. 
numGenerations: How long should the GA chew on the problem? You typically want a large number here, on the order of 100,000 generations. 
Returns: EXIT_SUCCESS on successful optimization. 
*/
int run_ga (FILE *playerDat, FILE *goodControllerInputs, 
        FILE *outputFile, int popSize, int numGenerations);

#endif
