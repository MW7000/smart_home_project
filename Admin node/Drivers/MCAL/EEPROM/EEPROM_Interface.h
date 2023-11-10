/***************************************
 * Filename:EEPROM_Interface.h         *
 * Description: EEPROM APIs            *
 * Created on: Oct 31, 2023            *
 * Author: Zeyad Ossama                *
 ***************************************/

#ifndef HAL_EEPROM_EEPROM_INTERFACE_H_
#define HAL_EEPROM_EEPROM_INTERFACE_H_
/*
 * Description:EEPROM initialization
 * */
void EEPROM_voidInit(void);
/*
 * Description:Write Byte to given location
 * */
void EEPROM_voidWriteByte(uint8 copy_u8Data,uint16 copy_u16WordAddress);
/*
 * Description:Read Byte from given location
 * */
void EEPROM_voidReadByte(uint8* u8DataRecieved,uint16 copy_u16WordAddress);
/*
 * Description:Write page to certain location
 * */
void EEPROM_voidWritePage(uint8 *u8DataArray,uint16 copy_u16WordAddress);
/*
 * Description:Read Sequence of bytes from Certain locations
 * */
void EEPROM_voidReadSequential(uint8 *u8ReceivedDataArray,uint16 copy_u16WordAddress,uint8 copy_u8NoByte);
#endif /* HAL_EEPROM_EEPROM_INTERFACE_H_ */
