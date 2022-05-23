//Given an entity (adam), randomly initialize a set of controller inputs.
//(Before seeding, the inputs may be invalid.)
//You may want to change this to start with a known-good flight path.
boolean slide_seed(population *pop, entity *adam){
    int frameIdx;
    for(frameIdx = 0; frameIdx < pop->len_chromosomes; frameIdx++){
        int nextValue;
        if(frameIdx < 100){
            nextValue = 0;
        }else{
            nextValue = random_int(2*72 + 1); //(0-144, inclusive)
            nextValue -= 72; //-72 to 72, inclusive.
        }
        int8_t controllerInput = (int8_t) nextValue;
        ((int8_t *)((entity_chrom *)adam ->chromosome[0])->controllerInputs)[frameIdx] = controllerInput;
    }
    //Now seed with known good inputs, if there are any. 
    pop_data *pd = ((pop_data *)pop->data);
    if(pd->goodControllerInputs != NULL){
        //If we've already seeded one input, no need to seed any more. 
        if(!pd->seededGood){
            pd->seededGood = true;
            char inBuf[10];
            int frameIdx = 0;
            while(fgets(inBuf, 9, pd->goodControllerInputs)){
                ((entity_chrom *) adam->chromosome[0])->controllerInputs[frameIdx] = 
                    (int8_t) atoi(inBuf);
                frameIdx++;
            }
        }
    }
    return true;
}

// TODO: Modify fitness function here

static boolean fitness(population *pop, entity *entity){
    entity->fitness = 1;
    return true;
}
#define STARTSLIDE_DURATION 240
//This is just a callback that's run at the end of each generation.         
bool slide_generation_hook(int generation, population *pop){
    entity *best;
    best = ga_get_entity_from_rank(pop, 0);
    fprintf(stderr, "Generation %d\r", generation);
    if(((pop_data *)pop->data)->lastScore != best->fitness){
        ((pop_data *)pop->data)->lastScore = best->fitness;

        int intReachFrame, intLandFrame, intCollideFrame;
        intCollideFrame = -1;
        printf("Generation %d, best fitness %f\n", generation, best->fitness);
        
	struct Player final;
        final = ((entity_chrom *)best->chromosome[0])
                ->results[STARTSLIDE_DURATION - 1].player;
        printf("\tdist_x: %f dist_z %f\n", distance_to_go_x(final),
            distance_to_go_z(final));
        FILE *outFile = ((pop_data *)pop->data)->outFile;
        fprintf(outFile, "%d,%f,%f,%f", generation, best->fitness,
                distance_to_go_x(final), distance_to_go_z(final));
        for(int i = 0; i <= (collide); i++){
            struct Player curPlayer = ((entity_chrom *)best->chromosome[0])->results[i].player;
            fprintf(outFile, ",%d,%f,%f,%f", 
                ((entity_chrom *)best->chromosome[0])->controllerInputs[i],
                curPlayer.position.x,
                curPlayer.position.z,
                curPlayer.baseSpeed);
        }
        fprintf(outFile, "\n");
    }
    return true;
}
