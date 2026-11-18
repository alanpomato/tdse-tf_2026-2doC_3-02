
#ifndef TASK_ACTUATOR_PWM_INTERFACE_H_
#define TASK_ACTUATOR_PWM_INTERFACE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include "task_actuator_pwm_attribute.h"
/********************** macros ***********************************************/

/********************** typedef **********************************************/

/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/
extern void put_event_task_actuator_pwm(task_actuator_pwm_ev_t event, task_actuator_pwm_id_t identifier);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_ACTUATOR_INTERFACE_H_ */

/********************** end of file ******************************************/
