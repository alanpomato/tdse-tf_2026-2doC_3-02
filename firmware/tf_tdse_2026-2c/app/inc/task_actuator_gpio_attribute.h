

#ifndef TASK_ACTUATOR_GPIO_ATTRIBUTE_H_
#define TASK_ACTUATOR_GPIO_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

/********************** macros ***********************************************/

/********************** typedef **********************************************/
/* Events to excite Task Actuator */
typedef enum task_actuator_gpio_ev {EV_BLINK,
								EV_OFF,
								EV_ON} task_actuator_gpio_ev_t;


								// EV_LED_ACTIVE,
								//EV_LED_IDLE,
/* States of Task Actuator */
typedef enum task_actuator_gpio_st {ST_OFF,
							   ST_ON,
							   ST_BLINK} task_actuator_gpio_st_t;

/* Identifier of Task Actuator */
typedef enum task_actuator_gpio_id {LED_STATUS, BUZZER} task_actuator_gpio_id_t;

typedef struct
{
	task_actuator_gpio_id_t	identifier;
	GPIO_TypeDef *		gpio_port;
	uint16_t			pin;
	GPIO_PinState		on;
	GPIO_PinState		off;
	uint32_t		tick_max;
} task_actuator_gpio_cfg_t;

typedef struct
{
	uint32_t			tick;
	task_actuator_gpio_st_t	state;
	task_actuator_gpio_ev_t	event;
	bool				flag;
} task_actuator_gpio_dta_t;

/********************** external data declaration ****************************/
extern task_actuator_gpio_dta_t task_actuator_gpio_dta_list[];

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_ACTUATOR_ATTRIBUTE_H_ */

/********************** end of file ******************************************/
