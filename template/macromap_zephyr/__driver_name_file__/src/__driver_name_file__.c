#include <stdint.h>
#include <string.h>

#include "${driver_name_file}_base.h"
#include "${driver_name_file}_reg.h"
#include "${driver_name_file}_utils.h"

// ======== Macro Quick Access =================================================================

#define REG(_reg_)                         ${driver_name_macro}_REG(_reg_)
#define REG_MASK(_reg_, _field_)           ${driver_name_macro}_REG_MASK(_reg_, _field_)
#define REG_CONST(_reg_, _field_, _const_) ${driver_name_macro}_REG_CONST(_reg_, _field_, _const_)

#define REG_FIELD_GET(_reg_, _field_, _v_)                ${driver_name_macro}_REG_FIELD_GET(_reg_, _field_, _v_)
#define REG_FIELD_CLR(_reg_, _field_, _v_reg_)            ${driver_name_macro}_REG_FIELD_CLR(_reg_, _field_, _v_reg_)
#define REG_FIELD_SET(_reg_, _field_, _v_reg_, _v_field_) ${driver_name_macro}_REG_FIELD_SET(_reg_, _field_, _v_reg_, _v_field_)
#define REG_FIELD_SET_CONST(_reg_, _field_, _v_reg_, _const_)                                                          \
  ${driver_name_macro}_REG_FIELD_SET_CONST(_reg_, _field_, _v_reg_, _const_)

#define DRVR_LOG(msg)                                                                                                   \
  if (h != 0 && h->log != 0) {                                                                                         \
    h->log(msg, false, false, 0);                                                                                      \
  }

#define DRVR_LOG_VAR(msg, val)                                                                                          \
  if (h != 0 && h->log != 0) {                                                                                         \
    h->log(msg, false, true, val);                                                                                     \
  }

#define DRVR_ERR(msg)                                                                                                   \
  if (h != 0 && h->log != 0) {                                                                                         \
    h->log(msg, true, false, 0);                                                                                       \
  }

#define DRVR_ERR_VAR(msg, val)                                                                                          \
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

  /* todo */

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

  // Check PART_ID register
  uint8_t part_id = 0;
  err |= h->read_regs(REG(PART_ID), 1, &part_id);
  if (err) return err;
  DRVR_LOG_VAR("${driver_name_macro} Who-Am-I: ", (int)part_id);

  if (REG_FIELD_GET(PART_ID, ID, part_id) != REG_CONST(PART_ID, ID, VAL)) {
    DRVR_ERR_VAR("ERROR: ${driver_name_macro} Who-Am-I should be:", (int)REG_CONST(PART_ID, ID, VAL));
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
