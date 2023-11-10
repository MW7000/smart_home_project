/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V01                            */
/*  Date: 30 OCT 2023                       */
/*  SWC: SPI                                */
/********************************************/

#ifndef	SPI_CONFIG_H
#define	SPI_CONFIG_H


/*
 * options:
 *	SPI_MASTER_NODE
 *  SPI_SLAVE_NODE
 *
 */


#define		SPI_NODE_MODE			SPI_MASTER_NODE




/*
 * options:
 *     SPI_MSB_FIRST
 *     SPI_LSB_FIRST
 *
 */


#define		SPI_COMM_DATA_ORDER		SPI_MSB_FIRST


/*
 * options:
 *    SPI_RISING_LEADING
 *    SPI_FALLING_LEADING
 *
 */



#define		SPI_CLK_POLARITY		SPI_RISING_LEADING



/*
 * options:
 *   SPI_SAMPLE_AT_LEADING
 *   SPI_SETUP_AT_LEADING
 *
 */


#define		SPI_CLK_PHASE			SPI_SAMPLE_AT_LEADING


/*
 * options:
 *   SPI_OSC_CLK_DIVIDED_BY_4
 *   SPI_OSC_CLK_DIVIDED_BY_16
 *   SPI_OSC_CLK_DIVIDED_BY_64
 *   SPI_OSC_CLK_DIVIDED_BY_128
 *   SPI_OSC_CLK_DIVIDED_BY_2
 *   SPI_OSC_CLK_DIVIDED_BY_8
 *   SPI_OSC_CLK_DIVIDED_BY_32
 *
 */


#define 	SPI_SCLK_RATE			SPI_OSC_CLK_DIVIDED_BY_16



#if  SPI_SCLK_RATE==SPI_OSC_CLK_DIVIDED_BY_4

#define	SPI_SCLK_CHOICE SPI_OSC_CLK_DIV_BY_4

#elif  SPI_SCLK_RATE==SPI_OSC_CLK_DIVIDED_BY_16

#define	SPI_SCLK_CHOICE SPI_OSC_CLK_DIV_BY_16

#elif  SPI_SCLK_RATE==SPI_OSC_CLK_DIVIDED_BY_64

#define	SPI_SCLK_CHOICE SPI_OSC_CLK_DIV_BY_64

#elif  SPI_SCLK_RATE==SPI_OSC_CLK_DIVIDED_BY_128

#define	SPI_SCLK_CHOICE SPI_OSC_CLK_DIV_BY_128

#elif  SPI_SCLK_RATE==SPI_OSC_CLK_DIVIDED_BY_2

#define	SPI_SCLK_CHOICE SPI_OSC_CLK_DIV_BY_2

#elif  SPI_SCLK_RATE==SPI_OSC_CLK_DIVIDED_BY_8

#define	SPI_SCLK_CHOICE SPI_OSC_CLK_DIV_BY_8

#elif  SPI_SCLK_RATE==SPI_OSC_CLK_DIVIDED_BY_32

#define	SPI_SCLK_CHOICE SPI_OSC_CLK_DIV_BY_32

#endif


#endif

