#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>

/* Aliases from devicetree */
#define SW1_BUTTON_NODE DT_ALIAS(sw1)
#define SW2_BUTTON_NODE DT_ALIAS(sw2)
#define LED0_NODE       DT_ALIAS(led0)
#define LED1_NODE       DT_ALIAS(led1)

/* Exported global GPIO specs */
const struct gpio_dt_spec sw1button = GPIO_DT_SPEC_GET(SW1_BUTTON_NODE, gpios);
const struct gpio_dt_spec sw2button = GPIO_DT_SPEC_GET(SW2_BUTTON_NODE, gpios);
const struct gpio_dt_spec led0      = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
const struct gpio_dt_spec led1      = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

/* Initialization function */
//static
int gpio_app_init(void)
{
    int ret;

    if (!gpio_is_ready_dt(&sw1button)) {
        printk("SW1 GPIO not ready\n");
        return -ENODEV;
    }

    if (!gpio_is_ready_dt(&sw2button)) {
        printk("SW2 GPIO not ready\n");
        return -ENODEV;
    }

    if (!gpio_is_ready_dt(&led0)) {
        printk("LED0 GPIO not ready\n");
        return -ENODEV;
    }

    if (!gpio_is_ready_dt(&led1)) {
        printk("LED1 GPIO not ready\n");
        return -ENODEV;
    }

    ret = gpio_pin_configure_dt(&sw1button, GPIO_INPUT);
    if (ret < 0) {
        printk("Failed to configure SW1\n");
        return ret;
    }

    ret = gpio_pin_configure_dt(&sw2button, GPIO_INPUT);
    if (ret < 0) {
        printk("Failed to configure SW2\n");
        return ret;
    }

    ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT);
    if (ret < 0) {
        printk("Failed to configure LED0\n");
        return ret;
    }

    ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT);
    if (ret < 0) {
        printk("Failed to configure LED1\n");
        return ret;
    }

    printk("GPIO initialization done.\n");
    return 0;
}

/* Run initialization at POST_KERNEL priority */
//SYS_INIT(gpio_app_init, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
