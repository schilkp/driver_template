#include "${driver_name_file}.h"
#include <stdio.h>

/*! \file example.c
    \brief Driver Example
*/

#define UNUSED(x) (void)(x)

// Function prototypes:
${driver_name_code}_err_t read_regs(uint8_t reg_adr, uint32_t n, uint8_t *buf);
${driver_name_code}_err_t write_regs(uint8_t reg_adr, uint32_t n, const uint8_t *buf);
void drvrlog(char *msg, bool is_err, bool has_int_arg, uint32_t arg);

int use_driver() {

  // Create a handle struct, providing all relevant hardware-specific functions
  // and configuration:
  struct ${driver_name_code}_h h = {
    .read_regs = read_regs,
    .write_regs = write_regs,
    .log = drvrlog,
    .conf = {
      .shutdown = false,
    },
  };

  if (${driver_name_code}_init(&h) != E_${driver_name_macro}_SUCCESS) {
    printf("Driver Init failed!\n");
    return -1;
  }

#warning example.c not yet implemented!

  return 0;
}

${driver_name_code}_err_t read_regs(uint8_t reg_adr, uint32_t n, uint8_t *buf) {
  UNUSED(reg_adr);
  UNUSED(n);
  UNUSED(buf);
  return E_${driver_name_macro}_COM_ERR; // TODO
}

${driver_name_code}_err_t write_regs(uint8_t reg_adr, uint32_t n, const uint8_t *buf) {
  UNUSED(reg_adr);
  UNUSED(n);
  UNUSED(buf);
  return E_${driver_name_macro}_COM_ERR; // TODO
}

void drvrlog(char *msg, bool is_err, bool has_int_arg, uint32_t arg) {
  if (has_int_arg) {
    printf("%s: %s %i", is_err ? "ERR" : "LOG", msg, arg);
  } else {
    printf("%s: %s", is_err ? "ERR" : "LOG", msg);
  }
}


