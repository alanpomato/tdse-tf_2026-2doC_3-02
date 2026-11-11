

/********************** inclusions *******************************************/
/* Project includes */
#include "main.h"

/* Demo includes */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes */
#include "board.h"
#include "app_it.h"
#include "task_system.h"
#include "task_actuator.h"

#include "task_sensor_btn.h"
#include "task_sensor_adc.h"


/********************** macros and definitions *******************************/
#define TASK_X_NOE_INI		0ul
#define TASK_X_LET_INI		0ul
#define TASK_X_BCET_INI		1000ul
#define TASK_X_WCET_INI		0ul
#define TASK_X_DELAY_MIN	0ul

typedef struct {
	void (*task_init)(void *);		// Pointer to task (must be a
									// 'void (void *)' function)
	void (*task_update)(void *);	// Pointer to task (must be a
									// 'void (void *)' function)
	void *parameters;				// Pointer to parameters
} task_cfg_t;

typedef struct {
    uint32_t NOE;		// Number of execution (numeral)
    uint32_t LET;		// Last execution time (microseconds)
    uint32_t BCET;		// Best-case execution time (microseconds)
    uint32_t WCET;		// Worst-case execution time (microseconds)
} task_dta_t;

/********************** internal data declaration ****************************/
const task_cfg_t task_cfg_list[]	= {
		{task_sensor_btn_init, 		task_sensor_btn_update, 	NULL},
		{task_sensor_adc_init, 		task_sensor_adc_update, 	NULL},
		{task_system_init, 		task_system_update, 	NULL},
		{task_actuator_init,	task_actuator_update, 	NULL}
};

#define TASK_QTY	(sizeof(task_cfg_list)/sizeof(task_cfg_t))

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
const char *p_app	= "Bare Metal - Event-Triggered Systems (ETS)";
const char *p_app_	= "App - Model Integration - C codig";
const char *p_app__	= "(Update by Time Code, period = 1mS)";

/********************** external data declaration ****************************/
uint32_t g_app_cnt;
uint32_t g_app_runtime_us;

task_dta_t task_dta_list[TASK_QTY];

/********************** external functions definition ************************/
void app_init(void)
{
	uint32_t index;

	/* Print out: Application Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("%s is running - Tick [mS] = %lu", GET_NAME(app_init), HAL_GetTick());

	LOGGER_INFO(" %s is a %s", GET_NAME(app), p_app);
	LOGGER_INFO(" %s is a %s", GET_NAME(app), p_app_);
	LOGGER_INFO(" %s is a %s", GET_NAME(app), p_app__);

	/* Init & Print out: Application execution counter */
	g_app_cnt = ZERO;
	LOGGER_INFO(" %s = %lu", GET_NAME(g_app_cnt), g_app_cnt);

	/* Init Cycle Counter */
	cycle_counter_init();

    /* Go through the task arrays */
	for (index = 0; TASK_QTY > index; index++)
	{
		/* Run task_x_init */
		(*task_cfg_list[index].task_init)(task_cfg_list[index].parameters);

		/* Init variables */
		task_dta_list[index].NOE = TASK_X_NOE_INI;
		task_dta_list[index].LET = TASK_X_LET_INI;
		task_dta_list[index].BCET = TASK_X_BCET_INI;
		task_dta_list[index].WCET = TASK_X_WCET_INI;
	}

  	/* Application Interrupts Init */
	app_it_init();
}

void app_update(void)
{
	uint32_t index;
	bool b_time_update_required = false;

	/* Protect shared resource */
	__asm("CPSID i");	/* disable interrupts */
    if (ZERO < g_app_tick_cnt)
    {
		/* Update Tick Counter */
    	g_app_tick_cnt--;
    	b_time_update_required = true;
    }
    __asm("CPSIE i");	/* enable interrupts */

	/* Check if it's time to run tasks */
    while (b_time_update_required)
    {
    	/* Update App Counter */
    	g_app_cnt++;
    	g_app_runtime_us = 0;

		/* Go through the task arrays */
		for (index = 0; TASK_QTY > index; index++)
		{
			cycle_counter_reset();

    		/* Run task_x_update */
			(*task_cfg_list[index].task_update)(task_cfg_list[index].parameters);

			/* Update variables */
			task_dta_list[index].NOE++;

			task_dta_list[index].LET = cycle_counter_get_time_us();

			if (task_dta_list[index].BCET > task_dta_list[index].LET)
			{
				task_dta_list[index].BCET = task_dta_list[index].LET;
			}

			if (task_dta_list[index].WCET < task_dta_list[index].LET)
			{
				task_dta_list[index].WCET = task_dta_list[index].LET;
			}

			g_app_runtime_us += task_dta_list[index].LET;
		}
//		HAL_PWR_EnterSLEEPMode(0, PWR_SLEEPENTRY_WFI);

		/* Protect shared resource */
		__asm("CPSID i");	/* disable interrupts */
		if (ZERO < g_app_tick_cnt)
		{
			/* Update Tick Counter */
			g_app_tick_cnt--;
			b_time_update_required = true;
		}
		else
		{
			b_time_update_required = false;
		}
		__asm("CPSIE i");	/* enable interrupts */
	}
}

/********************** end of file ******************************************/
