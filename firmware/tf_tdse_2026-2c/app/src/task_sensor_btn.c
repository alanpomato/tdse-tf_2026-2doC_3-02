
/********************** inclusions *******************************************/
/* Project includes */
#include "main.h"

/* Demo includes */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes */
#include "board.h"
#include "app.h"
#include "task_system_attribute.h"
#include "task_system_interface.h"
#include "task_sensor_btn_attribute.h"


/********************** macros and definitions *******************************/
#define DEL_BTN_MIN		0ul
#define DEL_BTN_MED		25ul
#define DEL_BTN_MAX		50ul

#define SENSOR_CFG_QTY		(sizeof(task_sensor_cfg_list)/sizeof(task_sensor_cfg_t))
#define SENSOR_DTA_QTY		SENSOR_CFG_QTY

/********************** CONFIGURACIÓN DE BOTONES -> Pongo los 3 botones para navegar en el menú + el switch entre SETUP/NORMAL ****************************/
const task_sensor_cfg_t task_sensor_cfg_list[] = {
	{ID_BTN_ENTER,  BTN_ENTER_PORT,  BTN_ENTER_PIN,  BTN_ENTER_PRESSED, DEL_BTN_MAX,
	EV_SYS_ENTER, EV_SYS_NONE},

	{ID_BTN_NEXT,  BTN_NEXT_PORT,  BTN_NEXT_PIN,  BTN_NEXT_PRESSED, DEL_BTN_MAX,
	EV_SYS_NEXT, EV_SYS_NONE},

	 {ID_BTN_ESC,  BTN_ESC_PORT,  BTN_ESC_PIN,  BTN_ESC_PRESSED, DEL_BTN_MAX,
	 EV_SYS_ESC, EV_SYS_NONE},

	 {ID_SW_SETUP,  SW_SETUP_PORT,  SW_SETUP_PIN,  SW_SETUP_PRESSED, DEL_BTN_MAX,
		EV_SYS_NORMAL, EV_SYS_SETUP},

		{ID_BARRERA,  BARRERA_PORT,  BARRERA_PIN,  BARRERA_PRESSED, DEL_BTN_MAX,
		EV_SYS_NONE, EV_SYS_ENTREGADO},

		{ID_BTN_MONEDA,  BTN_MONEDA_PORT,  BTN_MONEDA_PIN,  BTN_MONEDA_PRESSED, DEL_BTN_MAX,
			EV_SYS_MONEDA, EV_SYS_NONE},


};



task_sensor_dta_t task_sensor_dta_list[SENSOR_DTA_QTY];

/********************** internal functions declaration ***********************/
void task_sensor_statechart(uint32_t index);

/********************** internal data definition *****************************/
const char *p_task_sensor 		= "Task Sensor (Sensor Statechart)";
const char *p_task_sensor_ 		= "Non-Blocking Code";
const char *p_task_sensor__ 	= "(Update by Time Code, period = 1mS)";

/********************** external data declaration ****************************/

/********************** external functions definition ************************/
void task_sensor_init(void *parameters)
{
	uint32_t index;
	task_sensor_dta_t *p_task_sensor_dta;
	task_sensor_st_t state;
	task_sensor_ev_t event;

	/* Print out: Task Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - Tick [mS] = %lu", GET_NAME(task_sensor_init), HAL_GetTick());
	LOGGER_INFO("   %s is a %s", GET_NAME(task_sensor), p_task_sensor);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_sensor), p_task_sensor_);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_sensor), p_task_sensor__);

	for (index = 0; SENSOR_DTA_QTY > index; index++)
	{
		/* Update Task Sensor Data Pointer */
		p_task_sensor_dta = &task_sensor_dta_list[index];

		/* Init & Print out: Index & Task execution FSM */
		state = ST_BTN_UP;
		p_task_sensor_dta->state = state;

		event = EV_BTN_UP;
		p_task_sensor_dta->event = event;

		p_task_sensor_dta->tick=0;

		LOGGER_INFO(" ");
		LOGGER_INFO("   %s = %lu   %s = %lu   %s = %lu",
				    GET_NAME(index), index,
					GET_NAME(state), (uint32_t)state,
					GET_NAME(event), (uint32_t)event);
	}
}

void task_sensor_update(void *parameters)
{
	uint32_t index;

	for (index = 0; SENSOR_DTA_QTY > index; index++)
	{
		/* Run Task Statechart */
		task_sensor_statechart(index);
	}
}

void task_sensor_statechart(uint32_t index)
{
	const task_sensor_cfg_t *p_task_sensor_cfg;
	task_sensor_dta_t *p_task_sensor_dta;

	/* Update Task Sensor Configuration & Data Pointer */
	p_task_sensor_cfg = &task_sensor_cfg_list[index];
	p_task_sensor_dta = &task_sensor_dta_list[index];


	if (p_task_sensor_cfg->pressed == HAL_GPIO_ReadPin(p_task_sensor_cfg->gpio_port, p_task_sensor_cfg->pin))
	{
		p_task_sensor_dta->event =	EV_BTN_DOWN;
	}
	else
	{
		p_task_sensor_dta->event =	EV_BTN_UP;
	}

	switch (p_task_sensor_dta->state)
	{

		case ST_BTN_UP:

			if (EV_BTN_DOWN == p_task_sensor_dta->event)
			{
				p_task_sensor_dta->tick=DEL_BTN_MAX;
				p_task_sensor_dta->state = ST_BTN_FALLING;
			}
			break;

		case ST_BTN_FALLING:

			if ((EV_BTN_UP == p_task_sensor_dta->event) && (p_task_sensor_dta->tick == 0))
			{

				p_task_sensor_dta->state = ST_BTN_UP;
			}

			if (p_task_sensor_dta->tick>0)
			{
				p_task_sensor_dta->tick--;
			}

			if ((EV_BTN_DOWN == p_task_sensor_dta->event) && (p_task_sensor_dta->tick == 0))
			{
				put_event_task_system(p_task_sensor_cfg->signal_pressed);
				p_task_sensor_dta->state = ST_BTN_DOWN;
			}

			break;

		case ST_BTN_DOWN:

			if (EV_BTN_UP == p_task_sensor_dta->event)
			{
				p_task_sensor_dta->tick=DEL_BTN_MAX;
				p_task_sensor_dta->state = ST_BTN_RAISING;
			}

			break;

		case ST_BTN_RAISING:

			if ((EV_BTN_UP == p_task_sensor_dta->event) && (p_task_sensor_dta->tick == 0))
			{
				put_event_task_system(p_task_sensor_cfg->signal_released);
				p_task_sensor_dta->state = ST_BTN_UP;
			}

			if (p_task_sensor_dta->tick>0)
			{
				p_task_sensor_dta->tick--;
				//p_task_sensor_dta->state = ST_BTN_RAISING;
			}

			if ((EV_BTN_DOWN == p_task_sensor_dta->event) && (p_task_sensor_dta->tick == 0))
			{
				p_task_sensor_dta->state = ST_BTN_DOWN;
			}

			break;

		default:

			p_task_sensor_dta->tick  = DEL_BTN_MIN;
			p_task_sensor_dta->state = ST_BTN_UP;
			p_task_sensor_dta->event = EV_BTN_UP;

			break;
	}
}

/********************** end of file ******************************************/
