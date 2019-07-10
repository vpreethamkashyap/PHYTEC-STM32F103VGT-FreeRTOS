/*
 * QueueTask.c
 *
 *  Created on: Jul 10, 2019
 *      Author: preetham
 */
#include "FreeRTOS.h" /* Must come first. */
#include "QueueTask.h"
#include "queue.h"    /* RTOS queue related API prototypes. */
#include "task.h"     /* RTOS task related API prototypes. */

#define mainQUEUE_RECEIVE_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2 )
#define mainQUEUE_SEND_TASK_PRIORITY        ( tskIDLE_PRIORITY + 1 )
#define mainQUEUE_SEND_PERIOD_MS            pdMS_TO_TICKS( 200 )
#define mainQUEUE_LENGTH                    ( 1 )

static void prvQueueReceiveTask( void *pvParameters );
static void prvQueueSendTask( void *pvParameters );
static QueueHandle_t xQueue = NULL;
static volatile uint32_t ulCountOfItemsReceivedOnQueue = 0;

void QueueTask_Queue_Create(void)
{
	/* Create the queue used by the queue send and queue receive tasks. */
	xQueue = xQueueCreate(
			mainQUEUE_LENGTH,
			sizeof( uint32_t ) );


	/* Create the queue receive task as described in the
	 * comments at the top of this file. */
	xTaskCreate(
			prvQueueReceiveTask,
			"RX",
			configMINIMAL_STACK_SIZE,
			NULL,
			mainQUEUE_RECEIVE_TASK_PRIORITY,
			NULL );

	/* Create the queue send task in exactly the same way.
	 * Again, this is described in the comments at the top
	 * of the file. */
	xTaskCreate(
			prvQueueSendTask,
			"TX",
			configMINIMAL_STACK_SIZE,
			NULL,
			mainQUEUE_SEND_TASK_PRIORITY,
			NULL );
}

static void prvQueueSendTask( void *pvParameters )
{
	TickType_t xNextWakeTime;
	const uint32_t ulValueToSend = 100UL;

	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		vTaskDelayUntil( &xNextWakeTime, mainQUEUE_SEND_PERIOD_MS );

		xQueueSend( xQueue, &ulValueToSend, 0 );
	}
}

static void prvQueueReceiveTask( void *pvParameters )
{
	uint32_t ulReceivedValue;

	for( ;; )
	{
		xQueueReceive( xQueue, &ulReceivedValue, portMAX_DELAY );

		if( ulReceivedValue == 100UL )
		{
			ulCountOfItemsReceivedOnQueue++;
		}
	}
}
