#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include <string.h>
#include "esp8266_init.h"
const struct device *uart1_dev;

unsigned int at_command_send(unsigned char *cmd)
 {
    while (*cmd) 
    {
        uart_poll_out(uart1_dev, *cmd++);
    }
    return 0;
 }

void init_nodemcu8266_module(void *p1, void *p2, void *p3)
{
        //at_command_send("AT+CIPMUX=0\r\n");
        //k_msleep(5000);
        //at_command_send("AT+CIPCLOSE\r\n");
        //k_msleep(10000);

    #define mobile_hotspot
    //#define lyptus_wifi

        /*at_command_send("AT\r\n");
        k_msleep(2000);
        at_command_send("AT+GMR\r\n");
        k_msleep(2000); 
        at_command_send("AT+CWMODE=1\r\n");
        k_msleep(2000);
        at_command_send("AT+CWLAP\r\n");
        k_msleep(6000);
        */
#ifdef mobile_hotspot
        at_command_send("AT+CWJAP=\"POCO\",\"Aaaaaa1.\"\r\n");
        k_msleep(10000);
#endif
#ifdef lyptus_wifi
        at_command_send("AT+CWJAP=\"Lyptus-Tech\",\"L#@!4Tech\"\r\n");
        k_msleep(10000);
#endif
       // at_command_send("AT+CIFSR\r\n");
        //k_msleep(5000);
        //at_command_send("AT+GMR\r\n");
        //k_msleep(6000);
        //at_command_send("AT+CIPSTART=\"SSL\",\"0b70db84ddf14cfe9d3508a868ec097a.s1.eu.hivemq.cloud\",8883\r\n");
        //at_command_send("AT+CIPSTART=\"TCP\",\"test.mosquitto.org\",1883\r\n");
        //at_command_send("AT+CIPSTART=\"TCP\",\"test.mosquitto.org\",1883\r\n");
        at_command_send("AT+CIPSTART=\"SSL\",\"broker.hivemq.com\",8883\r\n");
        //at_command_send("AT+CIPSTART=\"TCP\",\"test.mosquitto.org\",1883\r\n");
        //at_command_send("AT+CIPSTART=\"TCP\",\"broker.emqx.io\",1883\r\n");
        //at_command_send("AT+CIPSTART=\"TCP\",\"18.194.14.62\",1883\r\n");



        k_msleep(5000);    
 
    while (1)
    {
               k_msleep(2000);    
    }
}