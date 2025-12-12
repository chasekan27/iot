#include <string.h>
#include "esp8266_init.h"
#include "uart1_handler.h"
#include <zephyr/kernel.h>
#include "thread_creation.h"
#include "my_dts_init.h"
    int main(void)
    {
        gpio_app_init(); 
        uart1_init();
        create_thread();
        while (1) 
        {
            k_msleep(1000);
        }
        return 0;
    }
