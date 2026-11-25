

/********************** inclusions *******************************************/
/* Project includes */

#include "main.h"
#include <string.h>
/* Demo includes */
#include "logger.h"
#include "dwt.h"


/* Application & Tasks includes */
#include "board.h"
#include "app.h"
#include "task_actuator_memoria_attribute.h"
#include "task_actuator_memoria_interface.h"
/********************** macros and definitions *******************************/

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data declaration ****************************/

void cargar_config(uint16_t n)
{
	task_actuator_memoria_dta_list[0].largo = n;
	task_actuator_memoria_dta_list[0].event = EV_MEM_LEER;
	task_actuator_memoria_dta_list[0].flag  = true;
}

bool config_lista(void *dst, uint16_t n){
	if ( task_actuator_memoria_dta_list[0].flag_lectura_lista == true ){
		memcpy(dst, task_actuator_memoria_dta_list[0].buffer, n);
		task_actuator_memoria_dta_list[0].flag_lectura_lista = false;
		return true;
	} else
	{
		return false;
	}
}

bool guardar_config(const void *p, uint16_t n){
	if( task_actuator_memoria_dta_list[0].flag_ocupado == true ) {
		return false;
	} else
	{
		memcpy( task_actuator_memoria_dta_list[0].buffer, p, n );
		task_actuator_memoria_dta_list[0].largo = n;
		task_actuator_memoria_dta_list[0].event = EV_MEM_ESCRIBIR;
		task_actuator_memoria_dta_list[0].flag  = true;
	}

}

/********************** external functions definition ************************/

/********************** end of file ******************************************/
