/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V02                            */
/*  Date: 5 NOV 2023                        */
/*  SWC: UART                               */
/********************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART_int.h"
#include "UART_reg.h"
#include "UART_priv.h"
#include "UART_config.h"
#include <util/delay.h>

#define		UART_RECEIVE_TIMEOUT		65535


static uint8 private_uint8BusyStatus=UART_RECEIVE_FUNC_IDLE;

void UART_voidInit(void){

	uint16 local_uint16UBRR_value;
	uint8 local_uint8UCSRC_RegContent=0, local_uint8UCSRA_RegContent=0, local_uint8UCSRB_RegContent=0, local_uint8UBRRH_RegContent;
	// making absolutely every write operation to the UART module registers an atomic operation


#if UART_OPERATION_MODE==UART_ASYNCH_OPERATION

		CLEAR_BIT(local_uint8UCSRC_RegContent, UCSRC_UMSEL);
		CLEAR_BIT(local_uint8UCSRC_RegContent, UCSRC_UCPOL);				// Cleared in Asynch mode

#elif UART_OPERATION_MODE==UART_SYNCH_OPERATION

		SET_BIT(local_uint8UCSRC_RegContent, UCSRC_UMSEL);

#if UART_CLOCK_POLARITY==UART_TX_RISING_XCK_EDGE

			CLEAR_BIT(local_uint8UCSRC_RegContent,UCSRC_UCPOL);

#elif UART_CLOCK_POLARITY==UART_TX_FALLING_XCK_EDGE

			SET_BIT(local_uint8UCSRC_RegContent,UCSRC_UCPOL);

#endif

#endif


#if UART_PARITY_MODE==UART_DISABLED_PARITY_MODE

		CLEAR_BIT(local_uint8UCSRC_RegContent,UCSRC_UPM0);
		CLEAR_BIT(local_uint8UCSRC_RegContent,UCSRC_UPM1);

#elif UART_PARITY_MODE==UART_EVEN_PARITY_MODE

		CLEAR_BIT(local_uint8UCSRC_RegContent,UCSRC_UPM0);
		SET_BIT(local_uint8UCSRC_RegContent,UCSRC_UPM1);

#elif UART_PARITY_MODE==UART_ODD_PARITY_MODE

		SET_BIT(local_uint8UCSRC_RegContent,UCSRC_UPM0);
		SET_BIT(local_uint8UCSRC_RegContent,UCSRC_UPM1);

#endif


#if  UART_STOP_BITS_NO==UART_1_STOP_BIT

		CLEAR_BIT(local_uint8UCSRC_RegContent,UCSRC_USBS);

#elif UART_STOP_BITS_NO==UART_2_STOP_BITS

		SET_BIT(local_uint8UCSRC_RegContent,UCSRC_USBS);

#endif


#if UART_CHARACTER_SIZE<UART_9_BIT_CHARACTER_SIZE

		local_uint8UCSRC_RegContent &= UCSRC_UCSZ_BITS_MASK;
		local_uint8UCSRC_RegContent |= ( UART_CHARACTER_SIZE<<1);

#elif UART_CHARACTER_SIZE==UART_9_BIT_CHARACTER_SIZE

		SET_BIT(local_uint8UCSRB_RegContent, UCSRB_UCSZ2);
		SET_BIT(local_uint8UCSRC_RegContent, UCSRC_UCSZ0);
		SET_BIT(local_uint8UCSRC_RegContent, UCSRC_UCSZ1);

#endif

#if UART_TRANSMISSION_SPEED==UART_DOUBLE_SPEED_COMMUNICATION

		SET_BIT(local_uint8UCSRA_RegContent, UCSRA_U2X);
		local_uint16UBRR_value = ((uint32) SYSTEM_OSC_FREQ/(8 * UART_BAUD_RATE));


#elif UART_TRANSMISSION_SPEED==UART_NORMAL_SPEED_COMMUNICATION

		CLEAR_BIT(local_uint8UCSRA_RegContent, UCSRA_U2X);
		local_uint16UBRR_value=((uint32) SYSTEM_OSC_FREQ/(16 * UART_BAUD_RATE));

#endif


#if UART_MULTI_PROCESSOR_MODE==UART_MULTI_PROCESSOR_ACTIVE

		SET_BIT(local_uint8UCSRA_RegContent,UCSRA_MPCM);

#elif UART_MULTI_PROCESSOR_MODE==UART_MULTI_PROCESSOR_INACTIVE

		CLEAR_BIT(local_uint8UCSRA_RegContent,UCSRA_MPCM);

#endif

	if((local_uint16UBRR_value%10)>4){
		local_uint16UBRR_value/=10;
	}else{
		local_uint16UBRR_value/=10;
		local_uint16UBRR_value--;
	}

	SET_BIT(local_uint8UCSRC_RegContent, UCSRC_URSEL);		// Selecting UCSRC register

	local_uint8UBRRH_RegContent = (local_uint16UBRR_value>>8);
	CLEAR_BIT(local_uint8UBRRH_RegContent,UBRRH_URSEL);

	UBRRH = local_uint8UBRRH_RegContent;
	UBRRL = (uint8)local_uint16UBRR_value;						// Setting the baud rate to be 9600

	UCSRA = local_uint8UCSRA_RegContent;

	SET_BIT(local_uint8UCSRB_RegContent,UCSRB_TXEN);				// Enabling transmitter and receiver
	SET_BIT(local_uint8UCSRB_RegContent,UCSRB_RXEN);

	UCSRB = local_uint8UCSRB_RegContent;

	UCSRC = local_uint8UCSRC_RegContent;


}

void UART_voidSendChar(uint8 Copy_charDataToBeSent){

	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);				// Checking the UDRE flag

	UDR = Copy_charDataToBeSent;

}
uint8 UART_uint8RecieveChar(void){

	uint8 receivedChar;
	while(GET_BIT(UCSRA,UCSRA_RXC)==0);				// Checking the receive flag

	if(GET_BIT(UCSRA, UCSRA_DOR)||GET_BIT(UCSRA,UCSRA_FE)){
		receivedChar=UDR;
		receivedChar=0xff;
	}
	else
	{
		receivedChar=UDR;
	}
	return receivedChar;

}

void UART_voidSendString(uint8 * copy_puint8Data){

	uint16 i=0;

	while(copy_puint8Data[i]!='\0'){

		UART_voidSendChar(copy_puint8Data[i]);
		i++;
	}

}

uint8 UART_uint8ReceiveString(uint8* copy_puint8DataToBeReceived, uint8 copy_uint8ArrSize){

	uint8 local_uint8ReceiveOperationStatus=UART_RECEIVE_FAILURE;
	if(UART_RECEIVE_FUNC_IDLE==private_uint8BusyStatus){

		private_uint8BusyStatus=UART_RECEIVE_FUNC_BUSY;

		uint8 i;
		for(i=0;i<copy_uint8ArrSize;i++){

			copy_puint8DataToBeReceived[i]=UART_uint8RecieveChar();
			if(copy_puint8DataToBeReceived[i]==0xff){
				i--;
			}
		}
		if(copy_uint8ArrSize>1){
			copy_puint8DataToBeReceived[i]='\0';
		}
		CLEAR_BIT(UCSRB,UCSRB_RXEN); 		// Flushing UDR buffer
		_delay_ms(5);
		SET_BIT(UCSRB,UCSRB_RXEN);
		private_uint8BusyStatus=UART_RECEIVE_FUNC_IDLE;
		local_uint8ReceiveOperationStatus=UART_RECEIVE_SUCCESS;

	}
	return local_uint8ReceiveOperationStatus;
}

uint16 UART_uint16RecieveCharWithTimeout(void){

	uint16 receivedChar;
	uint16 local_uint8Counter=0;
	while(GET_BIT(UCSRA,UCSRA_RXC)==0){				// Checking the receive flag

		local_uint8Counter++;
		if(UART_RECEIVE_TIMEOUT==local_uint8Counter){
			break;
		}
	}

	if(local_uint8Counter<UART_RECEIVE_TIMEOUT){

		if(GET_BIT(UCSRA, UCSRA_DOR)||GET_BIT(UCSRA,UCSRA_FE)){
			receivedChar=UDR;
			receivedChar=0xff;
		}
		else
		{
			receivedChar=UDR;
		}
		CLEAR_BIT(UCSRB,UCSRB_RXEN); 		// Flushing UDR buffer
		_delay_ms(5);
		SET_BIT(UCSRB,UCSRB_RXEN);
	}
	else{
		receivedChar = UART_NO_DATA_RECIEVED_VALUE;
	}
	return receivedChar;

}
