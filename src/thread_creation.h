#ifndef THREAD_CREATION_H
#define THREAD_CREATION_H

#define NODEMCU8266_THREAD_STACK 1024
#define NODEMCU8266_THREAD_PRIO  2
#define BPM280_THREAD_STACK 1024
#define BPM280_THREAD_PRIO  1

unsigned int create_thread(void);
extern struct k_sem pbm280_sem;

#endif
