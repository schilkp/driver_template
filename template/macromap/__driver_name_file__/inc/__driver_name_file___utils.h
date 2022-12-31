/*
 * ${driver_name} Driver - Macro Utils.
 *
 * Philipp Schilk, 2022
 * Free to use with no restrictions but no guarantees.
 */

#ifndef ${driver_name_macro}_UTILS_H_
#define ${driver_name_macro}_UTILS_H_

#include "${driver_name_file}.h"

// ======== Register Macros  =================================================================

#define ${driver_name_macro}_REG(_reg_)                         ${driver_name_macro}__REG_##_reg_
#define ${driver_name_macro}_REG_MASK(_reg_, _field_)           ${driver_name_macro}__REG_##_reg_##__FIELD_##_field_
#define ${driver_name_macro}_REG_CONST(_reg_, _field_, _const_) ${driver_name_macro}__REG_##_reg_##__FIELD_##_field_##__CONST_##_const_

// ======== Bit Manipulation =================================================================
#define ${driver_name_macro}_LSB_GET(_v_)             ((_v_) & -(_v_))
#define ${driver_name_macro}_FIELD_GET(_mask_, _v_)   (((_v_) & (_mask_)) / ${driver_name_macro}_LSB_GET(_mask_))
#define ${driver_name_macro}_FIELD_ALIGN(_mask_, _v_) (((_v_)*${driver_name_macro}_LSB_GET(_mask_)) & (_mask_))
#define ${driver_name_macro}_FIELD_CLR(_mask_, _v_)   ((_v_) & (~(_mask_)))
#define ${driver_name_macro}_FIELD_SET(_mask_, _v_reg_, _v_field_)                                                                 \
  (${driver_name_macro}_FIELD_ALIGN(_mask_, _v_field_) | ${driver_name_macro}_FIELD_CLR(_mask_, _v_reg_))

// ======== Register Bit Manipulation =================================================================
#define ${driver_name_macro}_REG_FIELD_GET(_reg_, _field_, _v_) (${driver_name_macro}_FIELD_GET(${driver_name_macro}_REG_MASK(_reg_, _field_), _v_))
#define ${driver_name_macro}_REG_FIELD_CLR(_reg_, _field_, _v_) (${driver_name_macro}_FIELD_CLR(${driver_name_macro}_REG_MASK(_reg_, _field_), _v_))
#define ${driver_name_macro}_REG_FIELD_SET(_reg_, _field_, _v_reg_, _v_field_)                                                     \
  (${driver_name_macro}_FIELD_SET(${driver_name_macro}_REG_MASK(_reg_, _field_), _v_reg_, _v_field_))
#define ${driver_name_macro}_REG_FIELD_SET_CONST(_reg_, _field_, _v_reg_, _const_)                                                 \
  ${driver_name_macro}_REG_FIELD_SET(_reg_, _field_, _v_reg_, ${driver_name_macro}_REG_CONST(_reg_, _field_, _const_))

#endif /* ${driver_name_macro}__UTILS_H_ */
