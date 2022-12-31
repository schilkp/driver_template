#include <stdint.h>
#include <string.h>

#include "${driver_name_file}.h"
#include "${driver_name_file}_regs.h"
#include "${driver_name_file}_reg_enums.h"

// ======== Macro Quick Access =================================================================

#define DRVR_LOG(msg)                                                                                                  \
  if (h != 0 && h->log != 0) {                                                                                         \
    h->log(msg, false, false, 0);                                                                                      \
  }

#define DRVR_LOG_VAR(msg, val)                                                                                         \
  if (h != 0 && h->log != 0) {                                                                                         \
    h->log(msg, false, true, val);                                                                                     \
  }

#define DRVR_ERR(msg)                                                                                                  \
  if (h != 0 && h->log != 0) {                                                                                         \
    h->log(msg, true, false, 0);                                                                                       \
  }

#define DRVR_ERR_VAR(msg, val)                                                                                         \
  if (h != 0 && h->log != 0) {                                                                                         \
    h->log(msg, true, true, val);                                                                                      \
  }

// ======== Private Prototypes =================================================================

static ${driver_name_code}_err_t check_connection(const struct ${driver_name_code}_h *h);
static ${driver_name_code}_err_t validate_handle(const struct ${driver_name_code}_h *h);

// ======== Public Functions =================================================================

${driver_name_code}_err_t ${driver_name_code}_reset(const struct ${driver_name_code}_h *h) {
  ${driver_name_code}_err_t err = E_${driver_name_macro}_SUCCESS;
  err |= validate_handle(h);
  if (err) return err;

  struct reg_ctrl reg_ctrl = {
    .reset = 1,
  };
  uint8_t reg_ctrl_packed = pack_reg_ctrl(&reg_ctrl);
  err |= h->write_regs(${driver_name_macro}_REG_CTRL, 1, &reg_ctrl_packed);

  return err;
}

${driver_name_code}_err_t ${driver_name_code}_init(const struct ${driver_name_code}_h *h) {
  ${driver_name_code}_err_t err = E_${driver_name_macro}_SUCCESS;
  err |= validate_handle(h);
  if (err) return err;
  
  err |= check_connection(h);
  if (err) return err;

  /* todo */

  return err;
}


// ======== Private Functions =================================================================

${driver_name_code}_err_t check_connection(const struct ${driver_name_code}_h *h) {

  ${driver_name_code}_err_t err = E_${driver_name_macro}_SUCCESS;

  // Check WHO_AM_I value:
  uint8_t reg_ctrl_packed = 0;
  err |= h->read_regs(${driver_name_macro}_REG_CTRL, 1, &reg_ctrl_packed);
  if (err) return err;

  struct reg_ctrl reg_ctrl = UNPACK_REG_CTRL(reg_ctrl_packed);

  DRVR_LOG_VAR("${driver_name_macro} Who-Am-I: ", (int)reg_ctrl.who_am_i);

  if (reg_ctrl.who_am_i != ${driver_name_macro}_WHO_AM_I_EXPECTED_VALUE) {
    DRVR_ERR_VAR("ERROR: ${driver_name_macro} Who-Am-I should be:", ${driver_name_macro}_WHO_AM_I_EXPECTED_VALUE);
    return E_${driver_name_macro}_COM_ERR;
  }

  return err;
}

${driver_name_code}_err_t validate_handle(const struct ${driver_name_code}_h *h) {
  ${driver_name_code}_err_t err = E_${driver_name_macro}_SUCCESS;

  if (h == 0) {
    err |= E_${driver_name_macro}_NULLPTR_ERR;
  }

  if (h->read_regs == 0) {
    DRVR_ERR("ERROR: read_regs is nullptr!")
    err |= E_${driver_name_macro}_NULLPTR_ERR;
  }

  if (h->write_regs == 0) {
    DRVR_ERR("ERROR: write_regs is nullptr!")
    err |= E_${driver_name_macro}_NULLPTR_ERR;
  }

  return err;
}
