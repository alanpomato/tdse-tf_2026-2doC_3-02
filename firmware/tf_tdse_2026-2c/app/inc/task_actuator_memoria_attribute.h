

#ifndef TASK_ACTUATOR_MEMORIA_ATTRIBUTE_H_
#define TASK_ACTUATOR_MEMORIA_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include <stdint.h>
#include <stdbool.h>
/********************** macros ***********************************************/

/********************** typedef **********************************************/
/* Events to excite Task Actuator */
typedef enum task_actuator_memoria_ev {EV_MEM_LEER,
							EV_MEM_ESCRIBIR
} task_actuator_memoria_ev_t;

/* States of Task Actuator */
typedef enum task_actuator_memoria_st {ST_MEM_IDLE,
								ST_MEM_LEYENDO,
								ST_MEM_ESCRIBIENDO,
								ST_MEM_GRABANDO
} task_actuator_memoria_st_t;


typedef struct
{
	uint16_t			dir_i2c;
	uint16_t			dir_base;

} task_actuator_memoria_cfg_t;

typedef struct
{
	uint32_t			tick;
	task_actuator_memoria_st_t	state;
	task_actuator_memoria_ev_t	event;
	bool				flag_ocupado;
	bool					flag;
	bool				flag_lectura_lista;
	uint8_t 			buffer[64];
	uint16_t 			largo;
	volatile bool 				tx_done;
	volatile bool 				rx_done;

} task_actuator_memoria_dta_t;

/********************** external data declaration ****************************/
extern task_actuator_memoria_dta_t task_actuator_memoria_dta_list[];

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_ACTUATOR_ATTRIBUTE_H_ */

/********************** end of file ******************************************/
