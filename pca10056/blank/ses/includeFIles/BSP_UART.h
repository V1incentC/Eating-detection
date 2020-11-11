#ifndef BSP_UART_INC_BSP_UART_H_
#define BSP_UART_INC_BSP_UART_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "app_uart.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf.h"
#include "bsp.h"
#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif
#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif

//#define ENABLE_LOOPBACK_TEST  /**< if defined, then this example will be a loopback test, which means that TX should be connected to RX to get data loopback. */

#define MAX_TEST_DATA_BYTES     (17U)                /**< max number of test bytes to be used for tx and rx. */
#define UART_TX_BUF_SIZE 32768                        /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE 32768                         /**< UART RX buffer size. */



void uart_error_handle(app_uart_evt_t * p_event);
void uart_init();


#endif /* BSP_UART_INC_BSP_UART_H_ */