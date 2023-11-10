/***********************************************
 * Filename:EEPROM_Program.c                   *
 * Description:EEPROM functions implementation *
 * Created on: Oct 31, 2023                    *
 * Author: Zeyad Ossama                        *
 ***********************************************/
#include"STD_TYPES.h"
#include "BIT_MATH.h"
#include"TWI_Interface.h"
#include"EEPROM_Interface.h"
#include"EEPROM_Private.h"
#include"EEPROM_config.h"
#include"util/delay.h"
/*
 * Description:EEPROM initialization
 * */
void EEPROM_voidInit(void)
{
	TWI_voidInitMaster(100);
}
/*
 * Description:Write Byte to given location
 * */
void EEPROM_voidWriteByte(uint8 copy_u8Data,uint16 copy_u16WordAddress)
{
	/*Get Device address*/
	uint8 local_u8Address=((copy_u16WordAddress>>8)|(EEPROM_FIXED_ADDRESS));
	/*Send Start Condition*/
	TWI_voidSendStartCondition();
	/*Send Slave Address with write operation*/
	TWI_voidSendSlaveAddressWithWrite(local_u8Address);
	/*Send Data address*/
	TWI_voidWMasterWriteDataByte((uint8)copy_u16WordAddress);
	/*Send Data*/
	TWI_voidWMasterWriteDataByte(copy_u8Data);
	/*Send Stop condition*/
	TWI_voidSendStopCondition();
	_delay_ms(10);
}
/*
 * Description:Read Byte from given location
 * */
void EEPROM_voidReadByte(uint8* u8DataRecieved,uint16 copy_u16WordAddress)
{
	if(u8DataRecieved!=NULL)
	{
		/*Get Device address*/
		uint8 local_u8Address=((copy_u16WordAddress>>8)|(EEPROM_FIXED_ADDRESS));
		/*Send Start Condition*/
		TWI_voidSendStartCondition();
		/*Send Slave Address with write operation*/
		TWI_voidSendSlaveAddressWithWrite(local_u8Address);
		/*Send Data address*/
		TWI_voidWMasterWriteDataByte((uint8)copy_u16WordAddress);
		/*Send Repeated start*/
		TWI_voidSendRepeatedStartCondition();
		/*Send Slave Address with read operation*/
		TWI_voidSendSlaveAddressWithRead(local_u8Address);
		/*Read Data with no ACK*/
		TWI_voidMasterReadDataByteWithNACK(u8DataRecieved);
		/*Send stop condition*/
		TWI_voidSendStopCondition();
		_delay_ms(10);
	}
}
/*
 * Description:Write page to certain location
 * */
void EEPROM_voidWritePage(uint8 *u8DataArray,uint16 copy_u16WordAddress)
{
	/*Get Device address*/
	uint8 local_u8Address=((copy_u16WordAddress>>8)|(EEPROM_FIXED_ADDRESS));
	/*Send Start Condition*/
	TWI_voidSendStartCondition();
	/*Send Slave Address with write operation*/
	TWI_voidSendSlaveAddressWithWrite(local_u8Address);
	/*Send Data address*/
	TWI_voidWMasterWriteDataByte((uint8)copy_u16WordAddress);
	/*Write Page*/
	for (uint8 i=0;i<PAGE_SIZE;i++)
	{
		TWI_voidWMasterWriteDataByte(*(u8DataArray+i));
	}
	/*Send Stop condition*/
	TWI_voidSendStopCondition();
	_delay_ms(10);
}
/*
 * Description:Read Sequence of bytes from Certain locations
 * */
void EEPROM_voidReadSequential(uint8 *u8ReceivedDataArray,uint16 copy_u16WordAddress,uint8 copy_u8NoByte)
{
	if(u8ReceivedDataArray!=NULL)
	{
		/*Get Device address*/
		uint8 local_u8Address=((copy_u16WordAddress>>8)|(EEPROM_FIXED_ADDRESS));
		/*Send Start Condition*/
		TWI_voidSendStartCondition();
		/*Send Slave Address with write operation*/
		TWI_voidSendSlaveAddressWithWrite(local_u8Address);
		/*Send Data address*/
		TWI_voidWMasterWriteDataByte((uint8)copy_u16WordAddress);
		/*Send repeated start condition*/
		TWI_voidSendRepeatedStartCondition();
		/*Send Slave Address with read operation*/
		TWI_voidSendSlaveAddressWithRead(local_u8Address);
		/*Read Number of bytes sequentially with ACK*/
		for(uint8 i=0;i<copy_u8NoByte-1;i++)
		{
		TWI_voidMasterReadDataByteWithACK(u8ReceivedDataArray+i);
		_delay_ms(10);
		}
		/*Last byte Read with NACK*/
		TWI_voidMasterReadDataByteWithNACK(u8ReceivedDataArray+copy_u8NoByte-1);
		/*Send Stop Conditions*/
		TWI_voidSendStopCondition();
		_delay_ms(10);
	}
}
