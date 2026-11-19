
/********************** inclusions *******************************************/
/* Project includes */
#include "main.h"
#include <string.h>
#include <stdio.h>

/* Demo includes */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes */
#include "board.h"
#include "app.h"
#include "task_actuator_display_attribute.h"
#include "task_actuator_display_interface.h"
#include "display.h"

/********************** macros and definitions *******************************/
#define DEL_DSP_MIN				0ul
#define DEL_DSP_MED				50ul
#define DEL_DSP_MAX				500ul

/********************** internal data declaration ****************************/
task_actuator_display_dta_t task_actuator_display_dta;

/********************** internal functions declaration ***********************/
void task_actuator_display_statechart(void);

/********************** internal data definition *****************************/
const char *p_task_actuator_display		= "Task Display (Display Statechart)";
const char *p_task_actuator_display_		= "Non-Blocking Code";
const char *p_task_actuator_display__	= "(Update by Time Code, period = 1mS)";

/********************** external data declaration ****************************/

/********************** external functions definition ************************/
void task_actuator_display_init(void *parameters)
{
	task_actuator_display_dta_t 	*p_task_actuator_display_dta;
	task_actuator_display_st_t	state;
	task_actuator_display_ev_t	event;
	bool b_event;

	/* Print out: Task Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - Tick [mS] = %lu", GET_NAME(task_actuator_display_init), HAL_GetTick());
	LOGGER_INFO("   %s is a %s", GET_NAME(task_actuator_display), p_task_actuator_display);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_actuator_display), p_task_actuator_display_);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_actuator_display), p_task_actuator_display__);

	/* Update Task Display Data Pointer */
	p_task_actuator_display_dta = &task_actuator_display_dta;

	/* Init & Print out: Task execution FSM */
	state = ST_DSP_IDLE;
	p_task_actuator_display_dta->state = state;

	event = EV_DSP_IDLE;
	p_task_actuator_display_dta->event = event;

	b_event = false;
	p_task_actuator_display_dta->flag = b_event;

	LOGGER_INFO(" ");
	LOGGER_INFO("   %s = %lu   %s = %lu   %s = %s",
				GET_NAME(state), (uint32_t)state,
				GET_NAME(event), (uint32_t)event,
				GET_NAME(b_event), (b_event ? "true" : "false"));

	/* Init & Print out: LCD Display */

	displayInit( DISPLAY_CONNECTION_GPIO_4BITS );
	displayCharPositionWrite(0, 0);

    p_task_actuator_display_dta->row = 0;
	displayStringWrite(p_task_actuator_display_dta->ddram[p_task_actuator_display_dta->row]);

    displayCharPositionWrite(0, 1);
	p_task_actuator_display_dta->row = 1;
	displayStringWrite(p_task_actuator_display_dta->ddram[p_task_actuator_display_dta->row]);
}

void task_actuator_display_update(void *parameters)
{
	/* Run Task Statechart */
	task_actuator_display_statechart();
}

void task_actuator_display_statechart(void)
{
	task_actuator_display_dta_t *p_task_actuator_display_dta;

	/* Update Task Display Data Pointer */
	p_task_actuator_display_dta = &task_actuator_display_dta;

	switch (p_task_actuator_display_dta->state)
	{
		case ST_DSP_IDLE:

			if ((true == p_task_actuator_display_dta->flag) && (EV_DSP_UPDATE == p_task_actuator_display_dta->event))
			{
				p_task_actuator_display_dta->state = ST_DSP_UPDATE;
				p_task_actuator_display_dta->row = 0;
				p_task_actuator_display_dta->column = 0;
			}

			break;

		case ST_DSP_UPDATE:

			if ((true == p_task_actuator_display_dta->flag) && (EV_DSP_UPDATE == p_task_actuator_display_dta->event))
			{
				p_task_actuator_display_dta->flag = false;
				p_task_actuator_display_dta->state = ST_DSP_UPDATE;
				p_task_actuator_display_dta->row = 0;
				p_task_actuator_display_dta->column = 0;

				displayCharPositionWrite(p_task_actuator_display_dta->column, p_task_actuator_display_dta->row);
			}
			else
			{
				if (COLUMNS > p_task_actuator_display_dta->column)
				{
					p_task_actuator_display_dta->character = p_task_actuator_display_dta->ddram[p_task_actuator_display_dta->row][p_task_actuator_display_dta->column++];
					displayDataWrite(p_task_actuator_display_dta->character);
				}
				else
					{
					p_task_actuator_display_dta->row++;
					if (ROWS > p_task_actuator_display_dta->row)
					{
						p_task_actuator_display_dta->column = 0;
						displayCharPositionWrite(p_task_actuator_display_dta->column, p_task_actuator_display_dta->row);
					}
					else
						p_task_actuator_display_dta->state = ST_DSP_IDLE;
					}
				}

			break;

		default:

			p_task_actuator_display_dta->tick  = DEL_DSP_MIN;
			p_task_actuator_display_dta->state = ST_DSP_IDLE;
			p_task_actuator_display_dta->event = EV_DSP_IDLE;
			p_task_actuator_display_dta->flag = false;

			break;
	}
}




