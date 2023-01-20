#include "${driver_name_file}_zephyr.h"

LOG_MODULE_REGISTER(${driver_name_zephyr}, CONFIG_LOG_DEFAULT_LEVEL);

// ======== Zephyr wrapper functions ==============================================================

static int zephyr_${driver_name_code}_init(const struct device *dev) {
  struct ${driver_name_code}_data *data           = dev->data;
  struct ${driver_name_code}_h *h                 = &(data->driver_handle);
  const struct ${driver_name_code}_config *config = dev->config;

  LOG_INST_INF(data->logging.log, "Initializing ${driver_name_macro}..");
  
  // Ensure I2C bus is ready:
  if (!device_is_ready(config->i2c.bus)) {
    LOG_INST_ERR(data->logging.log, "I2C Not ready!");
    return -EIO;
  }

  // Initiate device:
  ${driver_name_code}_err_t err = E_${driver_name_macro}_SUCCESS;
  err |= ${driver_name_code}_init(h);
  if (err != E_${driver_name_macro}_SUCCESS) {
    LOG_INST_ERR(data->logging.log, "${driver_name_macro} init failed.");
    return -EIO;
  }

  LOG_INST_INF(data->logging.log, "${driver_name_macro} init OK.");
  return 0;
}

// ======== ZEPHYR Driver Instantiation ===========================================================

#define DT_DRV_COMPAT ${zephyr_dts_compat}

#if DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) == 0
#warning "${driver_name_macro} driver enabled without any devices!"
#endif

// Macro to create a single driver instance:
#define ${driver_name_macro}_DEFINE(_inst_)                                                                                     \
                                                                                                                       \
  /* Declare all driver instance specific functions: */                                                                \
  static ${driver_name_code}_err_t ${driver_name_code}_read_regs_##_inst_(uint8_t reg_adr, uint32_t n, uint8_t *buf);                               \
  static ${driver_name_code}_err_t ${driver_name_code}_write_regs_##_inst_(uint8_t reg_adr, uint32_t n, const uint8_t *buf);                        \
  static void ${driver_name_code}_log_##_inst_(char *msg, bool is_err, bool has_int_arg, uint32_t arg);                                  \
                                                                                                                       \
  /* Register this specific driver instance for logging: */                                                            \
  LOG_INSTANCE_REGISTER(${driver_name_code}alt, _inst_, CONFIG_LOG_DEFAULT_LEVEL)                                                 \
                                                                                                                       \
  /* Create the driver config, which contains the i2c_dt_spec for this instance: */                                    \
  static struct ${driver_name_code}_config ${driver_name_code}_config_##_inst_ = {                                                           \A
      .i2c = I2C_DT_SPEC_INST_GET(_inst_),                                                                             \
  };                                                                                                                   \
                                                                                                                       \
  /* Create the driver data, which holds the handle of the generic driver. Provide functions pointers to the           \
   * instance specifc read_reg and write_reg, and convert all device tree properties into the correct                  \
   * driver configurtaion. */                                                                                          \
  static struct ${driver_name_code}_data ${driver_name_code}_data_##_inst_ = {                                                               \
      .driver_handle =                                                                                                 \
          {                                                                                                            \
              .read_regs  = &${driver_name_code}_read_regs_##_inst_,                                                              \
              .write_regs = &${driver_name_code}_write_regs_##_inst_,                                                             \
              .log        = &${driver_name_code}_log_##_inst_,                                                                    \
              .sensor_conf =                                                                                           \
                  {                                                                                                    \
                    0 /* TODO */ \
                  },                                                                                                   \
          },                                                                                                           \
      .logging = {0, LOG_INSTANCE_PTR_INIT(log, ${driver_name_code}alt, _inst_)},                                                 \
  };                                                                                                                   \
                                                                                                                       \
  /* Implement the read_regs and write_regs functions with the signature expected by the generic driver                \
   * for this driver instance: */                                                                                      \
  static ${driver_name_code}_err_t ${driver_name_code}_read_regs_##_inst_(uint8_t reg_adr, uint32_t n, uint8_t *buf) {                              \
    if (i2c_burst_read_dt(&(${driver_name_code}_config_##_inst_.i2c), reg_adr, buf, n) != 0) {                                    \
      return E_${driver_name_macro}_COM_ERR;                                                                                       \
    }                                                                                                                  \
    return E_${driver_name_macro}_SUCCESS;                                                                                         \
  }                                                                                                                    \
  static ${driver_name_code}_err_t ${driver_name_code}_write_regs_##_inst_(uint8_t reg_adr, uint32_t n, const uint8_t *buf) {                       \
    if (i2c_burst_write_dt(&(${driver_name_code}_config_##_inst_.i2c), reg_adr, buf, n) != 0) {                                   \
      return E_${driver_name_macro}_COM_ERR;                                                                                       \
    }                                                                                                                  \
    return E_${driver_name_macro}_SUCCESS;                                                                                         \
  }                                                                                                                    \
  /* Implement the instance-specific log function: */                                                                  \
  static void ${driver_name_code}_log_##_inst_(char *msg, bool is_err, bool has_int_arg, uint32_t arg) {                                 \
    if (is_err) {                                                                                                      \
      if (has_int_arg) {                                                                                               \
        LOG_INST_ERR(${driver_name_code}_data_##_inst_.logging.log, "%s 0x%x", msg, arg);                                         \
      } else {                                                                                                         \
        LOG_INST_ERR(${driver_name_code}_data_##_inst_.logging.log, "%s", msg);                                                   \
      }                                                                                                                \
    } else {                                                                                                           \
      if (has_int_arg) {                                                                                               \
        LOG_INST_INF(${driver_name_code}_data_##_inst_.logging.log, "%s 0x%x", msg, arg);                                         \
      } else {                                                                                                         \
        LOG_INST_INF(${driver_name_code}_data_##_inst_.logging.log, "%s", msg);                                                   \
      }                                                                                                                \
    }                                                                                                                  \
  }                                                                                                                    \
                                                                                                                       \
  /* Now, actually instantiate the device: */                                                                          \
  DEVICE_DT_INST_DEFINE(_inst_,                      /* Instance number */                                             \
                        zephyr_${driver_name_code}_init,        /* Init function */                                               \
                        NULL,                        /* No power-management yet */                                     \
                        &${driver_name_code}_data_##_inst_,     /* Data struct */                                                 \
                        &${driver_name_code}_config_##_inst_,   /* Config struct */                                               \
                        POST_KERNEL,                 /*Initialisation level: After kernel */                           \
                        CONFIG_SENSOR_INIT_PRIORITY, /* Initialisation priority with it's initialisation level */      \
                        NULL);                       /* API */

// Create a driver instance for each device tree node:
DT_INST_FOREACH_STATUS_OKAY(${driver_name_macro}_DEFINE);
