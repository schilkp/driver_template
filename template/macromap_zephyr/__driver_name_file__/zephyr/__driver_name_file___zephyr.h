#ifndef ${driver_name_macro}_ZEPHYR_H_
#define ${driver_name_macro}_ZEPHYR_H_

#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/i2c.h>
// #include <zephyr/drivers/spi.h>

#include <zephyr/logging/log.h>
#include <zephyr/logging/log_instance.h>

#include "${driver_name_file}_base.h"

struct ${driver_name_code}_config {
  const struct i2c_dt_spec i2c;
  // const struct spi_dt_spec i2c;
};

struct ${driver_name_code}_data {
  struct ${driver_name_code}_h driver_handle; // The state of the generic driver.
  struct {
    const int _unused;             // avoid empty struct if there is no logging
    LOG_INSTANCE_PTR_DECLARE(log); // Create an instance logger (if CONFIG_LOG is set)
  } logging;
};

#endif /* ${driver_name_macro}_ZEPHYR_H_ */
