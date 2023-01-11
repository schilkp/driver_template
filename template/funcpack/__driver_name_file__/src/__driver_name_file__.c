#include <stdint.h>
#include <string.h>

#include "${driver_name_file}.h"
#include "${driver_name_file}_regs.h"
#include "${driver_name_file}_reg_utils.h"
#include "${driver_name_file}_enums.h"

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

  // Check WHO_AM_I value:
  
  /* todo */ 

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
