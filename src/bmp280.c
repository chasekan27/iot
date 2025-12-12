#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/i2c.h>

/* Sensor node */
#define BMP_NODE DT_NODELABEL(bmp280)
static const struct device *bmp280 = DEVICE_DT_GET(BMP_NODE);

/* Get I2C controller (parent of bmp280) */
#define I2C_NODE DT_PARENT(BMP_NODE)
static const struct device *i2c_bus = DEVICE_DT_GET(I2C_NODE);

void bmp280_read_values(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    struct sensor_value temp, press;

    /* Check device readiness */
    if (!device_is_ready(i2c_bus)) {
        printk("I2C bus not ready\n");
        return;
    }

    if (!device_is_ready(bmp280)) {
        printk("BMP280 device not ready\n");
        return;
    }

    printk("=== I2C SCANNER START ===\n");

    /* ---------- I2C SCAN ---------- */
    for (uint8_t addr = 1; addr < 127; addr++) 
    {
        uint8_t dummy;
        int ret = i2c_read(i2c_bus, &dummy, 1, addr);

        if (ret == 0) {
            printk("Found I2C device at 0x%02X\n", addr);
        }
    }

    printk("=== I2C SCAN COMPLETE ===\n");

    /* ---------- BMP280 LOOP ---------- */
    while (1) 
    {
        if (sensor_sample_fetch(bmp280) == 0) 
        {
            sensor_channel_get(bmp280, SENSOR_CHAN_AMBIENT_TEMP, &temp);
            sensor_channel_get(bmp280, SENSOR_CHAN_PRESS, &press);

            printk("T = %d.%06d C | P = %d.%06d kPa\n",
                   temp.val1, temp.val2,
                   press.val1, press.val2);
        } 
        else 
        {
            printk("BMP280 sample fetch failed\n");
        }

        k_msleep(1000);
    }
}
