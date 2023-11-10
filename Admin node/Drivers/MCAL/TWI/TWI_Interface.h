/***************************************
 * Filename:TWI_Interface.h            *
 * Description:TWI modules API         *
 * Created on: Oct 31, 2023            *
 * Author: Zeyad Ossama                *
 ***************************************/

#ifndef MCAL_TWI_TWI_INTERFACE_H_
#define MCAL_TWI_TWI_INTERFACE_H_
/*
 * Description:Initialize TWI as Master
 * */
void TWI_voidInitMaster(uint8 copy_u8SlaveAddress);
/*
 * Description:Send start conditions
 * */
void TWI_voidSendStartCondition(void);
/*
 * Description:Send Repeated Start Condition
 * */
void TWI_voidSendRepeatedStartCondition(void);
/*
 * Description :Send Stop condition
 * */
void TWI_voidSendStopCondition(void);
/*
 * Description:Send Slave Address with Read operation
 * */
void TWI_voidSendSlaveAddressWithRead(uint8 copy_u8SlaveAddress);
/*
 * Description:Send Slave Address with write operation
 * */
void TWI_voidSendSlaveAddressWithWrite(uint8 copy_u8SlaveAddress);
/*
 * Description:Read Data with No ACK
 * */
void TWI_voidMasterReadDataByteWithNACK(uint8* receiveData);
/*
 * Description:Read Data with No ACK
 * */
void TWI_voidMasterReadDataByteWithACK(uint8* receiveData);
/*
 * Description:Write Data
 * */
void TWI_voidWMasterWriteDataByte(uint8 copy_u8Data);

#endif /* MCAL_TWI_TWI_INTERFACE_H_ */