static void task_actuator_display_pad_line(char *line)
{
	size_t len = strlen(line);

	/* Completa con espacios hasta COLUMNS para borrar restos del texto anterior */
	while (COLUMNS > len)
		line[len++] = ' ';
	line[COLUMNS] = '\0';
}

void task_actuator_display_setup(task_actuator_display_dta_t *p_dta)
{
	char line0[COLUMNS + 1];
	char line1[COLUMNS + 1];


	switch (p_dta->pantalla)
	{
		case PANTALLA_ESPERA:
				snprintf(line0, sizeof(line0), "NORMAL");
				snprintf(line1, sizeof(line1), "Espera");
				break;

		case PANTALLA_SELECCION:
	    	snprintf(line0, sizeof(line0), "Canal %u  $%4lu,%02lu",
	             (unsigned)(p_dta->valores.seleccion + 1),
	             (unsigned long)(p_dta->valores.precio_cv / 100),
	             (unsigned long)(p_dta->valores.precio_cv % 100));
			snprintf(line1, sizeof(line1), "Credito  $%4lu,%02lu",
	             (unsigned long)(p_dta->valores.credito_cv / 100),
	             (unsigned long)(p_dta->valores.credito_cv % 100));
			break;

		case PANTALLA_ENTREGANDO:
			snprintf(line0, sizeof(line0), "NORMAL");
			snprintf(line1, sizeof(line1), "Entregando");
			break;

		case PANTALLA_SIN_STOCK_SIN_CREDITO:
			snprintf(line0, sizeof(line0), "NORMAL");
			snprintf(line1, sizeof(line1), "Sin Stock");
			break;

		case PANTALLA_FALLA_TEMPERATURA:
			snprintf(line0, sizeof(line0), "FALLA");
			snprintf(line1, sizeof(line1), "Temperatura");
			break;

		case PANTALLA_FALLA_ATASCO:
			snprintf(line0, sizeof(line0), "FALLA");
			snprintf(line1, sizeof(line1), "Atasco");
			break;

		case PANTALLA_SETUP_MAIN:
			snprintf(line0, sizeof(line0), "SETUP");
			snprintf(line1, sizeof(line1), "MAIN");
			break;

		case PANTALLA_SETUP_MENU1:
			snprintf(line0, sizeof(line0), "SETUP");
			snprintf(line1, sizeof(line1), "MENU1");
			break;

		case PANTALLA_SETUP_MENU2:
			snprintf(line0, sizeof(line0), "SETUP");
			snprintf(line1, sizeof(line1), "MENU2");
			break;

		case PANTALLA_SETUP_MENU3:
			snprintf(line0, sizeof(line0), "SETUP");
			snprintf(line1, sizeof(line1), "MENU3");
			break;

		default:
			return;
	}

	task_actuator_display_pad_line(line0);
	task_actuator_display_pad_line(line1);

	put_event_task_actuator_display(0, 0, line0);
	put_event_task_actuator_display(0, 1, line1);
}



/********************** end of file ******************************************/
