#ifndef ESP8266_INIT_H
#define ESP8266_INIT_H
extern const struct device *uart1_dev;
void init_nodemcu8266_module(void *p1, void *p2, void *p3);
unsigned int at_command_send(unsigned char *cmd);
#endif