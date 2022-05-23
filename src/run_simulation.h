#ifndef RUN_SIMULATION_H
#define RUN_SIMULATION_H

#include "plane_physics.h"

/** Runs frameSim repeatedly, and once the startslide duration has elapsed,
stops the simulation.
Arguments:
stickPositions is an array (of length maxFrames) of the input stick positions at
    each frame. These will be fed into the frameSim function. 
Result *output is an array (of length maxFrames) into which the result of 
    each frame of simulation will be inserted. 
startPoint is the initial player struct. This will be copied into the 
    first element of output. (startPoint will not be modified by this code.)
*/
int runSimulation(int8_t *stickPositions,
                  struct Result * output, 
                  struct Player *startPoint, 
                  int maxFrames);


#endif
