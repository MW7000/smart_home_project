/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V01                            */
/*  Date: 30 OCT 2023                       */
/*  SWC: SPI                                */
/********************************************/


#ifndef	SPI_PRIV_H
#define	SPI_PRIV_H


#define      SPI_MASTER_NODE               1
#define      SPI_SLAVE_NODE                2


#define      SPI_MSB_FIRST                 1
#define      SPI_LSB_FIRST                 2


#define      SPI_RISING_LEADING           1
#define      SPI_FALLING_LEADING          2


#define     SPI_SAMPLE_AT_LEADING         1
#define     SPI_SETUP_AT_LEADING          2


#define     SPI_OSC_CLK_DIVIDED_BY_4       0
#define     SPI_OSC_CLK_DIVIDED_BY_16      1
#define     SPI_OSC_CLK_DIVIDED_BY_64      2
#define     SPI_OSC_CLK_DIVIDED_BY_128     3
#define     SPI_OSC_CLK_DIVIDED_BY_2       4
#define     SPI_OSC_CLK_DIVIDED_BY_8       5
#define     SPI_OSC_CLK_DIVIDED_BY_32      6


#define     SPI_OSC_CLK_DIV_BY_4       0
#define     SPI_OSC_CLK_DIV_BY_16      1
#define     SPI_OSC_CLK_DIV_BY_64      2
#define     SPI_OSC_CLK_DIV_BY_128     3
#define     SPI_OSC_CLK_DIV_BY_2       0
#define     SPI_OSC_CLK_DIV_BY_8       1
#define     SPI_OSC_CLK_DIV_BY_32      2

#define 	SPCR_MASK				0xFB


#define 	SPI_TIMEOUT_COUNT		65535

#define		SPI_COLLISION_ERROR		1
#define		SPI_TRANSMISSION_ERROR	2
#define		SPI_NO_ERROR			3



#endif
