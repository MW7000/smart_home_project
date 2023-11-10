/**************************************************************
 * Filename:TWI_Program.c                                      *
 * Description:TWI driver functions implementations            *
 * Created on: Oct 31, 2023                                    *
 * Author: Zeyad Ossama                                        *
 ***************************************************************/
#include"BIT_MATH.h"
#include"STD_TYPES.h"

#include"TWI_Interface.h"
#include"TWI_Private.h"
#include"TWI_Register.h"
/*
 * Description:Initialize TWI as Master
 * */
void TWI_voidInitMaster(uint8 copy_u8SlaveAddress)
{
	if((copy_u8SlaveAddress<128)&&(copy_u8SlaveAddress!=0))
	{
		TWAR=(copy_u8SlaveAddress)<<1;
	}
	TWBR=12;
	CLEAR_BIT(TWSR,TWPS0);
	CLEAR_BIT(TWSR,TWPS1);
	/*Enable Ack*/

	SET_BIT(TWCR,TWEN);
}
/*
 * Description:Send start conditions
 * */
void TWI_voidSendStartCondition(void)
{
	//Request Start Condition
	SET_BIT(TWCR,TWSTA);
	//Enable ACK
	SET_BIT(TWCR,TWEA);
	//Clear interrupt flag
	SET_BIT(TWCR,TWINT);
	//Busy wait
	while(!(GET_BIT(TWCR,TWINT)));
	while((TWSR&TWI_STATUS)!=TWI_START_CONDITION_ACK);
}
/*
 * Description:Send Repeated Start Condition
 * */
void TWI_voidSendRepeatedStartCondition(void)
{
	//Request Start Condition
	SET_BIT(TWCR,TWSTA);
	//Enable ACK
	SET_BIT(TWCR,TWEA);
	//Clear interrupt flag
	SET_BIT(TWCR,TWINT);
	//Busy wait
	while(!(GET_BIT(TWCR,TWINT)));
	while((TWSR&TWI_STATUS)!=TWI_REPEATED_START_CONDITION_ACK);
}
/*
 * Description :Send Stop condition
 * */
void TWI_voidSendStopCondition(void)
{
	//Request Start Condition
	SET_BIT(TWCR,TWSTO);
	//Clear interrupt flag
	SET_BIT(TWCR,TWINT);
}
/*
 * Description:Send Slave Address with Read operation
 * */
void TWI_voidSendSlaveAddressWithRead(uint8 copy_u8SlaveAddress)
{
	if(copy_u8SlaveAddress<128)
	{
		TWDR=copy_u8SlaveAddress<<1;
		SET_BIT(TWDR,0);
		////Enable ACK
		SET_BIT(TWCR,TWEA);
		//Clear Start condition
		CLEAR_BIT(TWCR,TWSTA);
		//Clear Interrupt Flag
		SET_BIT(TWCR,TWINT);
		//Busy wait
		while(!(GET_BIT(TWCR,TWINT)));
		while((TWSR&TWI_STATUS)!=TWI_SEND_SLAVE_ADDRESS_READ_ACK);
	}
}
/*
 * Description:Send Slave Address with write operation
 * */
void TWI_voidSendSlaveAddressWithWrite(uint8 copy_u8SlaveAddress)
{
	if(copy_u8SlaveAddress<128)
	{
		TWDR=copy_u8SlaveAddress<<1;
		CLEAR_BIT(TWDR,0);
		//Enable ACK
		SET_BIT(TWCR,TWEA);
		//Clear Start condition
		CLEAR_BIT(TWCR,TWSTA);
		//Clear Interrupt Flag
		SET_BIT(TWCR,TWINT);
		//Busy wait
		while(!(GET_BIT(TWCR,TWINT)));
		while((TWSR&TWI_STATUS)!=TWI_SEND_SLAVE_ADDRESS_WRITE_ACK);
	}
}
/*
 * Description:Read Data with ACK
 * */

void TWI_voidMasterReadDataByteWithACK(uint8* receiveData)
{
	if(receiveData!=NULL)
	{
		SET_BIT(TWCR,TWINT);
		//Enable ACK
		SET_BIT(TWCR,TWEA);
		//Busy wait
		while(!(GET_BIT(TWCR,TWINT)));
		while((TWSR&TWI_STATUS)!=TWI_MASTER_RECEIVE_DATA_ACK);
		*receiveData=TWDR;
	}
}
/*
 * Description:Read Data with No ACK
 * */
void TWI_voidMasterReadDataByteWithNACK(uint8* receiveData)
{
	if(receiveData!=NULL)
	{
		SET_BIT(TWCR,TWINT);
		//Enable NACK
		CLEAR_BIT(TWCR,TWEA);
		//Busy wait
		while(!(GET_BIT(TWCR,TWINT)));
		while((TWSR&TWI_STATUS)!=TWI_MASTER_RECEIVE_DATA_NACK);
		*receiveData=TWDR;
	}
}
/*
 * Description:Write Data
 * */
void TWI_voidWMasterWriteDataByte(uint8 copy_u8Data)
{
	TWDR=copy_u8Data;
	//Enable ACK
	SET_BIT(TWCR,TWEA);
	//Clear Interrupt Flag
	SET_BIT(TWCR,TWINT);
	//Busy wait
	while(!(GET_BIT(TWCR,TWINT)));
	while((TWSR&TWI_STATUS)!=TWI_MASTER_TRANSMIT_DATA_ACK);
}
