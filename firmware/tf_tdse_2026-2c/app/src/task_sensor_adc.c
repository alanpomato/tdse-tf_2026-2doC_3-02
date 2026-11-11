

/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"

/* Demo includes. */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes. */
#include "board.h"
#include "task_sensor_adc.h"
#include "task_sensor_adc_attribute.h"

/********************** macros and definitions *******************************/
#define DEL_ADC_MAX 100
#define ADC_QTY 1

/********************** internal data declaration ****************************/
task_sensor_adc_dta_t task_sensor_adc_dta_list[ADC_QTY];

/********************** internal functions declaration ***********************/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

/********************** internal data definition *****************************/
const char *p_task_adc 		= "Task ADC";

/********************** external data declaration *****************************/

extern ADC_HandleTypeDef hadc1;

/********************** external functions definition ************************/
void task_sensor_adc_init(void *parameters)
{
	task_sensor_adc_dta_list->tick = DEL_ADC_MAX;

	/* Print out: Task Initialized */
	LOGGER_LOG("  %s is running - %s\r\n", GET_NAME(task_adc_init), p_task_adc);

	task_sensor_adc_dta_list->adc_ready = false;
}

void task_sensor_adc_update(void *parameters)
{
	task_sensor_adc_dta_list->tick--;
	if (task_sensor_adc_dta_list->tick == 0) {
		task_sensor_adc_dta_list->tick = DEL_ADC_MAX;
		HAL_ADC_Start_IT(&hadc1);

	}
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	task_sensor_adc_dta_list->adc_value = HAL_ADC_GetValue(hadc);
	task_sensor_adc_dta_list->adc_ready = true;
}



/********************** end of file ******************************************/
