
#ifndef TASK_SENSOR_ADC_ATTRIBUTE_H_
#define TASK_SENSOR_ADC_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include "main.h"
#include "task_system_attribute.h"
#include "stdio.h"
#include <stdbool.h>
/********************** macros ***********************************************/

/********************** typedef **********************************************/
typedef struct {
	uint32_t tick;
	uint32_t adc_value;
	bool     adc_ready;
} task_sensor_adc_dta_t;

/********************** external data declaration ****************************/
extern task_sensor_adc_dta_t task_sensor_adc_dta_list[];
/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_SENSOR_ATTRIBUTE_H_ */

/********************** end of file ******************************************/
