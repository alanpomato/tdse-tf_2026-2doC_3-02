
#ifndef TASK_ACTUATOR_DISPLAY_ATTRIBUTE_H_
#define TASK_ACTUATOR_DISPLAY_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include <stdbool.h>
#include <stdint.h>
/********************** macros ***********************************************/

/********************** typedef **********************************************/
/* Display Data RAM */
#define ROWS 	2
#define COLUMNS 16

/* Events to excite Task Display */
typedef enum task_actuator_display_ev {EV_DSP_IDLE,
							  	  EV_DSP_UPDATE} task_actuator_display_ev_t;

/* State of Task Display */
typedef enum task_actuator_display_st {ST_DSP_IDLE,
							  	  ST_DSP_UPDATE} task_actuator_display_st_t;

typedef enum { PANTALLA_ESPERA,
				PANTALLA_SELECCION,
				PANTALLA_ENTREGANDO,
				PANTALLA_SIN_STOCK_SIN_CREDITO,
				PANTALLA_FALLA_TEMPERATURA,
				PANTALLA_FALLA_ATASCO,
				PANTALLA_SETUP_MAIN,
				PANTALLA_SETUP_MENU1,
				PANTALLA_SETUP_MENU2,
				PANTALLA_SETUP_MENU3,
				PANTALLA_CARGANDO
} pantalla_t;

typedef struct
{
	uint32_t			precio_cv;
	uint16_t			seleccion;
	uint32_t			credito_cv;
	uint32_t			parametro;
	uint32_t			stock;
	uint16_t			temperatura;
}display_valores_t;



typedef struct
{
	uint32_t			tick;
	task_actuator_display_st_t	state;
	task_actuator_display_ev_t	event;
	bool				flag;
	char 				ddram[ROWS][COLUMNS+1];
	uint32_t			row;
	uint32_t			column;
	char				character;
	pantalla_t 				pantalla;
	display_valores_t 	valores;
} task_actuator_display_dta_t;

/********************** external data declaration ****************************/
extern task_actuator_display_dta_t task_actuator_display_dta;

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_DISPLAY_ATTRIBUTE_H_ */

/********************** end of file ******************************************/
