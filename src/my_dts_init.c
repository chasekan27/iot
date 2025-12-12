#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* Existing GPIO aliases (unchanged) */
#define SW1_BUTTON_NODE DT_ALIAS(sw1)
#define SW2_BUTTON_NODE DT_ALIAS(sw2)
#define LED0_NODE       DT_ALIAS(led0)
#define LED1_NODE       DT_ALIAS(led1)



/* Get GPIO device and pin configuration from device tree */
const struct gpio_dt_spec sw1button = GPIO_DT_SPEC_GET(SW1_BUTTON_NODE, gpios);
const struct gpio_dt_spec sw2button = GPIO_DT_SPEC_GET(SW2_BUTTON_NODE, gpios);
const struct gpio_dt_spec led0      = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
const struct gpio_dt_spec led1      = GPIO_DT_SPEC_GET(LED1_NODE, gpios);



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
    if (ret < 0) return ret;

    ret = gpio_pin_configure_dt(&sw2button, GPIO_INPUT);
    if (ret < 0) return ret;

    ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT);
    if (ret < 0) return ret;

    ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT);
    if (ret < 0) return ret;

    printk("GPIO initialization done.\n");
    return 0;
}

/*
void bmp280_read_values(void)
{
    struct sensor_value temp, press;

    if (!device_is_ready(bmp280)) {
        printk("BMP280 is not ready!\n");
        return;
    }

    if (sensor_sample_fetch(bmp280) < 0) {
        printk("Failed to fetch sample\n");
        return;
    }

sensor_sample_fetch(bmp280);
sensor_channel_get(bmp280, SENSOR_CHAN_AMBIENT_TEMP, &temp);
sensor_channel_get(bmp280, SENSOR_CHAN_PRESS, &press);

    printk("Temperature: %d.%06d °C\n", temp.val1, temp.val2);
    printk("Pressure:    %d.%06d kPa\n", press.val1, press.val2);
}

    bmp280_read_values();

}
*/
