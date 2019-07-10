/*
 * Timer.c
 *
 *  Created on: Jul 10, 2019
 *      Author: preetham
 */

#include "FreeRTOS.h" /* Must come first. */
#include "timers.h"   /* Software timer related API prototypes. */
#include "Timer.h"
#include "helloWorld.h"

using namespace helloWorld;

#define mainSOFTWARE_TIMER_PERIOD_MS        pdMS_TO_TICKS( 1000 )

static void vExampleTimerCallback( TimerHandle_t xTimer );
static volatile uint32_t ulCountOfTimerCallbackExecutions = 0;

helloWorld::helloWorld helloworldObj;

void Timer_Create(void)
{
	TimerHandle_t xExampleSoftwareTimer = NULL;

	/* Create the software timer as described in the comments at the top of
	    this file. */
	xExampleSoftwareTimer = xTimerCreate
			(
					"LEDTimer",
					mainSOFTWARE_TIMER_PERIOD_MS,
					pdTRUE,
					( void * ) 0,
					vExampleTimerCallback
			);

	xTimerStart( xExampleSoftwareTimer, 0 );

}

static void vExampleTimerCallback( TimerHandle_t xTimer )
{
	helloworldObj.printhelloWorld();

	(void)xTimer;
	ulCountOfTimerCallbackExecutions++;
}
