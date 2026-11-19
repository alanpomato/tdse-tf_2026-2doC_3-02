

/********************** inclusions *******************************************/
/* Project includes */
#include "main.h"

/* Demo includes */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes */
#include "board.h"
#include "app.h"
#include "task_actuator_gpio_interface.h"

#include "task_actuator_pwm_interface.h"
#include "task_actuator_display_interface.h"

#include "task_system_attribute.h"
#include "task_system_interface.h"
#include "task_system.h"

#include "task_sensor_adc_interface.h"

/********************** macros and definitions *******************************/
// DUMMYS PARA PROBAR
#define PRECIO1 50000
#define PRECIO2 100000
#define PRECIO3 150000
#define STOCK1 1
#define STOCK2 5
#define STOCK3 10

// ************************************************

#define DEL_SYS_MIN			0ul
#define DEL_SYS_MED			250ul
#define DEL_SYS_MAX			500ul

#define TEMP_MAX 30

#define DEL_SELECCION 30000ul
#define DEL_ENTREGANDO 15000ul
#define DEL_SIN_STOCK_FALTA_CREDITO 10000ul
#define VAL_MONEDA 50000 // Centavos
#define SALTO_PRECIO 50000 // Centavos
#define TOPE_PRECIO 1000000
#define MAX_STOCK 10

/* Modes to excite Task System */
typedef enum task_system_mode {NORMAL, SETUP, FALLA} task_system_mode_t;

#define SYSTEM_DTA_QTY	1

/********************** internal data declaration ****************************/
task_system_dta_t task_system_dta_list[SYSTEM_DTA_QTY];

/********************** internal functions declaration ***********************/
void task_system_normal_statechart(void);
void task_system_falla_statechart(void);
void task_system_setup_statechart(void);
void entrar_falla( task_system_dta_t*, task_system_st_t);
void entrar_normal( task_system_dta_t* , task_system_st_t );
void entrar_setup( task_system_dta_t* , task_system_st_t );
void task_system_set_mode(task_system_mode_t);
void armar_valores(task_system_dta_t*, display_valores_t*);

/********************** internal data definition *****************************/
const char *p_task_system 		= "Task System (System Statechart)";
const char *p_task_system_ 		= "Non-Blocking Code";
const char *p_task_system__ 	= "(Update by Time Code, period = 1mS)";

/********************** external data declaration ****************************/
task_system_mode_t g_task_system_mode;

/********************** external functions definition ************************/
void task_system_init(void *parameters)
{
	uint32_t index;
	task_system_dta_t 	*p_task_system_dta;
	task_system_st_t	state;
	task_system_ev_t	event;
	bool b_event;

	/* Print out: Task Initialized */
	LOGGER_INFO(" ");
	LOGGER_INFO("  %s is running - Tick [mS] = %lu", GET_NAME(task_system_init), HAL_GetTick());
	LOGGER_INFO("   %s is a %s", GET_NAME(task_system), p_task_system);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_system), p_task_system_);
	LOGGER_INFO("   %s is a %s", GET_NAME(task_system), p_task_system__);

	init_event_task_system();

	task_system_set_mode(NORMAL);

	for (index = 0; SYSTEM_DTA_QTY > index; index++)
	{
		/* Update Task System Data Pointer */
		p_task_system_dta = &task_system_dta_list[index];

		/* Init & Print out: Task execution FSM */
		state = ST_SYS_ESPERA;
		p_task_system_dta->state = state;

		event = EV_SYS_NORMAL; // Indistinto total está la flag en false.
		p_task_system_dta->event = event;

		b_event = false;
		p_task_system_dta->flag = b_event;

		LOGGER_INFO(" ");
		LOGGER_INFO("   %s = %lu   %s = %lu   %s = %s",
					GET_NAME(state), (uint32_t)state,
					GET_NAME(event), (uint32_t)event,
					GET_NAME(b_event), (b_event ? "true" : "false"));
	}


	p_task_system_dta->canales[0].precio_cv = PRECIO1;  p_task_system_dta->canales[0].stock = STOCK1;
	p_task_system_dta->canales[1].precio_cv = PRECIO2;  p_task_system_dta->canales[1].stock = STOCK2;
	p_task_system_dta->canales[2].precio_cv = PRECIO3;  p_task_system_dta->canales[2].stock = STOCK3;
	p_task_system_dta->credito   = 0;
	p_task_system_dta->seleccion = 0;
	p_task_system_dta->recaudado = 0;
	p_task_system_dta->q_ventas  = 0;
	p_task_system_dta->tick      = 0;



	task_system_set_mode(NORMAL);


}

