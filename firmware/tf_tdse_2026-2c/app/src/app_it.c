

/********************** inclusions *******************************************/
/* Project includes */
#include "main.h"

/* Demo includes */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes */
#include "board.h"

/********************** macros and definitions *******************************/

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data declaration ****************************/
volatile uint32_t g_app_tick_cnt;

/********************** external functions definition ************************/
void app_it_init(void)
{
	/* Protect shared resource */
	__asm("CPSID i");	/* disable interrupts */
	/* Init Tick Counter */
	g_app_tick_cnt = ZERO;
    __asm("CPSIE i");	/* enable interrupts */
}

void HAL_SYSTICK_Callback(void)
{
	/* Update Tick Counter */
	g_app_tick_cnt++;
}

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// Check which version of the gpio triggered this callback

}

/********************** end of file ******************************************/
