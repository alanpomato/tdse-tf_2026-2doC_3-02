#ifndef TASK_ACTUATOR_PWM_ATTRIBUTE_H_
#define TASK_ACTUATOR_PWM_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

/********************** macros ***********************************************/

/********************** typedef **********************************************/
/* Events to excite Task Actuator */
typedef enum task_actuator_pwm_ev {EV_PWM_OFF,
								EV_PWM_ON} task_actuator_pwm_ev_t;


								// EV_LED_ACTIVE,
								//EV_LED_IDLE,
/* States of Task Actuator */
typedef enum task_actuator_pwm_st {ST_PWM_OFF,
							   ST_PWM_ON} task_actuator_pwm_st_t;

/* Identifier of Task Actuator */
typedef enum task_actuator_pwm_id {CANAL_1, CANAL_2} task_actuator_pwm_id_t;

typedef struct
{
	task_actuator_pwm_id_t	identifier;
	uint32_t			canal;
	uint16_t			ccr_reposo;
	uint16_t			ccr_entrega;
} task_actuator_pwm_cfg_t;

typedef struct
{
	uint32_t			tick;
	task_actuator_pwm_st_t	state;
	task_actuator_pwm_ev_t	event;
	bool				flag;
} task_actuator_pwm_dta_t;

/********************** external data declaration ****************************/
extern task_actuator_pwm_dta_t task_actuator_pwm_dta_list[];

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_ACTUATOR_ATTRIBUTE_H_ */

/********************** end of file ******************************************/
