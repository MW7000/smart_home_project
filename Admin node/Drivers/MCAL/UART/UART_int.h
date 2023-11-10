/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V02                            */
/*  Date: 5 NOV 2023                        */
/*  SWC: UART                               */
/********************************************/


#ifndef UART_INT_H
#define UART_INT_H

void UART_voidInit(void);

void UART_voidSendChar(uint8 Copy_uint8DataToBeSent);

uint8 UART_uint8RecieveChar(void);

// up to 65535 characters
void UART_voidSendString(uint8 * copy_puint8Data);

uint8 UART_uint8ReceiveString(uint8* copy_puint8DataToBeReceived, uint8 copy_uint8ArrSize);

// return UDR value or no value returned represented by 'UART_NO_DATA_RECIEVED_VALUE' macro

uint16 UART_uint16RecieveCharWithTimeout(void);

#define		UART_NO_DATA_RECIEVED_VALUE	500


#define 	UART_RECEIVE_SUCCESS			5
#define 	UART_RECEIVE_FAILURE			7


#endif
