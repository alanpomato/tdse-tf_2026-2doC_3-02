

/********************** inclusions *******************************************/
/* Project includes */
#include "main.h"

/* Demo includes */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes */
#include "board.h"
#include "app.h"
#include "task_actuator_gpio_attribute.h"
#include "task_actuator_gpio.h"

/********************** macros and definitions *******************************/
#define DEL_MIN		0ul
#define DEL_MED		25ul
#define DEL_MAX		50ul
#define DEL_LED		50ul
#define DEL_BUZZER	1ul

#define ACTUATOR_GPIO_CFG_QTY	(sizeof(task_actuator_gpio_cfg_list)/sizeof(task_actuator_gpio_cfg_t))
#define ACTUATOR_GPIO_DTA_QTY	ACTUATOR_GPIO_CFG_QTY

/********************** internal data declaration ****************************/
const task_actuator_gpio_cfg_t task_actuator_gpio_cfg_list[] = {
		{LED_STATUS, LED_STATUS_PORT, LED_STATUS_PIN, LED_STATUS_ON, LED_STATUS_OFF, DEL_LED},
		{BUZZER, BUZZER_PORT, BUZZER_PIN, BUZZER_ON, BUZZER_OFF, DEL_BUZZER}
};

task_actuator_gpio_dta_t task_actuator_gpio_dta_list[ACTUATOR_GPIO_DTA_QTY];

/********************** internal functions declaration ***********************/
void task_actuator_gpio_statechart(uint32_t index);

/********************** internal data definition *****************************/
const char *p_task_actuator 		= "Task Actuator Gpio (Actuator Statechart)";
const char *p_task_actuator_ 		= "Non-Blocking Code";
const char *p_task_actuator__ 		= "(Update by Time Code, period = 1mS)";

/********************** external data declaration ****************************/

/********************** external fu
 * nctions definition ************************/
void task_actuator_gpio_init(void *parameters)
{
	uint32_t index;
	const task_actuator_gpio_cfg_t *p_task_actuator_gpio_cfg;
	task_actuator_gpio_dta_t *p_task_actuator_gpio_dta;
	task_actuator_gpio_st_t state;
	task_actuator_gpio_ev_t event;
	bool b_event;

	/* Print out: Task Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - Tick [mS] = %lu", GET_NAME(task_actuator_init), HAL_GetTick());
	LOGGER_INFO("   %s is a %s", GET_NAME(task_actuator), p_task_actuator);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_actuator), p_task_actuator_);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_actuator), p_task_actuator__);

	for (index = 0; ACTUATOR_GPIO_DTA_QTY > index; index++)
	{
		/* Update Task Actuator Configuration & Data Pointer */
		p_task_actuator_gpio_cfg = &task_actuator_gpio_cfg_list[index];
		p_task_actuator_gpio_dta = &task_actuator_gpio_dta_list[index];

		/* Init & Print out: Index & Task execution FSM */
		state = ST_OFF;
		p_task_actuator_gpio_dta->state = state;

		event = EV_OFF;
		p_task_actuator_gpio_dta->event = event;

		b_event = false;
		p_task_actuator_gpio_dta->flag = b_event;

		LOGGER_INFO(" ");
		LOGGER_INFO("   %s = %lu   %s = %lu   %s = %lu   %s = %s",
					 GET_NAME(index), index,
					 GET_NAME(state), (uint32_t)state,
					 GET_NAME(event), (uint32_t)event,
					 GET_NAME(b_event), (b_event ? "true" : "false"));

		HAL_GPIO_WritePin(p_task_actuator_gpio_cfg->gpio_port, p_task_actuator_gpio_cfg->pin, p_task_actuator_gpio_cfg->off);
	}
}

void task_actuator_gpio_update(void *parameters)
{
	uint32_t index;

	for (index = 0; ACTUATOR_GPIO_DTA_QTY > index; index++)
	{
		/* Run Task Statechart */
		task_actuator_gpio_statechart(index);
	}
}

