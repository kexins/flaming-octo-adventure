/*
  name: Kexin Shi
  username: kexins
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/time.h>
#include "bathroomSim.h"
#include "bathroom.h"


#define pi 3.14159

int main(int argc, char *argv[]){
  
  srand(time(NULL));
  int nUsers, i;
  double meanArrival, meanStay, meanLoopCount;
  static  struct bathroom common_bathroom;
  
  nUsers = (int) atof(argv[1]);
  meanArrival = atof(argv[2]);
  meanStay = atof(argv[3]);
  meanLoopCount = atof(argv[4]);

  Initialize(&common_bathroom);
  pthread_t thread[nUsers];
  struct thread_data thread_data_array[nUsers];

  for (i=0; i<nUsers; i++){
    int err;  
    thread_data_array[i].shared_bathroom = common_bathroom;
    thread_data_array[i].arrive = abs(2 * meanArrival * drand48());
    thread_data_array[i].stay = normal(meanStay/2, meanStay) ;
    thread_data_array[i].loopCount = normal(meanLoopCount/2, meanLoopCount);    
    err = pthread_create(&thread[i], NULL, Individual, (void *) &thread_data_array[i]);
    if (err) {printf("unable to create thread\n");}   
  }

  
  for (i=0; i<nUsers; i++){
    if (thread[i]) (void) pthread_join(thread[i], NULL);
  } 
  
  return 0;
}

void *Individual(void *threadarg){
  struct thread_data *my_data;
  my_data = (struct thread_data *) threadarg;
  int i,j;
  enum gender g;
  j = rand()%2;
  if (j == 0)
    {g = male;}
  else {g = female;}
  struct bathroom shared_bathroom = my_data->shared_bathroom;
  float arrive = my_data->arrive;
  float stay = my_data->stay;
  int loopCount = my_data->loopCount;   
  struct timeval start, end;
  double time, max_time, min_time, total_time;
  max_time = 0; 
  min_time = 10000;
  total_time = 0;
  for (i=0; i<loopCount; i++){
    gettimeofday(&start, NULL);
    usleep(arrive*1000);
    gettimeofday(&end, NULL);
    Enter(g, &shared_bathroom);   
    usleep(stay*1000);
    Leave(&shared_bathroom);

  time = end.tv_sec * 1000 + end.tv_usec / 1000 - start.tv_sec * 1000 + start.tv_usec / 1000;
  total_time = total_time + time;
  if (max_time < time){max_time = time;}
  if (min_time > time){min_time = time;}
  }
  
  printf("thread number is %ld\n", (long int)syscall(SYS_gettid));  
  if (g == male){printf("thread gender: %s\n", "male");}
  else {printf("thread gender: %s\n", "female");}
  printf("thread loops: %d\n", loopCount);  
  printf("thread minimum time in queue: %f milliseconds\n", min_time);
  printf("thread maximum time in queue: %f milliseconds\n", max_time);
  printf("thread average time in queue: %f milliseconds\n\n", total_time/loopCount);

  return EXIT_SUCCESS;
}

double stdnormal(){
  double a,b,c;
  a = drand48();
  b = drand48();
  c = sqrt(-2 * log(a)) * cos(2 * pi *b);  
  return fabs(c);
}

double normal(double mean,double stddev){
  double x, z;
  z = stdnormal();
  x = stddev * z + mean;
  return x;
}





  
