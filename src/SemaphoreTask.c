/*
 * SemaphoreTask.c
 *
 *  Created on: Jul 10, 2019
 *      Author: preetham
 */

#include "SemaphoreTask.h"
#include "FreeRTOS.h" /* Must come first. */
#include "semphr.h"   /* Semaphore related API prototypes. */

#define mainEVENT_SEMAPHORE_TASK_PRIORITY   ( configMAX_PRIORITIES - 1 )

static void prvEventSemaphoreTask( void *pvParameters );
static SemaphoreHandle_t xEventSemaphore = NULL;
static volatile uint32_t ulCountOfReceivedSemaphores = 0;

void SemaphoreTask_Semaphore_Create(void)
{
	xEventSemaphore = xSemaphoreCreateBinary();

	/* Create the task that is synchronised with an interrupt using the
	    xEventSemaphore semaphore. */
	xTaskCreate(
			prvEventSemaphoreTask,
			"SemaphoreTask",
			configMINIMAL_STACK_SIZE,
			NULL,
			mainEVENT_SEMAPHORE_TASK_PRIORITY,
			NULL );
}

static void prvEventSemaphoreTask( void *pvParameters )
{
	for( ;; )
	{
		xSemaphoreTake( xEventSemaphore, portMAX_DELAY );

		ulCountOfReceivedSemaphores++;
	}
}



