/*
  name: Kexin Shi
  username: kexins
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "bathroom.h"

void Initialize(struct bathroom* shared_bathroom){
  shared_bathroom->users = 0;
  shared_bathroom->st = vacant;
  pthread_mutex_init(&shared_bathroom->mutex, NULL);
  pthread_cond_init(&shared_bathroom->occupied, NULL);
}


void Enter(enum gender g, struct bathroom* shared_bathroom){  
  pthread_mutex_lock(&shared_bathroom->mutex);  
//  printf("lock success\n");
  if (g==male){	
//	printf("male trying to enter\n");
	while (shared_bathroom->st == woman){
//	  printf("male wait\n");
	  pthread_cond_wait(&shared_bathroom->occupied, &shared_bathroom->mutex);}
//	printf("male enter success\n");
	shared_bathroom->users++;
	if (shared_bathroom->st == woman){printf("Error Occurs\n");}
	shared_bathroom->st = man;
//	printf("state change to man\n");	
  }
  else if (g==female){	
//	printf("female enter\n");
	while (shared_bathroom->st == man){
//	  printf("female wait\n");
	  pthread_cond_wait(&shared_bathroom->occupied, &shared_bathroom->mutex);}
//	printf("female enter success\n");
	shared_bathroom->users++;
	if (shared_bathroom->st == man) {printf("Error Occurs\n");}
	shared_bathroom->st = woman;
//	printf("state change to woman\n");	
	}
  pthread_mutex_unlock(&shared_bathroom->mutex);
//  printf("unlock success\n\n");  
}

void Leave(struct bathroom* shared_bathroom){
   pthread_mutex_lock(&shared_bathroom->mutex);
    if (shared_bathroom->users == 1){	
//	printf("Only one left\n");
	shared_bathroom->users--;
	shared_bathroom->st = vacant;
	pthread_cond_broadcast(&shared_bathroom->occupied);	
    }
    else if (shared_bathroom->users > 1){
	shared_bathroom->users--;
    }
   pthread_mutex_unlock(&shared_bathroom->mutex);   
}









