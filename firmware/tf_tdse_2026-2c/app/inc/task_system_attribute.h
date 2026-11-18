

#ifndef TASK_SYSTEM_ATTRIBUTE_H_
#define TASK_SYSTEM_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include <stdbool.h>
#include <stdint.h>

/********************** macros ***********************************************/
#define Q_CANALES 3
/********************** typedef **********************************************/
/* Events to excite Task System */
typedef enum task_system_ev {EV_SYS_ENTER,
							EV_SYS_NEXT,
							EV_SYS_ESC,
							EV_SYS_SETUP,
							EV_SYS_NORMAL,
							EV_SYS_NONE,
							EV_SYS_ENTREGADO,
							EV_SYS_MONEDA} task_system_ev_t; //

/* State of Task System */
typedef enum task_system_st {ST_SYS_ESPERA,
							ST_SYS_SELECCION,
							ST_SYS_ENTREGANDO,
							ST_SYS_SIN_STOCK_FALTA_CREDITO,
							ST_SYS_TEMPERATURA,
							ST_SYS_ATASCO
							} task_system_st_t;

typedef struct
{
	uint32_t	precio_cv; // en centavos
	uint32_t	stock;
} canal_t;

typedef struct
{
	canal_t				canales[Q_CANALES];
	uint32_t			credito;
	uint16_t			seleccion;
	uint32_t			recaudado;
	uint32_t			q_ventas;
	uint32_t			tick;
	task_system_st_t	state;
	task_system_ev_t	event;
	bool				flag;
} task_system_dta_t;

/********************** external data declaration ****************************/
extern task_system_dta_t task_system_dta_list[];

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_SYSTEM_ATTRIBUTE_H_ */

/********************** end of file ******************************************/
