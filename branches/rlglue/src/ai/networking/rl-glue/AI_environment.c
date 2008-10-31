/*
 *  AI_environment.c
 *  stella
 *
 *  Created by Andre Cohen on 7/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#include <stdio.h>

#include "RL_common.h"

Task_specification env_init(){
	Task_specification spec;
	fprintf(stderr,"Init\n");
	return 0;
}

Observation env_start(){
	Observation observation;
	fprintf(stderr,"Start\n");
	return observation;
}

Reward_observation env_step(Action a){
	Reward_observation observation;
	fprintf(stderr,"Step\n");
	return observation;
}

void env_cleanup(){
	fprintf(stderr,"Cleanup\n");
}

void env_set_state(State_key sk){
	fprintf(stderr,"State\n");
}

void env_set_random_seed(Random_seed_key rsk){
	fprintf(stderr,"Random\n");
}

State_key env_get_state(){
	State_key key;
	
	return key;
}

Random_seed_key env_get_random_seed(){
	RL_abstract_type key;
	return key;
}
 
Message env_message(const Message message){
	Message m;
	fprintf(stderr,"Message\n");
	return m;
}
