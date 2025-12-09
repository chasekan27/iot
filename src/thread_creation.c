#include <zephyr/kernel.h>
#include "thread_creation.h"
#include "esp8266_init.h"

/* Thread stack */
K_THREAD_STACK_DEFINE(nodemcu8266_stack, NODEMCU8266_THREAD_STACK);

/* Thread control block */
static struct k_thread nodemcu8266_thread;

unsigned int create_thread(void)
{
    /* Create WiFi init thread */
    k_thread_create(
        &nodemcu8266_thread,             // thread object
        nodemcu8266_stack,                       // stack
        K_THREAD_STACK_SIZEOF(nodemcu8266_stack),
        init_nodemcu8266_module,                             // thread entry
        NULL, NULL, NULL,                             // parameters
        NODEMCU8266_THREAD_PRIO,                             // priority
        0,                                            // options
        K_NO_WAIT                                     // start immediately
    );
    return 0;
}