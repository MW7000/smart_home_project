/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V01                            */
/*  Date: 30 OCT 2023                       */
/*  SWC: SPI                                */
/********************************************/


#ifndef	SPI_REG_H
#define	SPI_REG_H


typedef struct{

	uint8 SPCR;
	uint8 SPSR;
	uint8 SPDR;

}SPI_regType;


#define SPI_REG_FILE   ((volatile SPI_regType*) 0x2D)


#define    SPCR_SPR0              0
#define    SPCR_SPR1              1
#define    SPCR_CPHA              2
#define    SPCR_CPOL              3
#define    SPCR_MSTR              4
#define    SPCR_DORD              5
#define    SPCR_SPE               6
#define    SPCR_SPIE              7

#define    SPSR_SPI2X             0
#define    SPSR_WCOL              6
#define    SPSR_SPIF              7

#endif