void task_system_update(void *parameters)
{
	/* Run Task Statechart */
	switch (g_task_system_mode)
	{
		case NORMAL:

			task_system_normal_statechart();

			break;

		case SETUP:

			task_system_setup_statechart();

			break;

		case FALLA:

			task_system_falla_statechart();

			break;

		default:

			task_system_set_mode(NORMAL);

			break;
		}
}

void task_system_normal_statechart(void)
{
	task_system_dta_t *p_task_system_dta;
	display_valores_t v;
	static bool primer_acceso = true;
	uint32_t t;
	/* Update Task System Data Pointer */
	p_task_system_dta = &task_system_dta_list[0];

	//Primer acceso
	if (primer_acceso == true){
		entrar_normal(p_task_system_dta, ST_SYS_ESPERA);
	}
	primer_acceso = false;

	if (true == any_event_task_system())
	{
		p_task_system_dta->flag = true;
		p_task_system_dta->event = get_event_task_system();
	}


	if (p_task_system_dta->flag && p_task_system_dta->event == EV_SYS_MONEDA)
	{
	    p_task_system_dta->credito += VAL_MONEDA;
	    armar_valores(p_task_system_dta, &v);
	    switch (p_task_system_dta->state)
	    {
	        case ST_SYS_ESPERA:
	        	set_display(PANTALLA_ESPERA, v);    break;
	        case ST_SYS_SELECCION:
	        	set_display(PANTALLA_SELECCION, v); break;
	        default: break;
	    }
	}



	switch (p_task_system_dta->state)
	{

		case ST_SYS_ESPERA:


			if ( p_task_system_dta->event == EV_SYS_NEXT && p_task_system_dta->flag == true ){
				p_task_system_dta->state = ST_SYS_SELECCION;
				p_task_system_dta->tick = DEL_SELECCION;
				armar_valores(p_task_system_dta, &v);
				set_display(PANTALLA_SELECCION, v);
			} else
			if ( p_task_system_dta->event == EV_SYS_SETUP && p_task_system_dta->flag == true ){
				entrar_setup(p_task_system_dta, ST_SYS_MAIN);

			}
			break;


		case ST_SYS_SELECCION:
			p_task_system_dta->tick--;
			if ( p_task_system_dta->event == EV_SYS_NEXT && p_task_system_dta->flag == true ){
				p_task_system_dta->seleccion = ( p_task_system_dta->seleccion +1 ) % Q_CANALES;
				armar_valores(p_task_system_dta, &v);
				set_display(PANTALLA_SIN_STOCK_SIN_CREDITO, v);
			} else
			if ( ( p_task_system_dta->event == EV_SYS_ESC && p_task_system_dta->flag == true )|| p_task_system_dta->tick == 0 ){
				entrar_normal(p_task_system_dta, ST_SYS_ESPERA);
			} else
			if ( p_task_system_dta->event == EV_SYS_ENTER && p_task_system_dta->flag == true ){

				if ( p_task_system_dta->canales[p_task_system_dta->seleccion].stock > 0 && p_task_system_dta->canales[p_task_system_dta->seleccion].precio_cv <= p_task_system_dta->credito ){
					armar_valores(p_task_system_dta, &v);
					set_display(PANTALLA_ENTREGANDO, v);
					p_task_system_dta->state = ST_SYS_ENTREGANDO;
					put_event_task_actuator_pwm(EV_PWM_ON, (task_actuator_pwm_id_t)p_task_system_dta->seleccion);
					put_event_task_actuator_gpio(EV_BLINK, LED_STATUS);
					put_event_task_actuator_gpio(EV_BLINK, BUZZER);
					p_task_system_dta->tick = DEL_ENTREGANDO;
				} else {
					p_task_system_dta->state = ST_SYS_SIN_STOCK_FALTA_CREDITO;
					armar_valores(p_task_system_dta, &v);
					set_display(PANTALLA_SIN_STOCK_SIN_CREDITO, v);
					p_task_system_dta->tick = DEL_SIN_STOCK_FALTA_CREDITO;
				}
			}
			break;

		case ST_SYS_ENTREGANDO:
			p_task_system_dta->tick--;

			if ( p_task_system_dta->tick == 0 ){
				entrar_falla(p_task_system_dta, ST_SYS_ATASCO);
			} else
			if ( p_task_system_dta->event == EV_SYS_ENTREGADO && p_task_system_dta->flag == true ){
				p_task_system_dta->canales[p_task_system_dta->seleccion].stock--;
				p_task_system_dta->credito = p_task_system_dta->credito - p_task_system_dta->canales[p_task_system_dta->seleccion].precio_cv;
				p_task_system_dta->q_ventas++;
				p_task_system_dta->recaudado = p_task_system_dta->recaudado + p_task_system_dta->canales[p_task_system_dta->seleccion].precio_cv;
				entrar_normal(p_task_system_dta, ST_SYS_ESPERA);
			}
			break;



		case ST_SYS_SIN_STOCK_FALTA_CREDITO:
			p_task_system_dta->tick--;
			if ( p_task_system_dta->tick == 0 ){
				entrar_normal(p_task_system_dta, ST_SYS_ESPERA);
			}
			break;

		default:
			break;
	}

	p_task_system_dta->flag = false;
	if (get_temperatura(&t) && t > TEMP_MAX){
		entrar_falla(p_task_system_dta, ST_SYS_TEMPERATURA);
	}
}

