#ifndef THREAD_CREATION_H
#define THREAD_CREATION_H

#define NODEMCU8266_THREAD_STACK 1024
#define NODEMCU8266_THREAD_PRIO  2

unsigned int create_thread(void);

#endif
