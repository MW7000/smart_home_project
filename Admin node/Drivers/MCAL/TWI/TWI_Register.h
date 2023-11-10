/***************************************
 * Filename:TWI_Register.h             *
 * Description:TWI Register File       *
 * Created on: Oct 31, 2023            *
 * Author: Zeyad Ossama                *
 ***************************************/

#ifndef MCAL_TWI_TWI_REGISTER_H_
#define MCAL_TWI_TWI_REGISTER_H_

/*TWI Control Register*/
#define TWCR  (*(volatile uint8 *)0x56)
#define TWIE   0
#define TWEN   2
#define TWWC   3
#define TWSTO  4
#define TWSTA  5
#define TWEA   6
#define TWINT  7

/*TWI Data Register*/
#define TWDR  (*(volatile uint8 *)0x23)

/*TWI (Slave) Address Register*/
#define TWAR  (*(volatile uint8 *)0x22)
#define TWGCE 0
//Bits 7..1 – TWA

/*TWI Status Register*/
#define TWSR  (*(volatile uint8 *)0x21)
#define TWPS0  0
#define TWPS1  1
// Bits 7..3 TWS

/*TWI Bit Rate Register*/
#define TWBR  (*(volatile uint8 *)0x20)


#endif /* MCAL_TWI_TWI_REGISTER_H_ */
