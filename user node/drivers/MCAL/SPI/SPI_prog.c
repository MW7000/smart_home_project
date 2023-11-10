/********************************************/
/*  author: Mohamed Walid                   */
/*  version: V01                            */
/*  Date: 30 OCT 2023                       */
/*  SWC: SPI                                */
/********************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_int.h"
#include "SPI_reg.h"
#include "SPI_priv.h"
#include "SPI_config.h"

static void (*private_fptrCallBackFunc) (uint8 copy_uint8DataParam)=NULL;

void SPI_voidInit(void){

#if	SPI_NODE_MODE == SPI_MASTER_NODE

	SET_BIT(SPI_REG_FILE->SPCR, SPCR_MSTR);

#if SPI_COMM_DATA_ORDER == SPI_MSB_FIRST

	CLEAR_BIT(SPI_REG_FILE->SPCR, SPCR_DORD);

#elif SPI_COMM_DATA_ORDER == SPI_LSB_FIRST

	SET_BIT(SPI_REG_FILE->SPCR, SPCR_DORD);


#endif


#if	SPI_CLK_POLARITY == SPI_RISING_LEADING

	CLEAR_BIT(SPI_REG_FILE->SPCR, SPCR_CPOL);

#elif SPI_CLK_POLARITY == SPI_FALLING_LEADING

	SET_BIT(SPI_REG_FILE->SPCR, SPCR_CPOL);

#endif


#if SPI_CLK_PHASE == SPI_SETUP_AT_LEADING

	SET_BIT(SPI_REG_FILE->SPCR, SPCR_CPHA);

#elif SPI_CLK_PHASE == SPI_SAMPLE_AT_LEADING

	CLEAR_BIT(SPI_REG_FILE->SPCR, SPCR_CPHA);

#endif


#if SPI_SCLK_RATE>SPI_OSC_CLK_DIVIDED_BY_128

	SET_BIT(SPI_REG_FILE->SPSR,SPSR_SPI2X);

	SPI_REG_FILE->SPCR &= SPCR_MASK;

	SPI_REG_FILE->SPCR |= SPI_SCLK_CHOICE;

#elif SPI_SCLK_RATE<SPI_OSC_CLK_DIVIDED_BY_2

	CLEAR_BIT(SPI_REG_FILE->SPSR,SPSR_SPI2X);

	SPI_REG_FILE->SPCR &= SPCR_MASK;

	SPI_REG_FILE->SPCR |= SPI_SCLK_CHOICE;

#endif

#elif SPI_NODE_MODE == SPI_SLAVE_NODE

	CLEAR_BIT(SPI_REG_FILE->SPCR, SPCR_MSTR);

#if SPI_COMM_DATA_ORDER == SPI_MSB_FIRST

	CLEAR_BIT(SPI_REG_FILE->SPCR, SPCR_DORD);

#elif SPI_COMM_DATA_ORDER == SPI_LSB_FIRST

	SET_BIT(SPI_REG_FILE->SPCR, SPCR_DORD);


#endif


#if	SPI_CLK_POLARITY == SPI_RISING_LEADING

	CLEAR_BIT(SPI_REG_FILE->SPCR, SPCR_CPOL);

#elif SPI_CLK_POLARITY == SPI_FALLING_LEADING

	SET_BIT(SPI_REG_FILE->SPCR, SPCR_CPOL);

#endif


#if SPI_CLK_PHASE == SPI_SETUP_AT_LEADING

	SET_BIT(SPI_REG_FILE->SPCR, SPCR_CPHA);

#elif SPI_CLK_PHASE == SPI_SAMPLE_AT_LEADING

	CLEAR_BIT(SPI_REG_FILE->SPCR, SPCR_CPHA);

#endif


#endif

	SET_BIT(SPI_REG_FILE->SPCR,SPCR_SPE);		// Enabling SPI Peripheral

}




uint8 SPI_uint8TransceiveSynch(uint8 copy_uint8DataByteToTransmit, uint8* copy_uint8DataByteToReceive){

	uint8 local_uint8ErrorStatus=SPI_NO_ERROR;
	uint16 local_uint16Counter=0;

	while(GET_BIT(SPI_REG_FILE->SPSR,SPSR_WCOL)==1){			// checking the collision flag

		local_uint16Counter++;
		if(local_uint16Counter==SPI_TIMEOUT_COUNT){
			local_uint8ErrorStatus = SPI_COLLISION_ERROR;
			return local_uint8ErrorStatus;
		}
	}

	local_uint16Counter=0;
	SPI_REG_FILE->SPDR = copy_uint8DataByteToTransmit;

	while(GET_BIT(SPI_REG_FILE->SPSR,SPSR_SPIF)==0){ 												// checking Transmission complete flag

		local_uint16Counter++;
		if(local_uint16Counter==SPI_TIMEOUT_COUNT){
			local_uint8ErrorStatus = SPI_TRANSMISSION_ERROR;
			return local_uint8ErrorStatus;
		}
	}

	*copy_uint8DataByteToReceive = SPI_REG_FILE->SPDR;

	return local_uint8ErrorStatus;

}


uint8 SPI_uint8TransmitAsynch(uint8 copy_uint8DataByteToTransmit, void (* copy_fptrAppFunc)(uint8 copy_uint8ReceivedData)){

	uint8 local_uint8ErrorStatus=SPI_NO_ERROR;

	SET_BIT(SPI_REG_FILE->SPCR,SPCR_SPIE);	// Enabling SPI ISR

	private_fptrCallBackFunc = copy_fptrAppFunc;

	if(GET_BIT(SPI_REG_FILE->SPSR,SPSR_WCOL)==1){			// checking the collision flag

		local_uint8ErrorStatus = SPI_COLLISION_ERROR;
		return local_uint8ErrorStatus;
	}

	SPI_REG_FILE->SPDR = copy_uint8DataByteToTransmit;

	return local_uint8ErrorStatus;
}


void __vector_12(void)		__attribute__ ((signal));
void __vector_12(void){

	private_fptrCallBackFunc(SPI_REG_FILE->SPDR);

}
