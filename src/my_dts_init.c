#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>

/* Existing GPIO aliases (unchanged) */
#define SW1_BUTTON_NODE DT_ALIAS(sw1)
#define SW2_BUTTON_NODE DT_ALIAS(sw2)
#define LED0_NODE       DT_ALIAS(led0)
#define LED1_NODE       DT_ALIAS(led1)


#define BMP_NODE DT_NODELABEL(bmp280)
static const struct device *bmp280 = DEVICE_DT_GET(BMP_NODE);
void bmp280_read_values(void);

const struct gpio_dt_spec sw1button = GPIO_DT_SPEC_GET(SW1_BUTTON_NODE, gpios);
const struct gpio_dt_spec sw2button = GPIO_DT_SPEC_GET(SW2_BUTTON_NODE, gpios);
const struct gpio_dt_spec led0      = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
const struct gpio_dt_spec led1      = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

/* Get I2C device directly by node label (no alias) */
static const struct device *bpm_i2c = DEVICE_DT_GET(DT_NODELABEL(i2c2));


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

void i2c1_init(void)
{
    if (!device_is_ready(bpm_i2c)) {
        printk("I2C device not ready\n");
        return;
    }

    printk("I2C scanner running on %s\n", bpm_i2c->name);

    for (uint8_t addr = 1; addr < 127; addr++) {
        uint8_t data;
        if (i2c_read(bpm_i2c, &data, 1, addr) == 0) {
            printk("Found device at 0x%02X\n", addr);
        }
    }

void bmp280_read_values(void)
{
    struct sensor_value temp, press;

    if (!device_is_ready(bmp280)) {
        printk("BMP280 is not ready!\n");
        return;
    }

    /* Fetch all sensor channels */
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

