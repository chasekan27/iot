#include <zephyr/kernel.h>
#include "thread_creation.h"
#include "esp8266_init.h"
#include "bmp280.h"

/* Thread stack */
K_THREAD_STACK_DEFINE(nodemcu8266_stack, NODEMCU8266_THREAD_STACK);
K_THREAD_STACK_DEFINE(bpm280_stack, BPM280_THREAD_STACK);
/* Semaphore for data synchronization */
K_SEM_DEFINE(pbm280_sem, 0, 1);
/* Thread control block */
static struct k_thread nodemcu8266_thread;
static struct k_thread bpm280_thread;
unsigned int create_thread(void)
{
    /* Create WiFi init thread */
k_thread_create(
    &nodemcu8266_thread,                 // Thread control block (k_thread object)
    nodemcu8266_stack,                   // Pointer to thread stack memory
    K_THREAD_STACK_SIZEOF(nodemcu8266_stack),  // Size of the stack
    init_nodemcu8266_module,             // Thread entry function
    NULL, NULL, NULL,                    // Arguments passed to the entry function
    NODEMCU8266_THREAD_PRIO,             // Thread priority
    0,                                   // Thread options (e.g., cooperativity)
    K_NO_WAIT                            // Start immediately after creation
);
    /* Create BMP280 read thread */
k_thread_create(
    &bpm280_thread,                      // Thread control block (k_thread object)
    bpm280_stack,                        // Pointer to thread stack memory
    K_THREAD_STACK_SIZEOF(bpm280_stack), // Size of the stack
    bmp280_read_values,                  // Thread entry function
    NULL, NULL, NULL,                    // Arguments passed to the entry function
    BPM280_THREAD_PRIO,                  // Thread priority
    0,                                   // Thread options (e.g., cooperativity)
    K_NO_WAIT                            // Start immediately after creation
);
    return 0;
}