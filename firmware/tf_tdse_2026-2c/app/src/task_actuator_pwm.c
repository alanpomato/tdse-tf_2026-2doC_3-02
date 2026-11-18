

/********************** inclusions *******************************************/
/* Project includes */
#include "main.h"

/* Demo includes */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes */
#include "board.h"
#include "app.h"
#include "task_actuator_pwm_attribute.h"

#include "task_actuator_pwm_interface.h"

/********************** macros and definitions *******************************/
#define CCR_REPOSO		1000ul
#define CCR_ENTREGA		2000ul

#define ACTUATOR_PWM_CFG_QTY	(sizeof(task_actuator_pwm_cfg_list)/sizeof(task_actuator_pwm_cfg_t))
#define ACTUATOR_PWM_DTA_QTY	ACTUATOR_PWM_CFG_QTY

/********************** internal data declaration ****************************/
const task_actuator_pwm_cfg_t task_actuator_pwm_cfg_list[] = {
		{CANAL_1, TIM_CHANNEL_1, CCR_REPOSO, CCR_ENTREGA},
		{CANAL_2, TIM_CHANNEL_2, CCR_REPOSO, CCR_ENTREGA},

};

task_actuator_pwm_dta_t task_actuator_pwm_dta_list[ACTUATOR_PWM_DTA_QTY];

/********************** internal functions declaration ***********************/
void task_actuator_pwm_statechart(uint32_t index);

/********************** internal data definition *****************************/
const char *p_task_actuator_pwm 		= "Task Actuator pwm (Actuator Statechart)";
const char *p_task_actuator_pwm_ 		= "Non-Blocking Code";
const char *p_task_actuator_pwm__ 		= "(Update by Time Code, period = 1mS)";

/********************** external data declaration ****************************/
extern TIM_HandleTypeDef htim3;
/********************** external fu
 * nctions definition ************************/
void task_actuator_pwm_init(void *parameters)
{
	uint32_t index;
	const task_actuator_pwm_cfg_t *p_task_actuator_pwm_cfg;
	task_actuator_pwm_dta_t *p_task_actuator_pwm_dta;
	task_actuator_pwm_st_t state;
	task_actuator_pwm_ev_t event;
	bool b_event;

	/* Print out: Task Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - Tick [mS] = %lu", GET_NAME(task_actuator_pwm_init), HAL_GetTick());
	LOGGER_INFO("   %s is a %s", GET_NAME(task_actuator_pwm), p_task_actuator_pwm);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_actuator_pwm), p_task_actuator_pwm_);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_actuator_pwm), p_task_actuator_pwm__);

	for (index = 0; ACTUATOR_PWM_DTA_QTY > index; index++)
	{
		/* Update Task Actuator Configuration & Data Pointer */
		p_task_actuator_pwm_cfg = &task_actuator_pwm_cfg_list[index];
		p_task_actuator_pwm_dta = &task_actuator_pwm_dta_list[index];

		/* Init & Print out: Index & Task execution FSM */
		state = ST_PWM_OFF;
		p_task_actuator_pwm_dta->state = state;

		event = EV_PWM_OFF;
		p_task_actuator_pwm_dta->event = event;

		b_event = false;
		p_task_actuator_pwm_dta->flag = b_event;

		LOGGER_INFO(" ");
		LOGGER_INFO("   %s = %lu   %s = %lu   %s = %lu   %s = %s",
					 GET_NAME(index), index,
					 GET_NAME(state), (uint32_t)state,
					 GET_NAME(event), (uint32_t)event,
					 GET_NAME(b_event), (b_event ? "true" : "false"));

		HAL_TIM_PWM_Start(&htim3, p_task_actuator_pwm_cfg->canal);
		__HAL_TIM_SET_COMPARE(&htim3, p_task_actuator_pwm_cfg->canal, p_task_actuator_pwm_cfg->ccr_reposo);
	}
}

void task_actuator_pwm_update(void *parameters)
{
	uint32_t index;

	for (index = 0; ACTUATOR_PWM_DTA_QTY > index; index++)
	{
		/* Run Task Statechart */
		task_actuator_pwm_statechart(index);
	}
}

void task_actuator_pwm_statechart(uint32_t index)
{
	const task_actuator_pwm_cfg_t *p_task_actuator_pwm_cfg;
	task_actuator_pwm_dta_t *p_task_actuator_pwm_dta;

	/* Update Task Actuator Configuration & Data Pointer */
	p_task_actuator_pwm_cfg = &task_actuator_pwm_cfg_list[index];
	p_task_actuator_pwm_dta = &task_actuator_pwm_dta_list[index];

	switch (p_task_actuator_pwm_dta->state)
	{
		case ST_PWM_OFF:

			if ((true == p_task_actuator_pwm_dta->flag) && (EV_PWM_ON == p_task_actuator_pwm_dta->event))
			{
				p_task_actuator_pwm_dta->flag = false;
				__HAL_TIM_SET_COMPARE(&htim3, p_task_actuator_pwm_cfg->canal, p_task_actuator_pwm_cfg->ccr_entrega);
				p_task_actuator_pwm_dta->state = ST_PWM_ON;
			}

			break;

		case ST_PWM_ON:

			if ((true == p_task_actuator_pwm_dta->flag) && (EV_PWM_OFF == p_task_actuator_pwm_dta->event))
			{
				p_task_actuator_pwm_dta->flag = false;
				__HAL_TIM_SET_COMPARE(&htim3, p_task_actuator_pwm_cfg->canal, p_task_actuator_pwm_cfg->ccr_reposo);
				p_task_actuator_pwm_dta->state = ST_PWM_OFF;
			}
			break;

		default:

			p_task_actuator_pwm_dta->state = ST_PWM_OFF;
			p_task_actuator_pwm_dta->event = EV_PWM_OFF;
			p_task_actuator_pwm_dta->flag = false;

			break;
	}
}

/********************** end of file ******************************************/
