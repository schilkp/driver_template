/*
 * ${driver_name} Driver
 *
 * ${author_name}
 * ${author_affiliation}
 */

/*! \file ${driver_name_file}_base.h
    \brief Main driver header.
*/

#ifndef ${driver_name_macro}_BASE_H_
#define ${driver_name_macro}_BASE_H_

#include <stdbool.h>
#include <stdint.h>

// ======== General Definitions ================================================

/**
 * @brief Driver error codes
 */
typedef enum {
  E_${driver_name_macro}_SUCCESS     = 0, //!< Success
  E_${driver_name_macro}_NULLPTR_ERR = (1 << 0), //!< Nullpointer error
  E_${driver_name_macro}_COM_ERR     = (1 << 1), //!< Communication error
  E_${driver_name_macro}_CONFIG_ERR  = (1 << 2), //!< Configuration error
  E_${driver_name_macro}_ERR         = (1 << 3), //!< Other error
} ${driver_name_code}_err_t;

// ======== Configuration ======================================================

/**
 * @brief Device Configuration
 */
struct ${driver_name_code}_conf{
  bool shutdown; //!< Shutdown device
};

// ======== Handle Definition ==================================================

/**
 * @brief Device Handle struct.
 * Represents a single physical device. Holds the hardware-specific interface functions,
 * and device configuration.
 */
struct ${driver_name_code}_h {
  // === Interface function pointers. Required. ===
  /**
   * @brief Pointer to the device-specific read-register functions
   * @warning Required!
   *
   * @param reg_adr Register address at which to start reading.
   * @param n Number of registers to read.
   * @param buf Buffer to store results.
   * @return @ref E_${driver_name_macro}_SUCCESS if read was successful, otherwise @ref E_${driver_name_macro}_COM_ERR.
   */
  ${driver_name_code}_err_t (*read_regs)(uint8_t reg_adr, uint32_t n, uint8_t *buf);

  /**
   * @brief Pointer to the device-specific write-register functions
   * @warning Required!
   *
   * @param reg_adr Register address at which to start writing.
   * @param n Number of registers to write.
   * @param buf Buffer of data to hold.
   * @return @ref E_${driver_name_macro}_SUCCESS if write was successful, otherwise @ref E_${driver_name_macro}_COM_ERR.
   */
  ${driver_name_code}_err_t (*write_regs)(uint8_t reg_adr, uint32_t n, const uint8_t *buf);


  // === Interface function pointers. Optional. ===

  /**
   * @brief Pointer to logging function.
   * Called by the driver to log status and error messages, with an optional integer
   * variable to log. Note that the string does not contain any formatting specifiers,
   * and should be logged as follows (if has_int_arg is true):
   *
   * printf("%s: %s %i", is_err ? "ERR" : "LOG", msg, arg);
   *
   * @param msg the log message
   * @param is_err indicates if this is an error message
   * @param has_int_arg indicates if this message is accompanied by an integer variable to log.
   * @param arg the integer variable to log if has_int_arg is true.
   */
  void (*log)(char *msg, bool is_err, bool has_int_arg, uint32_t arg);

  // === Device Configuration. Required. ===
  struct ${driver_name_code}_conf conf; //!< Configuration. Required.
};

// ======== Function Prototypes ================================================

/**
 * @brief Reset the device.
 *
 * @param h Pointer to the device-specific handle struct.
 * @return @ref E_${driver_name_macro}_SUCCESS if successful, otherwise an error code from @ref E_${driver_name_macro}_COM_ERR.
 */
${driver_name_code}_err_t ${driver_name_code}_reset(const struct ${driver_name_code}_h *h);


/**
 * @brief Initialize the device.
 * Validates the driver handle, Tests the connection to the device,
 * and applies the complete device configuration within the handle to the device.
 *
 * @note This function should be called before any other driver functions are called.
 *
 * @param h Pointer to the device-specific handle struct.
 * @return @ref E_${driver_name_macro}_SUCCESS if successful, otherwise an error code from @ref E_${driver_name_macro}_COM_ERR.
 */
${driver_name_code}_err_t ${driver_name_code}_init(const struct ${driver_name_code}_h *h);

#endif /* ${driver_name_macro}_BASE_H_ */
