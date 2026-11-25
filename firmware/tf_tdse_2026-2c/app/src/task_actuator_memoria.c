

/********************** inclusions *******************************************/
/* Project includes */
#include "main.h"

/* Demo includes */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes */
#include "board.h"
#include "app.h"
#include "task_actuator_memoria_attribute.h"
#include "task_actuator_memoria.h"
#include "eeprom.h"

/********************** macros and definitions *******************************/
#define ACTUATOR_MEMORIA_DTA_QTY 1
#define DEL_MEMORIA 5

/********************** internal data declaration ****************************/
const task_actuator_memoria_cfg_t task_actuator_memoria_cfg_list[] = {
		{EEPROM_DIR_I2C, EEPROM_DIR_BASE},
};

task_actuator_memoria_dta_t task_actuator_memoria_dta_list[ACTUATOR_MEMORIA_DTA_QTY];

/********************** internal functions declaration ***********************/
void task_actuator_memoria_statechart(uint32_t index);

/********************** internal data definition *****************************/
const char *p_task_actuator_memoria 		= "Task Actuator Memoria (Actuator Statechart)";
const char *p_task_actuator_memoria_ 		= "Non-Blocking Code";
const char *p_task_actuator_memoria__ 		= "(Update by Time Code, period = 1mS)";

/********************** external data declaration ****************************/

/********************** external functions definition ************************/
void task_actuator_memoria_init(void *parameters)
{
	uint32_t index;
	const task_actuator_memoria_cfg_t *p_task_actuator_memoria_cfg;
	task_actuator_memoria_dta_t *p_task_actuator_memoria_dta;

	/* Print out: Task Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - Tick [mS] = %lu", GET_NAME(task_actuator_init), HAL_GetTick());
	LOGGER_INFO("   %s is a %s", GET_NAME(task_actuator), p_task_actuator_memoria);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_actuator), p_task_actuator_memoria_);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_actuator), p_task_actuator_memoria__);

	for (index = 0; ACTUATOR_MEMORIA_DTA_QTY > index; index++)
	{
		/* Update Task Actuator Configuration & Data Pointer */
		p_task_actuator_memoria_cfg = &task_actuator_memoria_cfg_list[index];
		p_task_actuator_memoria_dta = &task_actuator_memoria_dta_list[index];

		/* Init & Print out: Index & Task execution FSM */
		p_task_actuator_memoria_dta->state = ST_MEM_IDLE;
		p_task_actuator_memoria_dta->event = EV_MEM_LEER;
		p_task_actuator_memoria_dta->flag = false;
		p_task_actuator_memoria_dta->flag_ocupado = false;
		p_task_actuator_memoria_dta->flag_lectura_lista = false;
		p_task_actuator_memoria_dta->tick = 0;


	}
}

void task_actuator_memoria_update(void *parameters)
{
	uint32_t index;

	for (index = 0; ACTUATOR_MEMORIA_DTA_QTY > index; index++)
	{
		/* Run Task Statechart */
		task_actuator_memoria_statechart(index);
	}
}

void task_actuator_memoria_statechart(uint32_t index)
{
	const task_actuator_memoria_cfg_t *p_task_actuator_memoria_cfg;
	task_actuator_memoria_dta_t *p_task_actuator_memoria_dta;

	/* Update Task Actuator Configuration & Data Pointer */
	p_task_actuator_memoria_cfg = &task_actuator_memoria_cfg_list[index];
	p_task_actuator_memoria_dta = &task_actuator_memoria_dta_list[index];

	switch (p_task_actuator_memoria_dta->state)
	{
		case ST_MEM_IDLE:
			if (p_task_actuator_memoria_dta->event == EV_MEM_LEER && p_task_actuator_memoria_dta->flag){
				p_task_actuator_memoria_dta->rx_done = false;
				eeprom_read_it (p_task_actuator_memoria_cfg->dir_base, p_task_actuator_memoria_dta->buffer, p_task_actuator_memoria_dta->largo); // arranco a leer
				p_task_actuator_memoria_dta->state = ST_MEM_LEYENDO;
				p_task_actuator_memoria_dta->flag_lectura_lista = false;
				p_task_actuator_memoria_dta->flag_ocupado = true;
			} else
			if (p_task_actuator_memoria_dta->event == EV_MEM_ESCRIBIR && p_task_actuator_memoria_dta->flag){
				p_task_actuator_memoria_dta->tx_done = false;
				eeprom_write_it(p_task_actuator_memoria_cfg->dir_base, p_task_actuator_memoria_dta->buffer, p_task_actuator_memoria_dta->largo); // arranco a escribir.
				p_task_actuator_memoria_dta->state = ST_MEM_ESCRIBIENDO;
				p_task_actuator_memoria_dta->flag_ocupado = true;
			}

			break;

		case ST_MEM_LEYENDO:
			if ( p_task_actuator_memoria_dta->rx_done == true ){
				p_task_actuator_memoria_dta->flag_lectura_lista = true;
				p_task_actuator_memoria_dta->flag_ocupado = false;
				p_task_actuator_memoria_dta->state = ST_MEM_IDLE;

			}

			break;

		case ST_MEM_ESCRIBIENDO:
			if ( p_task_actuator_memoria_dta->tx_done == true ){
				p_task_actuator_memoria_dta->tick = DEL_MEMORIA;
				p_task_actuator_memoria_dta->state = ST_MEM_GRABANDO;

			}

			break;

		case ST_MEM_GRABANDO:
			p_task_actuator_memoria_dta->tick--;

			if ( p_task_actuator_memoria_dta->tick == 0 ){
				p_task_actuator_memoria_dta->state = ST_MEM_IDLE; // terminó de grabar (x tiempo)
				p_task_actuator_memoria_dta->flag_ocupado = false;
			}

			break;


		default:

			p_task_actuator_memoria_dta->state = ST_MEM_IDLE;
			p_task_actuator_memoria_dta->event = EV_MEM_LEER;
			p_task_actuator_memoria_dta->flag = false;

			break;
	}
	p_task_actuator_memoria_dta->flag = false;
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (hi2c->Instance == I2C1)
	{
		task_actuator_memoria_dta_list[0].tx_done = true;
	}
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (hi2c->Instance == I2C1)
	{
		task_actuator_memoria_dta_list[0].rx_done = true;
	}
}
/********************** end of file ******************************************/
