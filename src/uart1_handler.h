#ifndef UART1_HANDLER_H
#define UART1_HANDLER_H

#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>

void uart1_init(void);
extern const struct device *uart1_dev;


#endif // UART1_HANDLER_H
