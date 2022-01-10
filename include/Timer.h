#ifndef _Timer_H_
#define _Timer_H_

#include <stdio.h>
#include <sys/time.h>
#include "Terminal.h"

#define START 1
#define END 0

/**
 * @brief lance ou arrete un chrono
 * 
 * @pre what_do vaut START (0) ou END (1)
 * @post si "what_do" vaut START alors lance le chrono, si "what_do" vaut END affiche le temps écouler depuis le derner Clock(START) (en milli-seconds) et retourne le timer (en micro-seconds)
 * 
 * @param what_do 
 */
long Clock(int what_do);

#endif
