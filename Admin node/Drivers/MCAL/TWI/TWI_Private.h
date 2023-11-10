/****************************************
 * Filename:TWI_Private.h               *
 * Description:TWI Private file         *
 * Created on: Oct 31, 2023             *
 * Author: Zeyad Ossama                 *
 ***************************************/

#ifndef MCAL_TWI_TWI_PRIVATE_H_
#define MCAL_TWI_TWI_PRIVATE_H_
#define TWI_STATUS                               0XF8
#define TWI_START_CONDITION_ACK                  0x08
#define TWI_REPEATED_START_CONDITION_ACK         0x10
#define TWI_SEND_SLAVE_ADDRESS_WRITE_ACK         0x18
#define TWI_SEND_SLAVE_ADDRESS_READ_ACK          0x40
#define TWI_MASTER_TRANSMIT_DATA_ACK             0x28
#define TWI_MASTER_RECEIVE_DATA_ACK              0x50
#define TWI_MASTER_RECEIVE_DATA_NACK             0x58

#endif /* MCAL_TWI_TWI_PRIVATE_H_ */
