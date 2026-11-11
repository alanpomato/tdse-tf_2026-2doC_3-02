

#ifndef TASK_SENSOR_BTN_ATTRIBUTE_H_
#define TASK_SENSOR_BTN_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include "main.h"
#include "task_system_attribute.h"
/********************** macros ***********************************************/

/********************** typedef **********************************************/
/* Events to excite Task Sensor */
typedef enum task_sensor_btn_ev {EV_BTN_UP,
							 EV_BTN_DOWN} task_sensor_btn_ev_t;

/* States of Task Sensor */
typedef enum task_sensor_btn_st {ST_BTN_UP,
							 ST_BTN_DOWN,
							ST_BTN_RAISING,
							ST_BTN_FALLING} task_sensor_btn_st_t;

/* Identifier of Task Sensor */
typedef enum task_sensor_btn_id {ID_BTN_ENTER, ID_BTN_NEXT, ID_BTN_ESC, ID_SW_SETUP, ID_BARRERA, ID_BTN_MONEDA} task_sensor_btn_id_t;

typedef struct
{
	task_sensor_btn_id_t	identifier;
	GPIO_TypeDef *		gpio_port;
	uint16_t			pin;
	GPIO_PinState		pressed;
	uint32_t			tick_max;
	task_system_ev_t	signal_pressed;
	task_system_ev_t	signal_released;
} task_sensor_btn_cfg_t;

typedef struct
{
	uint32_t			tick;
	task_sensor_btn_st_t	state;
	task_sensor_btn_ev_t	event;
} task_sensor_btn_dta_t;

/********************** external data declaration ****************************/
extern task_sensor_btn_dta_t task_sensor_btn_dta_list[];

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_SENSOR_ATTRIBUTE_H_ */

/********************** end of file ******************************************/
