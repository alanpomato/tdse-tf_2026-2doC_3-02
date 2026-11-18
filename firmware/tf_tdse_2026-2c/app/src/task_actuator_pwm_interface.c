

/********************** inclusions *******************************************/
/* Project includes */

#include "main.h"

/* Demo includes */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes */
#include "board.h"
#include "app.h"
#include <task_actuator_pwm_attribute.h>
/********************** macros and definitions *******************************/

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data declaration ****************************/

/********************** external functions definition ************************/
void put_event_task_actuator_pwm(task_actuator_pwm_ev_t event, task_actuator_pwm_id_t identifier)
{
	task_actuator_pwm_dta_t *p_task_actuator_pwm_dta;

	p_task_actuator_pwm_dta = &task_actuator_pwm_dta_list[identifier];

	p_task_actuator_pwm_dta->event = event;
	p_task_actuator_pwm_dta->flag = true;
}

/********************** end of file ******************************************/
