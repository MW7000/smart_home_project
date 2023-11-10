/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V02                            */
/*  Date: 5 NOV 2023                        */
/*  SWC: UART                               */
/********************************************/

#ifndef UART_PRIV_H
#define UART_PRIV_H


#define			UCSRC_UCSZ_BITS_MASK		0xF9

#define    UART_ASYNCH_OPERATION            3
#define    UART_SYNCH_OPERATION             1

#define    UART_DOUBLE_SPEED_COMMUNICATION	1
#define    UART_NORMAL_SPEED_COMMUNICATION	3

#define    UART_MULTI_PROCESSOR_ACTIVE      1
#define    UART_MULTI_PROCESSOR_INACTIVE    3

#define    UART_5_BIT_CHARACTER_SIZE        0
#define    UART_6_BIT_CHARACTER_SIZE        1
#define    UART_7_BIT_CHARACTER_SIZE        2
#define    UART_8_BIT_CHARACTER_SIZE        3
#define    UART_9_BIT_CHARACTER_SIZE        7

#define    UART_DISABLED_PARITY_MODE        5
#define    UART_EVEN_PARITY_MODE            7
#define    UART_ODD_PARITY_MODE             9

#define    UART_1_STOP_BIT                  3
#define    UART_2_STOP_BITS                 1

#define    UART_TX_RISING_XCK_EDGE          3
#define    UART_TX_FALLING_XCK_EDGE         1

#define    UART_2400_BPS_BAUD_RATE          240
#define    UART_4800_BPS_BAUD_RATE          480
#define    UART_9600_BPS_BAUD_RATE          960
#define    UART_14400_BPS_BAUD_RATE         1440
#define    UART_19200_BPS_BAUD_RATE         1920
#define    UART_28800_BPS_BAUD_RATE         2880
#define    UART_38400_BPS_BAUD_RATE         3840
#define    UART_57600_BPS_BAUD_RATE         5760
#define    UART_76800_BPS_BAUD_RATE         7680
#define    UART_115200_BPS_BAUD_RATE        11520
#define    UART_230400_BPS_BAUD_RATE        23040
#define    UART_250000_BPS_BAUD_RATE        25000
#define    UART_500000_BPS_BAUD_RATE        50000
#define    UART_1M_BPS_BAUD_RATE            100000


#define 	UART_RECEIVE_FUNC_BUSY			9
#define 	UART_RECEIVE_FUNC_IDLE			11


#endif
