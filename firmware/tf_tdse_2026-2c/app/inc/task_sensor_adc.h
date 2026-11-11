#ifndef TASK_SENSOR_ADC_H_
#define TASK_SENSOR_ADC_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

/********************** macros ***********************************************/

/********************** typedef **********************************************/


/********************** external data declaration ****************************/
extern uint32_t g_task_a_cnt;
/********************** external functions declaration ***********************/
void task_sensor_adc_init(void *parameters);
void task_sensor_adc_update(void *parameters);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_INC_TASK_ADC_H_ */

/********************** end of file ******************************************/