void task_system_falla_statechart(void)
{
	task_system_dta_t *p_task_system_dta;
	uint32_t t;
	/* Update Task System Data Pointer */
	p_task_system_dta = &task_system_dta_list[0];



	if (true == any_event_task_system())
	{
		p_task_system_dta->flag = true;
		p_task_system_dta->event = get_event_task_system();
	}

	switch (p_task_system_dta->state)
	{

		case ST_SYS_TEMPERATURA:


			if ( get_temperatura(&t) && t < (TEMP_MAX - 2) ){
				entrar_normal(p_task_system_dta, ST_SYS_ESPERA);
			}
			break;


		case ST_SYS_ATASCO:
			if ( p_task_system_dta->event == EV_SYS_ESC && p_task_system_dta->flag == true ){
				entrar_normal(p_task_system_dta, ST_SYS_ESPERA);
			}
			break;


		default:

			break;
	}
	p_task_system_dta->flag = false;
}

void task_system_setup_statechart(void)
{
	task_system_dta_t *p_task_system_dta;
	display_valores_t v;
	/* Update Task System Data Pointer */
	p_task_system_dta = &task_system_dta_list[0];

	if (true == any_event_task_system())
	{
		p_task_system_dta->flag = true;
		p_task_system_dta->event = get_event_task_system();
	}

	if ( p_task_system_dta->event == EV_SYS_NORMAL && p_task_system_dta->flag == true ){
		entrar_normal(p_task_system_dta, ST_SYS_ESPERA);
	}


	switch (p_task_system_dta->state)
	{

		case ST_SYS_MAIN:

			if ( p_task_system_dta->event == EV_SYS_ENTER && p_task_system_dta->flag == true ){
				armar_valores(p_task_system_dta, &v);
				set_display(PANTALLA_SETUP_MENU1, v);
				p_task_system_dta->state = ST_SYS_MENU1;
			}

			break;

		case ST_SYS_MENU1:

			if ( p_task_system_dta->event == EV_SYS_ENTER && p_task_system_dta->flag == true ){
				armar_valores(p_task_system_dta, &v);
				set_display(PANTALLA_SETUP_MENU2, v);
				p_task_system_dta->state = ST_SYS_MENU2;
			} else
			if ( p_task_system_dta->event == EV_SYS_NEXT && p_task_system_dta->flag == true ){
				armar_valores(p_task_system_dta, &v);
				set_display(PANTALLA_SETUP_MENU1, v);
				p_task_system_dta->seleccion = (p_task_system_dta->seleccion+1) % Q_CANALES;
			} else
			if ( p_task_system_dta->event == EV_SYS_ESC && p_task_system_dta->flag == true ){
				armar_valores(p_task_system_dta, &v);
				set_display(PANTALLA_SETUP_MAIN, v);
				p_task_system_dta->state = ST_SYS_MAIN;
			}


			break;

		case ST_SYS_MENU2:
			if ( p_task_system_dta->event == EV_SYS_ENTER && p_task_system_dta->flag == true ){
				armar_valores(p_task_system_dta, &v);
				set_display(PANTALLA_SETUP_MENU3, v);
				p_task_system_dta->state = ST_SYS_MENU3;
			} else
			if ( p_task_system_dta->event == EV_SYS_NEXT && p_task_system_dta->flag == true ){
				armar_valores(p_task_system_dta, &v);
				set_display(PANTALLA_SETUP_MENU2, v);
				p_task_system_dta->parametro = (p_task_system_dta->parametro + 1) % PARAM_QTY;
			} else
			if ( p_task_system_dta->event == EV_SYS_ESC && p_task_system_dta->flag == true ){
				armar_valores(p_task_system_dta, &v);
				set_display(PANTALLA_SETUP_MENU1, v);
				p_task_system_dta->state = ST_SYS_MENU1;
			}

			break;

		case ST_SYS_MENU3:
			if ( p_task_system_dta->event == EV_SYS_NEXT  && p_task_system_dta->flag == true ){
				switch ( p_task_system_dta->parametro ){
					case PARAM_PRECIO:
						// Aumento Salto precio
						p_task_system_dta->canales[p_task_system_dta->seleccion].precio_cv = (p_task_system_dta->canales[p_task_system_dta->seleccion].precio_cv + SALTO_PRECIO) % TOPE_PRECIO ;
						break;
					case PARAM_STOCK:
						p_task_system_dta->canales[p_task_system_dta->seleccion].stock = (p_task_system_dta->canales[p_task_system_dta->seleccion].stock + 1) % (MAX_STOCK + 1);
						break;
					default: break;
				}
				armar_valores(p_task_system_dta, &v);
				set_display(PANTALLA_SETUP_MENU3, v);
			} else
			if ( (true == p_task_system_dta->flag) && (EV_SYS_ESC == p_task_system_dta->event) ){
				armar_valores(p_task_system_dta, &v);
				set_display(PANTALLA_SETUP_MENU2, v);
				p_task_system_dta->state = ST_SYS_MENU2;
			}
			break;
		default:

			break;
	}
	p_task_system_dta->flag = false;
}

