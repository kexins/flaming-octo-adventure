/*
  name: Kexin Shi
  username: kexins
 */
#ifndef BATHROOMSIM_H
#define BATHROOMSIM_H

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/unistd.h>
#include <math.h>
#include <sys/types.h>
#include "bathroom.h"

struct thread_data{  
  struct bathroom shared_bathroom;
  float arrive;
  float stay;
  int loopCount;
};

void *Individual(void *threadarg);

double stdnormal();

double normal(double mean,double stddev);

#endif
