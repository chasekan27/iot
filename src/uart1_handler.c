#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/printk.h>

#include "uart1_handler.h"

#define UART1_NODE DT_NODELABEL(usart1)


/* --- UART ISR --- */
static void uart1_isr(const struct device *dev, void *user_data)
{
    ARG_UNUSED(user_data);

    if (!uart_irq_update(dev)) {
        return;
    }

    if (uart_irq_rx_ready(dev)) {
        uint8_t c;
        int len = uart_fifo_read(dev, &c, 1);
        if (len > 0) {
            printk("%c", c);   // Or push to ring buffer etc.
        }
    }
}

/* --- PUBLIC INIT FUNCTION --- */
void uart1_init(void)
{
    uart1_dev = DEVICE_DT_GET(UART1_NODE);

    if (!device_is_ready(uart1_dev)) {
        printk("UART1 not ready!\n");
        return;
    }

    uart_irq_callback_user_data_set(uart1_dev, uart1_isr, NULL);
    uart_irq_rx_enable(uart1_dev);

    printk("UART1 IRQ enabled.\n");
}
