/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V01                            */
/*  Date: 30 OCT 2023                       */
/*  SWC: SPI                                */
/********************************************/


#ifndef	SPI_INT_H
#define	SPI_INT_H



void SPI_voidInit(void);

uint8 SPI_uint8TransceiveSynch(uint8 copy_uint8DataByteToTransmit, uint8* copy_uint8DataByteToReceive);

uint8 SPI_uint8TransmitAsynch(uint8 copy_uint8DataByteToTransmit, void (* copy_fptrAppFunc)(uint8 copy_uint8ReceivedData));


#define		SPI_COLLISION_ERROR		1
#define		SPI_TRANSMISSION_ERROR	2
#define		SPI_NO_ERROR			3


#endif
