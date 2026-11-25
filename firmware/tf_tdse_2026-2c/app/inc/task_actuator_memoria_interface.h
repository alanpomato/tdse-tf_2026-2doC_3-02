
#ifndef TASK_ACTUATOR_MEMORIA_INTERFACE_H_
#define TASK_ACTUATOR_MEMORIA_INTERFACE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include "task_actuator_memoria_attribute.h"
#include <stdbool.h>
/********************** macros ***********************************************/

/********************** typedef **********************************************/

/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/
extern void cargar_config(uint16_t n);
bool config_lista(void *dst, uint16_t n);
extern bool guardar_config(const void *p, uint16_t n);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_ACTUATOR_INTERFACE_H_ */

/********************** end of file ******************************************/
