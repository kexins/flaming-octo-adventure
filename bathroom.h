/*
  name: Kexin Shi
  username: kexins
 */
#ifndef BATHROOM_H
#define BATHROOM_H

#include <pthread.h>

enum gender {male, female} ;

enum state {vacant, man, woman};


struct bathroom {
  pthread_mutex_t mutex;  
  pthread_cond_t occupied;
  int users;
  enum state st; 
  
};
  

void Enter(enum gender g, struct bathroom* shared_bathroom);

void Leave(struct bathroom* shared_bathroom);

void Initialize(struct bathroom* shared_bathroom);
#endif
