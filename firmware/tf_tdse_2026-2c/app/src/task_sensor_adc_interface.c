
/********************** inclusions *******************************************/

/* Demo includes */
#include "main.h"
#include <stdbool.h>

/* Application & Tasks includes */
#include "board.h"
#include "app.h"
#include "task_sensor_adc_attribute.h"
#include "task_sensor_adc_interface.h"

/********************** macros and definitions *******************************/

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data declaration ****************************/

/********************** external functions definition ************************/
bool get_temperatura(uint32_t *t)
{
	if (!task_sensor_adc_dta_list[0].adc_ready) return false; // verifico que flag esté alta.

	*t = (uint32_t)task_sensor_adc_dta_list[0].adc_value * 60 / 4096;   // °C, 0..60

	task_sensor_adc_dta_list[0].adc_ready=false; // bajo flag

	return true;
}



/********************** end of file ******************************************/
