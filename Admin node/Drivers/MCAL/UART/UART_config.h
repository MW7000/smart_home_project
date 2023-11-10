/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V02                            */
/*  Date: 5 NOV 2023                        */
/*  SWC: UART                               */
/********************************************/


#ifndef UART_CONFIG_H
#define UART_CONFIG_H


#define			SYSTEM_OSC_FREQ				8000000

/*
 * options:
 * 		UART_ASYNCH_OPERATION
 * 		UART_SYNCH_OPERATION
 *
 */

#define         UART_OPERATION_MODE       UART_ASYNCH_OPERATION


#if		UART_OPERATION_MODE==UART_SYNCH_OPERATION

/*
 *  options:
 *  		UART_TX_RISING_XCK_EDGE
 *  		UART_TX_FALLING_XCK_EDGE
 */

#define         UART_CLOCK_POLARITY		UART_TX_RISING_XCK_EDGE


#endif

/*
 * options:
 * 		UART_DOUBLE_SPEED_COMMUNICATION
 * 		UART_NORMAL_SPEED_COMMUNICATION
 *
 */


#define         UART_TRANSMISSION_SPEED		UART_NORMAL_SPEED_COMMUNICATION


/*
 * options:
 * 		UART_MULTI_PROCESSOR_ACTIVE
 * 		UART_MULTI_PROCESSOR_INACTIVE
 *
 */

#define         UART_MULTI_PROCESSOR_MODE		UART_MULTI_PROCESSOR_INACTIVE


/*
 * options:
 * 		UART_5_BIT_CHARACTER_SIZE
 * 		UART_6_BIT_CHARACTER_SIZE
 *      UART_7_BIT_CHARACTER_SIZE
 *      UART_8_BIT_CHARACTER_SIZE
 *      UART_9_BIT_CHARACTER_SIZE
 *
 */


#define         UART_CHARACTER_SIZE			UART_8_BIT_CHARACTER_SIZE


/*
 * options:
 * 		UART_DISABLED_PARITY_MODE
 * 		UART_EVEN_PARITY_MODE
 *      UART_ODD_PARITY_MODE
 */

#define         UART_PARITY_MODE		UART_DISABLED_PARITY_MODE



/*
 * options :
 *         UART_2400_BPS_BAUD_RATE
 *         UART_4800_BPS_BAUD_RATE
 *         UART_9600_BPS_BAUD_RATE
 *         UART_14400_BPS_BAUD_RATE
 *         UART_19200_BPS_BAUD_RATE
 *         UART_28800_BPS_BAUD_RATE
 *         UART_38400_BPS_BAUD_RATE
 *         UART_57600_BPS_BAUD_RATE
 *         UART_76800_BPS_BAUD_RATE
 *         UART_115200_BPS_BAUD_RATE
 *         UART_230400_BPS_BAUD_RATE
 *         UART_250000_BPS_BAUD_RATE
 *         UART_500000_BPS_BAUD_RATE
 *         UART_1M_BPS_BAUD_RATE
 *
 */

#define         UART_BAUD_RATE		UART_9600_BPS_BAUD_RATE


/*
 *  options:
 *  		UART_1_STOP_BIT
 *  		UART_2_STOP_BITS
 *
 */

#define         UART_STOP_BITS_NO		UART_1_STOP_BIT


#endif
