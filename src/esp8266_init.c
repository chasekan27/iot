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
 void init_wifi_module(void)
 {
        at_command_send("AT\r\n");
        k_msleep(2000);
        at_command_send("AT+CWMODE=1\r\n");
        k_msleep(2000);
        at_command_send("AT+CWLAP\r\n");
        k_msleep(6000);
        
        at_command_send("AT+CWJAP=\"POCO\",\"Aaaaaa1.\"\r\n");
        k_msleep(2000);
 }
void init_nodemcu8266_module(void *p1, void *p2, void *p3)
{
    while (1)
    {
        printk("i am node mcu module\n");
        k_msleep(1000);
    }
}