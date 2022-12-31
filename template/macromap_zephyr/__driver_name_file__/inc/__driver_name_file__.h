/*
 * ${driver_name} Driver
 *
 * ${author_name}
 * ${author_affiliation}
 */

#ifndef ${driver_name_macro}_H_
#define ${driver_name_macro}_H_

#ifndef CONFIG_${driver_name_zephyr}
/* Running without zephyr, expose normal driver: */
#include "${driver_name_file}_base.h"
#else
/* Running with zephyr, expose zephyr driver: */
#include "${driver_name_file}_zephyr.h"
#endif /* CONFIG_${driver_name_zephyr} */

#endif /* ${driver_name_macro}_H_ */