void task_actuator_gpio_statechart(uint32_t index)
{
	const task_actuator_gpio_cfg_t *p_task_actuator_gpio_cfg;
	task_actuator_gpio_dta_t *p_task_actuator_gpio_dta;

	/* Update Task Actuator Configuration & Data Pointer */
	p_task_actuator_gpio_cfg = &task_actuator_gpio_cfg_list[index];
	p_task_actuator_gpio_dta = &task_actuator_gpio_dta_list[index];

	switch (p_task_actuator_gpio_dta->state)
	{
		case ST_OFF:

			if ((true == p_task_actuator_gpio_dta->flag) && (EV_ON == p_task_actuator_gpio_dta->event))
			{
				p_task_actuator_gpio_dta->flag = false;
				HAL_GPIO_WritePin(p_task_actuator_gpio_cfg->gpio_port, p_task_actuator_gpio_cfg->pin, p_task_actuator_gpio_cfg->on);
				p_task_actuator_gpio_dta->state = ST_ON;
			}

			if ((true == p_task_actuator_gpio_dta->flag) && (EV_BLINK == p_task_actuator_gpio_dta->event))
			{
				p_task_actuator_gpio_dta->flag = false;
				p_task_actuator_gpio_dta->tick  = p_task_actuator_gpio_cfg->tick_max;
				HAL_GPIO_WritePin(p_task_actuator_gpio_cfg->gpio_port, p_task_actuator_gpio_cfg->pin, p_task_actuator_gpio_cfg->on);
				p_task_actuator_gpio_dta->state = ST_BLINK;
			}

			break;

		case ST_ON:

			if ((true == p_task_actuator_gpio_dta->flag) && (EV_OFF == p_task_actuator_gpio_dta->event))
			{
				p_task_actuator_gpio_dta->flag = false;
				HAL_GPIO_WritePin(p_task_actuator_gpio_cfg->gpio_port, p_task_actuator_gpio_cfg->pin, p_task_actuator_gpio_cfg->off);
				p_task_actuator_gpio_dta->state = ST_OFF;
			}

			if ((true == p_task_actuator_gpio_dta->flag) && (EV_BLINK == p_task_actuator_gpio_dta->event))
			{
				p_task_actuator_gpio_dta->flag = false;
				p_task_actuator_gpio_dta->tick  = p_task_actuator_gpio_cfg->tick_max;
				HAL_GPIO_WritePin(p_task_actuator_gpio_cfg->gpio_port, p_task_actuator_gpio_cfg->pin, p_task_actuator_gpio_cfg->off);
				p_task_actuator_gpio_dta->state = ST_BLINK;
			}

			break;

		case ST_BLINK:
			if ((true == p_task_actuator_gpio_dta->flag) && (EV_OFF == p_task_actuator_gpio_dta->event))
			{
				p_task_actuator_gpio_dta->flag = false;
				HAL_GPIO_WritePin(p_task_actuator_gpio_cfg->gpio_port, p_task_actuator_gpio_cfg->pin, p_task_actuator_gpio_cfg->off);
				p_task_actuator_gpio_dta->state = ST_OFF;
			}

			if ((true == p_task_actuator_gpio_dta->flag) && (EV_ON == p_task_actuator_gpio_dta->event))
			{
				p_task_actuator_gpio_dta->flag = false;
				HAL_GPIO_WritePin(p_task_actuator_gpio_cfg->gpio_port, p_task_actuator_gpio_cfg->pin, p_task_actuator_gpio_cfg->on);
				p_task_actuator_gpio_dta->state = ST_ON;
			}
			if (p_task_actuator_gpio_dta->tick == 0)
			{
				p_task_actuator_gpio_dta->tick  = p_task_actuator_gpio_cfg->tick_max;
				HAL_GPIO_TogglePin(p_task_actuator_gpio_cfg->gpio_port, p_task_actuator_gpio_cfg->pin);
			}

			else
			{
				p_task_actuator_gpio_dta->tick--;
			}




			break;


		default:

			p_task_actuator_gpio_dta->tick  = DEL_MIN;
			p_task_actuator_gpio_dta->state = ST_OFF;
			p_task_actuator_gpio_dta->event = EV_OFF;
			p_task_actuator_gpio_dta->flag = false;

			break;
	}
}

/********************** end of file ******************************************/
