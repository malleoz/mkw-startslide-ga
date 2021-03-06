#include "plane_physics.h"
#include "run_simulation.h"
#include <stdlib.h>
#include <stdio.h>
/** Runs frameSim repeatedly, and once the startslide duration has elapsed,
stops the simulation.
Arguments:
stickPositions is an array (of length maxFrames) of the input stick positions at each frame. These will be fed into the frameSim function. 
Result *output is an array (of length maxFrames) into which the result of 
each frame of simulation will be inserted. 
startPoint is the initial player struct. This will be copied into the 
first element of output. (startPoint will not be modified by this code.)
*/
#define STARTSLIDE_DURATION 240
int runSimulation(int8_t *stickPositions,
                  struct Result * output, 
                  struct Player *startPoint){
    //Initialize the first frame of the output.
    output[0].landed = false;
    output[0].collidedInterference = false;
    output[0].landedInterference = false;
    output[0].reachedInterference = false;
    output[0].player = *startPoint;
    
    int curFrame;
    for(curFrame=1; curFrame < STARTSLIDE_DURATION; curFrame++){
        frameSim(stickPositions[curFrame], 
                 &(output[curFrame-1].player),
                 output + curFrame);
    }
    
    return 0;
}


