
#ifndef TASK_ACTUATOR_DISPLAY_INTERFACE_H_
#define TASK_ACTUATOR_DISPLAY_INTERFACE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include "task_actuator_display_attribute.h"
/********************** macros ***********************************************/

/********************** typedef **********************************************/

/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/
extern void put_event_task_actuator_display(uint32_t char_row, uint32_t char_column, const char *message);
void set_display(pantalla_t pantalla, display_valores_t valores);
void task_actuator_display_setup(task_actuator_display_dta_t *p_dta);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_DISPLAY_INTERFACE_H_ */

/********************** end of file ******************************************/