void armar_valores(task_system_dta_t *p, display_valores_t *v){
    v->seleccion   = p->seleccion;
    v->precio_cv   = p->canales[p->seleccion].precio_cv;
    v->stock       = p->canales[p->seleccion].stock;
    v->credito_cv  = p->credito;
    v->parametro   = (uint32_t)p->parametro;
}

void entrar_setup( task_system_dta_t* p_task_system_dta, task_system_st_t task_system_st){
	display_valores_t v;

	p_task_system_dta->parametro = 0;
	put_event_task_actuator_gpio(EV_OFF,  LED_STATUS);
	put_event_task_actuator_gpio(EV_OFF, BUZZER);
	put_event_task_actuator_pwm(EV_PWM_OFF, (task_actuator_pwm_id_t)p_task_system_dta->seleccion);
	p_task_system_dta->state = task_system_st;
	if( p_task_system_dta->state == ST_SYS_MAIN ){
		armar_valores(p_task_system_dta, &v);
		set_display(PANTALLA_SETUP_MAIN, v);
	}
	p_task_system_dta->seleccion = 0;
	task_system_set_mode(SETUP);

}

void entrar_falla( task_system_dta_t* p_task_system_dta, task_system_st_t task_system_st){
	display_valores_t v;

	put_event_task_actuator_gpio(EV_OFF,  LED_STATUS);
	put_event_task_actuator_gpio(EV_BLINK, BUZZER);
	put_event_task_actuator_pwm(EV_PWM_OFF, (task_actuator_pwm_id_t)p_task_system_dta->seleccion);
	p_task_system_dta->state = task_system_st;
	task_system_set_mode(FALLA);


	if( p_task_system_dta->state == ST_SYS_TEMPERATURA ){
		armar_valores(p_task_system_dta, &v);
		set_display(PANTALLA_FALLA_TEMPERATURA, v);
	} else {
		armar_valores(p_task_system_dta, &v);
		set_display(PANTALLA_FALLA_ATASCO, v );
	}
}

void entrar_normal( task_system_dta_t* p_task_system_dta, task_system_st_t task_system_st){
	display_valores_t v;

	put_event_task_actuator_gpio(EV_ON,  LED_STATUS);
	put_event_task_actuator_gpio(EV_OFF, BUZZER);
	put_event_task_actuator_pwm(EV_PWM_OFF, (task_actuator_pwm_id_t)p_task_system_dta->seleccion);
	p_task_system_dta->state = task_system_st;
	task_system_set_mode(NORMAL);
	p_task_system_dta->seleccion = 0;
	armar_valores(p_task_system_dta, &v);
	set_display(PANTALLA_ESPERA, v);

}

void task_system_set_mode(task_system_mode_t task_system_mode)
{
	g_task_system_mode = task_system_mode;
}

/********************** end of file ******************************************/


